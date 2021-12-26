//
// Created by Phoenix on 25.12.2021.
//
#include <iostream>
#include <fstream>

#include "FilesOperation.h"
#include "Timer.h"

using namespace std;

extern bool data_info;

std::vector<unsigned char> readFile(const string& filename)
{
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

FilesOperation::FilesOperation(string& path){
    Timer timer;
    pos = -1;
    int channel = 0;
    bytes = readFile(path);
    timer.pinup("open file");

    if (bytes.empty()){
        cout << "Error: file not read";
        exit(65);
    }

    type = read_to_sep('\n');
    if (type == "P5"){
        if (data_info){cout << "Current format: P5(PGM)" << endl;}
        channel = 1;
    }
    else if (type == "P6"){
        if (data_info){cout << "Current format: P6(PPM)" << endl;}
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
    if (data_info) {
        cout << "Size: " << width << "x" << height << endl;
        cout << "Max value: " << value << endl;
    }
    header.assign(bytes.begin(), bytes.begin() + pos + 1);
    bytes.erase(bytes.begin(), bytes.begin() + pos + 1);
    if (bytes.size() != width * height * channel) {
        cout << "Error: Gray_data/RGB_data size does not match width*height" << endl;
        cout << "   Expected size: " << width * height * channel << endl;
        cout << "   Current size:  " << bytes.size() << endl;
        exit(65);
    }
    timer.pinup("parse file");
}


string FilesOperation::read_to_sep(char sep) {
    string buf;
    while (bytes[++pos] != sep){
        buf += bytes[pos];
    }
    return buf;
}

void FilesOperation::save_file(const string &path) {
    ofstream out(path, ios::binary);
    for(unsigned char symb: header){
        out.write((char*) &symb, sizeof(symb));
    }
    for(unsigned char symb: bytes){
        out.write((char*) &symb, sizeof(symb));
    }
    out.close();
}

void FilesOperation::save_file(const std::string& path, const std::vector<unsigned char> &data) {
    ofstream out(path, ios::binary);
    for(unsigned char symb: header){
        out.write((char*) &symb, sizeof(symb));
    }
    for(unsigned char symb: data){
        out.write((char*) &symb, sizeof(symb));
    }
    out.close();
}
