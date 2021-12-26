//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_PPM_H
#define AUTO_CONTRAST_OPENMP_PPM_H
#include <vector>
#include "Reader.h"
#include "Channel.h"

class Ppm {

public:
    std::vector<char> auto_contrast(std::vector<char> color_data, float ignore_perc);
private:
    Channel R;
    Channel G;
    Channel B;
};


#endif //AUTO_CONTRAST_OPENMP_PPM_H
