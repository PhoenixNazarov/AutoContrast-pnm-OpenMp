//
// Created by Phoenix on 25.12.2021.
//

#include "Channel.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

void Channel::load_colors(std::vector<unsigned char> &colors_data, int start_index, int step) {
    size = colors_data.size() / step;
    int nd = -1;
#pragma omp parallel for default(none) shared(colors_data, step, start_index)
    for (int i = start_index; i < colors_data.size(); i += step) {
        color_map[colors_data[i]]++;
    }
}

void Channel::print_ignore_value(const std::string& channel_name){
    std::cout << channel_name << " min: " << ignore_lower << ", max: " << ignore_higher << std::endl;
}

void Channel::find_ignore_colors(float perc) {
    auto index_min = (unsigned long long)((float)size * perc);

    int sum = 0;
    for (int i = 0; i <= 255; i++){
        sum += color_map[i];
        if (sum >= index_min){
            ignore_lower = i;
            break;
        }
    }

    sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += color_map[i];

        if (sum >= index_min){
            ignore_higher = i;
            break;
        }
    }
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
    int diagram[256];
    for(int i = 0; i <= 255; i++) {
        diagram[i] = change_function(i);
//        std::cout<< change_function(i) << std::endl;
    }

#pragma omp parallel for default(none) shared(global_colors, diagram, step, start_index)
    for (int i = start_index; i < global_colors.size(); i += step) {
        global_colors[i] = diagram[global_colors[i]];
    }
}
