//
// Created by Phoenix on 25.12.2021.
//

#include "Ppm.h"
#include <vector>
#include <iostream>

using namespace std;

std::vector<char> Ppm::auto_contrast(std::vector<char> color_data, float ignore_perc) {
    std::vector<char> colors(color_data);
    for(int pos = 0; pos < color_data.size() / 3; pos++){
        int current_step = pos * 3;
        R.add_pixel(color_data[current_step]);
        G.add_pixel(color_data[current_step + 1]);
        B.add_pixel(color_data[current_step + 2]);
    }

    R.find_ignore(ignore_perc);
    G.find_ignore(ignore_perc);
    B.find_ignore(ignore_perc);

    R.change_colors(colors, 0, 3);
    G.change_colors(colors, 1, 3);
    B.change_colors(colors, 2, 3);

    return colors;
}
