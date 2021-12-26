//
// Created by Phoenix on 25.12.2021.
//

#include "Channel.h"
#include <iostream>
#include <vector>
#include <vector>
#include <map>
#include <string>
#include <math.h>

extern int count_threads;

void Channel::add_pixel(unsigned char color) {
    colors.push_back(color);
}

#pragma omp declare reduction (merge : std::vector<unsigned char> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))


void Channel::get_pixels(std::vector<unsigned char> &colors_data, int start_index, int step) {
    std::vector<int> vec_private;
#pragma omp parallel for schedule(static)
    for (int i = start_index; i < colors_data.size(); i+=step) {
        colors.push_back(colors_data[i]);
        color_map.at(colors_data[i])++;
    }
    std::cout << "ebd  "<< colors.size() << std::endl;
}

void Channel::print_ignore_value(const std::string& channel_name){
    std::cout << channel_name << " min: " << ignore_lower << ", max: " << ignore_higher << std::endl;
}

bool higher_comp (int i,int j) { return (i>j); }


void Channel::find_ignore(float perc) {
    std:: cout<<"what " << colors.size() << std::endl;
//    for(int i = 100; i <= 110; i++){
//        std::cout<< i << ' ' << color_map.at(i) << std::endl;
//    }
    auto index_min = (unsigned long long)((float)colors.size() * perc);

    int sum = 0;
    for (int i = 0; i <= 255; i++){
        sum += color_map.at(i);
        if (sum >= index_min){
            ignore_lower = i;
            break;
        }
    }

    sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += color_map.at(i);
        if (sum >= index_min){
            ignore_higher = i;
            break;
        }
    }


//    bool end = false;
//
//    for (int i = 0; i <= 255; i++) {
//        if (end) { break; }
//#pragma omp parallel default(none) shared(sum, index_min, i, end) num_threads(count_threads)
//        {
//#pragma omp for
//            for (unsigned char a: colors) {
//                if (i == a) {
//                    sum++;
//                }
//            }
//#pragma omp barrier
//            if (sum >= index_min) {
//                ignore_lower = i;
//                end = true;
//            }
//        };
//    }
//
//    sum = 0;
//    end = false;
//    for (int i = 255; i >= 0; i--) {
//        if (end) { break; }
//#pragma omp parallel default(none) shared(sum, index_min, i, end) num_threads(count_threads)
//        {
//#pragma omp for
//            for (unsigned char a: colors) {
//                if (i == a) {
//                    sum++;
//                }
//            }
//#pragma omp barrier
//            if (sum >= index_min) {
//                ignore_higher = i;
//                end = true;
//            }
//        };
//    }
//    auto index_min = (unsigned long long)((float)colors.size() * perc);
//
//    std::nth_element(colors.begin(), colors.begin()+index_min, colors.end());
//    ignore_lower = colors[index_min];
//
//    std::nth_element( colors.begin(), colors.begin()+index_min, colors.end(), higher_comp);
//    ignore_higher = colors[index_min];
}

int Channel::change_function(int value) {
    double new_value = value;
    if ((ignore_higher - ignore_lower) != 0) {
        new_value = (value - ignore_lower) * (255.0 / (ignore_higher - ignore_lower));
    }

    if (new_value < 0){
        return 0;
    }
    if (new_value > 255){
        return 255;
    }
    if (new_value < 127.5){
        return floor(new_value);
    } else {
        return ceil(new_value);
    }

}

void Channel::change_colors(std::vector<unsigned char> &global_colors, int start_index, int step) {
    std::map<int, int> diagram;
    for(int i = 0; i <= 255; i++){
        diagram.insert(std::make_pair(i, change_function(i)));
    }

    #pragma omp parallel for default(none) shared(global_colors, diagram, step, start_index) num_threads(count_threads)
    for (int i = start_index; i < global_colors.size(); i += step) {
        global_colors[i] = diagram.at(global_colors[i]);
    }
}


void Channel::change_colors() {
    std::map<int, int> diagram;
    for(int i = 0; i <= 255; i++){
        diagram.insert(std::make_pair(i, change_function(i)));
    }

    for (unsigned char a: colors){
        a = diagram.at(a);
    }
}


