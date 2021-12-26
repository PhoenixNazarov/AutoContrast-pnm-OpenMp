//
// Created by Phoenix on 26.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_TIMER_H
#define AUTO_CONTRAST_OPENMP_TIMER_H

#include <ctime>
#include <string>

class Timer {
private:
    int create_time;
    int last_time{};

public:
    Timer(){
        create_time = clock();
    }
    void pinup();
    void pinup(const std::string& message);
    void live();
};


#endif //AUTO_CONTRAST_OPENMP_TIMER_H
