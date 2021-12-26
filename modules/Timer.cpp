//
// Created by Phoenix on 26.12.2021.
//

#include "Timer.h"

#include <ctime>
#include <iostream>
#include <string>
#include <string_view>

extern bool time_info;

void Timer::pinup(){
    last_time = clock();
}

void Timer::pinup(const std::string& message){
    if (!time_info){
        return;
    }

    std::string t_d = std::to_string(clock() - last_time);
    if (t_d.size() >= 4){
        t_d.insert(t_d.size() - 3, ".");
    }

    while (t_d.size() < 6){
        t_d.insert(0, " ");
    }

    std::cout << "T_D: " << t_d << "s, " << message << std::endl;
    last_time = clock();
}

void Timer::live() {
    if (!time_info){
        return;
    }

    std::string t_d = std::to_string(clock() - create_time);
    if (t_d.size() >= 4){
        t_d.insert(t_d.size() - 3, ".");
    }

    while (t_d.size() < 6){
        t_d.insert(0, " ");
    }

    std::cout << "T_D: " << t_d << "s, " << "work all program" << std::endl;
}
