#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include "modules/Ppm.h"
#include "modules/Reader.h"

using namespace std;

void save_file(const string& path, vector<unsigned char> header, vector<unsigned char> data){
    ofstream out(path, ios::binary);
    for(unsigned char symb: header){
        out.write((char*) &symb, sizeof(symb));
    }
    for(unsigned char symb: data){
        out.write((char*) &symb, sizeof(symb));
    }
    out.close();
}


int main() {
    string file = "photo_2021-12-25_17-02-47.pnm";
//    string path_inp(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\input\)");
//    string path_out(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\output\)");

    string path_out(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\input\)");
    string path_inp(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\output\)");


    path_inp += file;
    path_out += file;

    float ignore_perc = 0;
    vector<unsigned char> after_contrast;

    Reader data_image(path_inp);

    cout<< "size: " << data_image.bytes.size() << endl;
    if (data_image.type == "P5") {

    } else if (data_image.type == "P6"){
        Ppm matrix;
        after_contrast = matrix.auto_contrast(data_image.bytes, ignore_perc);
        matrix.auto_contrast(data_image, ignore_perc);
    } else {
        cout << "Program Error";
        exit(70);
    }
    cout<< "size: " << after_contrast.size();
//    save_file(path_out, data_image.header, after_contrast);
    return 0;
}


//ignore: 0 204
//ignore: 0 197
//ignore: 0 199