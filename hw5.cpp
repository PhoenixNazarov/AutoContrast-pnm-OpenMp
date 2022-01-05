#include <iostream>
#include <omp.h>
#include <ctime>

#include "modules/FilesOperation.h"
#include "modules/Ppm.h"
#include "modules/Pgp.h"

using namespace std;

// logging
bool data_info = false;
bool min_max_before_info = false;

int main(int argc, char* argv[]) {
    int count_threads = atoi(argv[1]);
    string path_inp(argv[2]);
    string path_out(argv[3]);
    float ignore_perc = atof(argv[4]);
    FilesOperation data_image;
    try {
        data_image.open_file(path_inp);
    }
    catch (exception& e){
        cout << "Error: cant open file: " << e.what();
        exit(70);
    }

    int time = clock();
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
    std::cout << "Time (" << count_threads <<" thread(s)): " << clock() - time << " ms\n";

    data_image.save_file(path_out);
    return 0;
}
