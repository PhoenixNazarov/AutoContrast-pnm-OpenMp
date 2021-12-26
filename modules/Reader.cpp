//
// Created by Phoenix on 25.12.2021.
//
#include <chrono>
#include <iostream>
#include <fstream>
#include <ctime>

#include "Reader.h"

using namespace std;

Reader::Reader(const string& path){
//    clock_t time;
//    time = clock();
    int start_time = clock();
    ifstream input(path, ios::binary);
    bytes = vector(
            (istreambuf_iterator<char>(input)),
            (istreambuf_iterator<char>()));
    input.close();
//    time = clock() - time;
//    cout << static_cast<float>(time)/CLOCKS_PER_SEC <<endl;
    unsigned int end_time = clock();
    cout <<  end_time - start_time << endl;
    pos = -1;
    int channel = 0;
    type = read_to_sep('\n');
    if (type == "P5"){
        cout << "Current format: P5(PGM)" << endl;
        channel = 1;
    }
    else if (type == "P6"){
        cout << "Current format: P6(PPM)" << endl;
        channel = 3;
    }
    else {
        cout << "Data format error: " << type;
        exit(65);
    }

    // read width, height, value
    width = stoi(read_to_sep(' '));
    height = stoi(read_to_sep('\n'));
    value = stoi(read_to_sep('\n'));
    cout << "Size: " << width << "x" << height << endl;
    cout << "Max value: " << value << endl;

    header.assign(bytes.begin(), bytes.begin() + pos + 1);
    bytes.erase(bytes.begin(), bytes.begin() + pos + 1);
    if (bytes.size() != width * height * channel) {
        cout << "Error: Gray_data/RGB_data size does not match width*height" << endl;
        cout << "   Expected size: " << width * height * channel << endl;
        cout << "   Current size:  " << bytes.size() << endl;
        exit(65);
    }
//    for (int i=0; i<20; i++){
//        int a = (unsigned char) bytes[i];
//        cout << a << endl;
//    }
}


string Reader::read_to_sep(char sep) {
    string buf;
    while (bytes[++pos] != sep){
        buf += bytes[pos];
    }
    return buf;
}
