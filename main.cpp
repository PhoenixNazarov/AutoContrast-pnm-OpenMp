#include <iostream>

#include "modules/FilesOperation.h"
#include "modules/Ppm.h"
#include "modules/Pgp.h"

#include <omp.h>
using namespace std;

// logging
bool data_info = false;
bool time_info = true;
bool min_max_before_info = false;
bool min_max_after_info = false;
int count_threads = 1;

int main() {
    string file = "10.pnm";
    string path_inp(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\incorrect\)");
    string path_out(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\output\)");

    path_inp += file;
    path_out += file;

    float ignore_perc = 0.1;
//    vector<unsigned char> after_contrast;

    FilesOperation data_image(path_inp);

    if (data_image.type == "P5") {
        Pgp matrix;
        matrix.auto_contrast(data_image.bytes, ignore_perc);
    } else if (data_image.type == "P6"){
        Ppm matrix;
        matrix.auto_contrast(data_image.bytes, ignore_perc);
    } else {
        cout << "Program Error";
        exit(70);
    }

    data_image.save_file(path_out);
    return 0;
}
