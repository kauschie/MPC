#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
enum pformat {single, comma};

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
    void readFile();

public:
    // vars
    MetaData meta;
    std::unordered_map<std::string, std::vector<std::string> > data;

    // foos
    FileData(std::string _fileName_ = "");
    void printData();
    void printMetaData(std::ofstream* fout = nullptr, pformat pf = single);
    void printMetaHeaders(std::ofstream* fout);

};
