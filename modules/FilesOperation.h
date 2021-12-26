//
// Created by Phoenix on 25.12.2021.
//

#ifndef AUTO_CONTRAST_OPENMP_FILESOPERATION_H
#define AUTO_CONTRAST_OPENMP_FILESOPERATION_H


#include <string>
#include <vector>

class FilesOperation {
public:
    explicit FilesOperation(std::string& path);
    void save_file(const std::string& path);
    void save_file(const std::string& path, const std::vector<unsigned char> &data);
    std::vector<unsigned char> header;
    std::string type; // "P5", "P6"
    int width{};
    int height{};
    int value{};
    std::vector<unsigned char> bytes;
private:
    int pos{};
    std::string read_to_sep(char sep);
};


#endif //AUTO_CONTRAST_OPENMP_FILESOPERATION_H
