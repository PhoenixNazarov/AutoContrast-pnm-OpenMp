#include <iostream>
#include <omp.h>

#include "modules/FilesOperation.h"
#include "modules/Ppm.h"
#include "modules/Pgp.h"
#include "modules/Timer.h"

using namespace std;

// logging
bool data_info = false;
bool time_info = true;
bool min_max_before_info = true;
bool min_max_after_info = false;

int main() {
    Timer timer;
    omp_set_num_threads(20);
    string file = "photo_2021-12-25_17-02-47.pnm";
    string path_inp(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\input\)");
    string path_out(R"(C:\Users\Phoenix\CLionProjects\auto_contrast_OpenMp\test\output\)");

    path_inp += file;
    path_out += file;
    float ignore_perc = 0.0;
    FilesOperation data_image;
    try {
        data_image.open_file(path_inp);
    }
    catch (exception& e){
        cout << "Error: cant open file: " << e.what();
        exit(70);
    }
    if (data_image.type == "P5") {
        Pgp matrix;
        matrix.auto_contrast(data_image.bytes, ignore_perc);
    } else if (data_image.type == "P6") {
        Ppm matrix;
        matrix.auto_contrast(data_image.bytes, ignore_perc);
    } else {
        cout << "Program Error";
        exit(70);
    }
    timer.pinup();
    data_image.save_file(path_out);
    timer.pinup("save file");
    timer.live();
    return 0;
}
