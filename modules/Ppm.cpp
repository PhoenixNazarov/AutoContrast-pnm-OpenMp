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
    float new_value = max;
    if (max != min) {
        new_value = (value - min) * (255 / (max - min));
    }
    return perep(new_value);
}

int find_min(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 0; i < 256; i++){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 0;
}

int find_max(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 255;
}

std::vector<unsigned char> Ppm::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer tm;
    int color_map_r[256] = {0};
    int color_map_g[256] = {0};
    int color_map_b[256] = {0};
    int i;
#pragma omp parallel for default(none) shared(color_map_r, color_map_g, color_map_b, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i += 3) {
        color_map_r[color_data[i]]++;
        color_map_g[color_data[i+1]]++;
        color_map_b[color_data[i+2]]++;
    }

    auto index_min = (unsigned long long)((float)color_data.size()/3 * ignore_perc);
    int min_r = find_min(color_map_r, index_min);
    int min_g = find_min(color_map_g, index_min);
    int min_b = find_min(color_map_b, index_min);

    int max_r = find_max(color_map_r, index_min);
    int max_g = find_max(color_map_g, index_min);
    int max_b = find_max(color_map_b, index_min);

    int cur_min = min(min(min_r, min_g), min_b);
    int cur_max = max(max(max_r, max_g), max_b);

    if (min_max_before_info) {
        cout << "(R) min: " << min_r << ", max: " << max_r << endl;
        cout << "(G) min: " << min_g << ", max: " << max_g << endl;
        cout << "(B) min: " << min_b << ", max: " << max_b << endl;
        cout << "(RGB) min: " << cur_min << ", max: " << cur_max << endl;
    }
    tm.pinup("find min max");


    int diagram[256] = {0};
    for(i = 1; i < 256; i++) {
        diagram[i] = change_function(i, cur_min, cur_max);
    }

#pragma omp parallel for default(none) shared(diagram, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i++) {
        color_data[i] = diagram[color_data[i]];
    }

    tm.pinup("change colors");

    return color_data;
}


