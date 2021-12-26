//
// Created by Phoenix on 25.12.2021.
//

#include "Ppm.h"
#include <vector>
#include "Timer.h"

using namespace std;

extern bool min_max_before_info;
extern bool min_max_after_info;

std::vector<unsigned char> Ppm::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer time;
    for(int pos = 0; pos < color_data.size() / 3; pos++){
        int current_step = pos * 3;
        R.add_pixel(color_data[current_step]);
        G.add_pixel(color_data[current_step + 1]);
        B.add_pixel(color_data[current_step + 2]);
    }
    time.pinup("decompose pixels into channels");

    R.find_ignore(ignore_perc);
    G.find_ignore(ignore_perc);
    B.find_ignore(ignore_perc);

    if (min_max_before_info){
        R.print_ignore_value("(R)");
        G.print_ignore_value("(G)");
        B.print_ignore_value("(B)");
    }
    time.pinup("find ignore value");

//    if(true) {
//        vector<unsigned char> color_data2;
//        R.change_colors();
//        G.change_colors();
//        B.change_colors();
//        for (int pos = 0; pos < color_data.size() / 3; pos++) {
//            color_data2.push_back(G.colors[pos]);
//        }
//        time.pinup("changed colors");
//        return color_data2;
//    }

    R.change_colors(color_data, 0, 3);
    G.change_colors(color_data, 1, 3);
    B.change_colors(color_data, 2, 3);
    time.pinup("changed colors");

    if (min_max_after_info){
        R = Channel();
        G = Channel();
        B = Channel();
        for(int pos = 0; pos < color_data.size() / 3; pos++){
            int current_step = pos * 3;
            R.add_pixel(color_data[current_step]);
            G.add_pixel(color_data[current_step + 1]);
            B.add_pixel(color_data[current_step + 2]);
        }
        R.find_ignore(0);
        G.find_ignore(0);
        B.find_ignore(0);

        R.print_ignore_value("(R)");
        G.print_ignore_value("(G)");
        B.print_ignore_value("(B)");
    }


    return color_data;
}


