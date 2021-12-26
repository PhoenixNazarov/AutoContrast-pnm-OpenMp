//
// Created by Phoenix on 25.12.2021.
//

#include "Ppm.h"
#include <vector>
#include <iostream>
#include "Timer.h"

using namespace std;

extern bool min_max_before_info;
extern bool min_max_after_info;
extern int count_threads;

std::vector<unsigned char> Ppm::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer time;
//    for (int pos = 0; pos < color_data.size() / 3; pos++) {
//        int current_step = pos * 3;
//        R.add_pixel(color_data[current_step]);
//        G.add_pixel(color_data[current_step + 1]);
//        B.add_pixel(color_data[current_step + 2]);
//    }



#pragma omp parallel num_threads(count_threads) default(none) shared(color_data, ignore_perc, std::cout)
    {
    #pragma omp sections
    {
        #pragma omp section
            {
                std::cout << "R.get_pixels start" << std::endl;
                R.get_pixels(color_data, 0, 3);
                std::cout << "R.find_ignore start" << std::endl;
                R.find_ignore(ignore_perc);
                R.change_colors(color_data, 0, 3);
                std::cout << "R end" << std::endl;
            }
//        #pragma omp section
//            {
//                std::cout << "G.get_pixels start" << std::endl;
//                G.get_pixels(color_data, 1, 3);
//                std::cout << "G.find_ignore start" << std::endl;
//                G.find_ignore(ignore_perc);
//                G.change_colors(color_data, 0, 3);
//                std::cout << "G end" << std::endl;
//            }
//        #pragma omp section
//            {
//                std::cout << "B.get_pixels start" << std::endl;
//                B.get_pixels(color_data, 2, 3);
//                std::cout << "B.find_ignore start" << std::endl;
//                B.find_ignore(ignore_perc);
//                B.change_colors(color_data, 0, 3);
//                std::cout << "B end" << std::endl;
//            }
    };
};
    time.pinup("decompose pixels into channels");

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

//    R.change_colors(color_data, 0, 3);
//    G.change_colors(color_data, 1, 3);
//    B.change_colors(color_data, 2, 3);
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


