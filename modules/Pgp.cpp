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
extern int count_threads;

vector<unsigned char> Pgp::auto_contrast(vector<unsigned char> &color_data, float ignore_perc) {
    Timer time;

    std::vector<Channel> channels = {Gray};
    int s_pos = 0;
    for (Channel &channel: channels){
        channel.load_colors(color_data, s_pos, 1);
        time.pinup(to_string(s_pos) + " channel, load_colors");
        channel.find_ignore_colors(ignore_perc);
        time.pinup(to_string(s_pos) + " channel, find_ignore");
        channel.change_colors(color_data, s_pos, 1);
        time.pinup(to_string(s_pos) + " channel, change_colors");
        s_pos++;
    }
    if (min_max_before_info){
        channels[0].print_ignore_value("(Gray)");
    }
    time.live();

    if (min_max_after_info) {
        cout << endl << "new min-max:" << endl;
        Gray = Channel();
        Gray.colors = color_data;
        Gray.find_ignore_colors(0);
        Gray.print_ignore_value("(Gray)");
    }

    return color_data;
}

