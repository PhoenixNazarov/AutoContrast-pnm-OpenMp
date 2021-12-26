//
// Created by Phoenix on 25.12.2021.
//

#include "Channel.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <cmath>

void Channel::add_pixel(char color) {
    if (color < min){
        min = color;
    }
    if (color > max){
        max = color;
    }

    colors.push_back(color);
}


bool higher_comp (int i,int j) { return (i>j); }

void Channel::find_ignore(float perc) {

    auto index_min = (unsigned long long)((float)colors.size() * perc);
    std::nth_element( colors.begin(), colors.begin()+index_min, colors.end());
    ignore_lower = colors[index_min];

    std::nth_element( colors.begin(), colors.begin()+index_min, colors.end(), higher_comp);
    ignore_higher = colors[index_min];
    std::cout << "ignore: " << ignore_lower << ' ' << ignore_higher << std::endl;
}

int Channel::change_function(int value) {
    int new_value = (value - ignore_lower) * (255 / (ignore_higher - ignore_lower));
    if (new_value < 0){
        return 0;
    }
    if (new_value > 255){
        return 255;
    }
    return new_value;
}

void Channel::change_colors(std::vector<char> &colors, int start_index, int step) {
    std::map<int, int> diagram;
    for(int i = 0; i <= 255; i++){
        diagram.insert(std::make_pair(i, change_function(i)));
    }

//    for (unsigned char a: colors){
//        a = diagram.at(a);
//    }

    for (int i = start_index; i < colors.size(); i++){
        if ((i % step) == start_index){
//            std::cout << i << ' ' << start_index << std::endl;
            colors[i] = diagram.at(colors[i]);
        }
    }
}

