//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_PPM_H
#define AUTO_CONTRAST_OPENMP_PPM_H
#include <vector>
#include "FilesOperation.h"
#include "Channel.h"

class Ppm {
public:
    std::vector<unsigned char> auto_contrast(std::vector<unsigned char> &color_data, float ignore_perc);
private:
    Channel R;
    Channel G;
    Channel B;
};


#endif //AUTO_CONTRAST_OPENMP_PPM_H
