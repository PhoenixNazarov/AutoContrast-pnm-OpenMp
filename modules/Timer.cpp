//
// Created by Phoenix on 26.12.2021.
//

#include "Timer.h"

#include <ctime>
#include <string>
#include <iostream>

void Timer::pinup(){
    last_time = clock();
}

void Timer::pinup(const std::string& message){
    std::cout << message << ' ' << clock() - last_time << "ms" << std::endl;
    last_time = clock();
}
