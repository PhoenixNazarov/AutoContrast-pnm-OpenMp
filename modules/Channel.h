//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_CHANNEL_H
#define AUTO_CONTRAST_OPENMP_CHANNEL_H
#include <vector>
#include <string>

class Channel {
public:
    void add_pixel(unsigned char &color);
    void find_ignore(float perc);
    void print_ignore_value(const std::string& channel_name);
    void change_colors(std::vector<unsigned char> &colors, int start_index, int step);
    void change_colors();
    std::vector<unsigned char> colors;
private:
    int ignore_lower;
    int ignore_higher;
    int change_function(int value);
};


#endif //AUTO_CONTRAST_OPENMP_CHANNEL_H
