//
// Created by Phoenix on 25.12.2021.
//

#include "Ppm.h"
#include "Timer.h"
#include <vector>
#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

extern bool min_max_before_info;
extern bool min_max_after_info;



void process(Channel &channel, int start_index, float ignore_perc, std::vector<unsigned char> &color_data){
    Timer tm;
    channel.load_colors(color_data, start_index, 3);
    tm.pinup(to_string(start_index) + " channel, load_colors");
    channel.find_ignore_colors(ignore_perc);
    tm.pinup(to_string(start_index) + " channel, find_ignore");
    channel.change_colors(color_data, start_index, 3);
    tm.pinup(to_string(start_index) + " channel, change_colors");
}

int perep(float new_value) {
    if (new_value < 0) {
        return 0;
    }
    if (new_value >= 255) {
        return 255;
    }
    if (new_value < 127) {
        return std::floor(new_value);
    } else {
        return std::ceil(new_value);
    }
}

int change_function(int value, int min, int max) {
    float new_value = value;
    if ((max - min) != 0) {
        new_value = (value - min) * (255 / (max - min));
    }
    return perep(new_value);
}

int find_min(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 0; i < 256; i++){
        sum += values[i];
        if (sum >= index_min){
            return i;
        }
    }
    return 0;
}

int find_max(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += values[i];
        if (sum >= index_min){
            return i;
        }
    }
    return 255;
}



std::vector<unsigned char> Ppm::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer tm;
    tm.pinup();

    std::vector<Channel> channels = {R, G, B};
//    process(channels[0], 0, ignore_perc, color_data);
    int color_map_r[256] = {0};
    int color_map_g[256] = {0};
    int color_map_b[256] = {0};
    for (int i = 0; i < color_data.size(); i += 3) {
        color_map_r[color_data[i]]++;
        color_map_g[color_data[i+1]]++;
        color_map_b[color_data[i+2]]++;
    }
//    for(int i : color_map) {
////        diagram[i] = change_function(i);
//        std::cout<< i << std::endl;
//    }

    auto index_min = (unsigned long long)((float)color_data.size()/3 * ignore_perc);
    cout << index_min << " " << color_data.size() << endl;
    int min_r = find_min(color_map_r, index_min);
    int min_g = find_min(color_map_g, index_min);
    int min_b = find_min(color_map_b, index_min);

    int max_r = find_max(color_map_r, index_min);
    int max_g = find_max(color_map_g, index_min);
    int max_b = find_max(color_map_b, index_min);

    int cur_min = min(min(min_r, min_g), min_b);
    int cur_max = max(max(max_r, max_g), max_b);
    cout << min_r << " " << min_g << " " << min_b << endl;
    cout << max_r << " " << max_g << " " << max_b << endl;

//    std::cout<< min_b<< " "<< max_b << std::endl;
    int diagram[256];
    for(int i = 1; i < 256; i++) {
        diagram[i] = change_function(i, cur_min, cur_max);
//        diagram_g[i] = change_function(i, min_g, cur_min, cur_max);
//        diagram_b[i] = change_function(i, min_b, cur_min, cur_max);
//        std::cout<< i<< " "<< diagram[i] << std::endl;
    }

    for (int i = 0; i < color_data.size(); i += 1) {
        color_data[i] = diagram[color_data[i]];
//        color_data[i+1] *= diagram[color_data[i+1]];
//        color_data[i+2] *= diagram[color_data[i+2]];
//        int next_b = diagram[prev_b];
//
//        color_data[i] = perep(color_data[i] * (next_b / prev_b));
    }

//#pragma omp parallel default(none) shared(channels, color_data, tm, ignore_perc)
//{
//    #pragma omp sections
//    {
//        #pragma omp section
//        {
//            int i = 0;
//            process(channels[i], i, ignore_perc, color_data);
//        }
//        #pragma omp section
//        {
//            int i = 1;
//            process(channels[i], i, ignore_perc, color_data);
//        }
//        #pragma omp section
//        {
//            int i = 2;
//            process(channels[i], i, ignore_perc, color_data);
//        }
//    };
//};
    if (min_max_before_info){
        channels[0].print_ignore_value("(R)");
        channels[1].print_ignore_value("(G)");
        channels[2].print_ignore_value("(B)");
    }

    tm.pinup("asd");

    if (min_max_after_info){
        cout << endl << "new min-max:" << endl;
        R = Channel();
        G = Channel();
        B = Channel();
        int s_pos = 0;
        for (Channel &channel: channels){
            channel.load_colors(color_data, s_pos, 3);
            tm.pinup(to_string(s_pos) + " channel, load_colors");
            channel.find_ignore_colors(0);
            tm.pinup(to_string(s_pos) + " channel, find_ignore");
            channel.change_colors(color_data, s_pos, 3);
            tm.pinup(to_string(s_pos) + " channel, change_colors");
            s_pos++;
        }
        channels[0].print_ignore_value("(R)");
        channels[1].print_ignore_value("(G)");
        channels[2].print_ignore_value("(B)");
    }


    return color_data;
}


