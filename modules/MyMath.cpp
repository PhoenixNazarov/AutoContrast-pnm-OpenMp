//
// Created by Phoenix on 05.01.2022.
//

#include <cmath>
#include "MyMath.h"


int perep(float value) {
    if (value < 0) {
        return 0;
    }
    if (value >= 255) {
        return 255;
    }
    return std::floor(value);
}

int change_function(int value, int min, int max) {
    return perep( (value - min) * (255.0 / (max - min)));
}

int find_min(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 0; i < 256; i++){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 0;
}

int find_max(const int values[], unsigned long long index_min){
    unsigned long long sum = 0;
    for (int i = 255; i >= 0; i--){
        sum += values[i];
        if (sum > index_min){
            return i;
        }
    }
    return 255;
}