//
// Created by Phoenix on 26.12.2021.
//

#include "Pgp.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "Timer.h"

using namespace std;

extern bool min_max_before_info;

// it is my first program on c++ and I dont know, how I need define functions from ppm.cpp with one names
int perep1(float new_value) {
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

int change_function1(int value, int min, int max) {
    float new_value = max;
    if (max != min) {
        new_value = (value - min) * (255 / (max - min));
    }
    return perep1(new_value);
}

int find_min1(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 0; i < 256; i++){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 0;
}

int find_max1(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 255;
}
vector<unsigned char> Pgp::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer tm;

    int color_map[256] = {0};
    int i;
#pragma omp parallel for default(none) shared(color_map, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i++) {
        color_map[color_data[i]]++;
    }

    auto index_min = (unsigned long long)((float)color_data.size() * ignore_perc);
    int cur_min = find_min1(color_map, index_min);
    int cur_max = find_max1(color_map, index_min);

    if (min_max_before_info) {
        cout << "(GRAY) min: " << cur_min << ", max: " << cur_max << endl;
    }
    tm.pinup("find min max");

    int diagram[256] = {0};
    for(i = 1; i < 256; i++) {
        diagram[i] = change_function1(i, cur_min, cur_max);
    }

#pragma omp parallel for default(none) shared(diagram, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i++) {
        color_data[i] = diagram[color_data[i]];
    }

    tm.pinup("change colors");


    return color_data;
}

