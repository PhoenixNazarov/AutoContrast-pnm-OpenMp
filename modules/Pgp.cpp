//
// Created by Phoenix on 26.12.2021.
//

#include "Pgp.h"
#include "MyMath.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

extern bool min_max_before_info;


vector<unsigned char> Pgp::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {

    int color_map[256] = {0};
    int i;
//#pragma omp parallel for default(none) shared(color_map, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i++) {
        color_map[color_data[i]]++;
    }

    auto index_min = (unsigned long long)((float)color_data.size() * ignore_perc);
    int cur_min = find_min(color_map, index_min);
    int cur_max = find_max(color_map, index_min);

    if (min_max_before_info) {
        cout << "(GRAY) min: " << cur_min << ", max: " << cur_max << endl;
    }

    int diagram[256] = {0};
    for(i = 1; i < 256; i++) {
        diagram[i] = change_function(i, cur_min, cur_max);
    }

#pragma omp parallel for default(none) shared(diagram, color_data) private(i) schedule(static)
    for (i = 0; i < color_data.size(); i++) {
        color_data[i] = diagram[color_data[i]];
    }


    return color_data;
}

