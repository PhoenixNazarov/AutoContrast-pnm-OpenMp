//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_READER_H
#define AUTO_CONTRAST_OPENMP_READER_H


#include <string>
#include <vector>

class Reader {
public:
    Reader(const std::string& path);
    std::vector<unsigned char> header;
    std::string type; // "P5", "P6"
    int width{};
    int height{};
    int value{};
    std::vector<char> bytes;
private:
    int pos{};
    std::string read_to_sep(char sep);
};


#endif //AUTO_CONTRAST_OPENMP_READER_H
