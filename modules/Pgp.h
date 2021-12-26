//
// Created by Phoenix on 26.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_PGP_H
#define AUTO_CONTRAST_OPENMP_PGP_H
#include <vector>
#include "FilesOperation.h"
#include "Channel.h"

class Pgp {
public:
    std::vector<unsigned char> auto_contrast(std::vector<unsigned char> &color_data, float ignore_perc);
private:
    Channel Gray;
};


#endif //AUTO_CONTRAST_OPENMP_PGP_H
