//
// Created by Phoenix on 26.12.2021.
//

#include "Pgp.h"
#include <vector>
#include <iostream>
#include "Timer.h"

using namespace std;

extern bool min_max_before_info;
extern bool min_max_after_info;

vector<unsigned char> Pgp::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer time;
    Gray.colors = color_data;
    time.pinup("decompose pixels into channels");

    Gray.find_ignore(ignore_perc);

    if (min_max_before_info){
        Gray.print_ignore_value("(Gray)");
    }
    time.pinup("find ignore value");

    Gray.change_colors(color_data, 0, 1);
    time.pinup("changed colors");

    if (min_max_after_info) {
        cout << endl << "new min-max:" << endl;
        Gray = Channel();
        Gray.colors = color_data;
        Gray.find_ignore(0);
        Gray.print_ignore_value("(Gray)");
    }

    return color_data;
}

