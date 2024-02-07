#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

struct MetaData {
    std::string file_name,
            start_date,
            end_date,
            start_time,
            end_time,
            program,
            rat_id;

    int experiment,
            group,
            box;
};


class FileData {

private:
    std::string fileName;
    std::ifstream fin;
    void readFile();

public:
    // vars
    MetaData meta;
    std::unordered_map<std::string, std::vector<float>> data;

    // foos
    FileData(std::string _fileName_ = "");
    void printData();


};