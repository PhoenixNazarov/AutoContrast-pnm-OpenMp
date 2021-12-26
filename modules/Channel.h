//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_CHANNEL_H
#define AUTO_CONTRAST_OPENMP_CHANNEL_H
#include <vector>
#include <string>
#include <map>

class Channel {
public:
    void load_colors(std::vector<unsigned char> &colors_data, int start_index, int step);
    void find_ignore_colors(float perc);
    void print_ignore_value(const std::string& channel_name);
    void change_colors(std::vector<unsigned char> &global_colors, int start_index, int step);
    std::vector<unsigned char> colors;
private:
    int ignore_lower;
    int ignore_higher;
    int color_map[256] = {0};
    int change_function(int value);
    unsigned long long size;
};


#endif //AUTO_CONTRAST_OPENMP_CHANNEL_H
