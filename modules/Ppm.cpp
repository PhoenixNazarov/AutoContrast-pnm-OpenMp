//
// Created by Phoenix on 25.12.2021.
//

#include "Ppm.h"
#include "Timer.h"
#include <vector>
#include <iostream>

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

std::vector<unsigned char> Ppm::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer tm;
    std::vector<Channel> channels = {R, G, B};

#pragma omp parallel default(none) shared(channels, color_data, tm, ignore_perc)
{
    #pragma omp sections
    {
        #pragma omp section
        {
            int i = 0;
            process(channels[i], i, ignore_perc, color_data);
        }
        #pragma omp section
        {
            int i = 1;
            process(channels[i], i, ignore_perc, color_data);
        }
        #pragma omp section
        {
            int i = 2;
            process(channels[i], i, ignore_perc, color_data);
        }
    };
};
    if (min_max_before_info){
        channels[0].print_ignore_value("(R)");
        channels[1].print_ignore_value("(G)");
        channels[2].print_ignore_value("(B)");
    }

    tm.live();

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


