#include "FileData.h"
#include <fstream>
#include <iostream>
#include "StringUtil.h"
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>

// enum pformat {single, comma};

// #define DEBUG

FileData::FileData(std::string _fileName_)
    : fileName(_fileName_)
{
    readFile();
}

void FileData::readFile()
{
    std::ifstream fin;
    try
    {
        fin.open(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Unable to open file << " << fileName << " >>" << std::endl;
        exit(1);
    }




    int i = 1;

    // for metadata
    std::string line, first_dig;
    std::vector<std::string> words;
    std::vector<std::string> pieces;

    // for data
    bool arrayFlag = false;
    std::string array_char;
    std::vector<std::string> array_data;


    while(getline(fin, line)) {


        words.clear();
        words = StringUtil::split(line, ':');

#ifdef DEBUG
        std::cout << "\t* i: " << i << " *\n";
        StringUtil::print_tokens(words);
        std::cout << "words.size(): " << words.size() << std::endl;
#endif

        if (!words.size()) continue;

        switch (i++)
        {
            case 1:
                meta.file_name = line.substr(6, line.length() - 6 - 1);
                break;

            case 2:
                pieces.clear();
                pieces = StringUtil::split(words[2], '/');
                meta.start_date = "20" + pieces[2] + "-" + pieces[0] + "-" + pieces[1];
                break;

            case 3:
                pieces.clear();
                pieces = StringUtil::split(words[2], '/');
                meta.end_date = "20" + pieces[2] + "-" + pieces[0] + "-" + pieces[1];
                break;

            case 4:
                meta.rat_id = line.substr(9, line.length() - 9 - 1);
                break;

            case 5:
                meta.experiment = std::stoi(line.substr(12));
                break;

            case 6:
                meta.group = std::stoi(line.substr(7));
                break;

            case 7:
                meta.box = std::stoi(words[1]);
                break;

            case 8:
                first_dig = (words[2].size() == 1 ? ("0"+words[2]) : words[2]);
                meta.start_time = first_dig + ":" + words[3] + ":" + words[4]; 
                break;

            case 9:
                first_dig = (words[2].size() == 1 ? ("0"+words[2]) : words[2]);
                meta.end_time = first_dig + ":" + words[3] + ":" + words[4]; 
                // meta.end_time = words[2];
                break;

            case 10:
                meta.program = line.substr(5, line.length() - 5 - 1);
                break;

            default:

                if (words.size() == 2 && !arrayFlag) {
                    // old
                    // if (isalpha(words[0][0]) && !arrayFlag) {
                    // line starts with a letter and we havent hit the arrays yet

                    array_char = words[0][0];

                    array_data.clear();
                    // array_data.push_back(atof(words[1].c_str()));
                    array_data.push_back(words[1]);

                    data[array_char] = array_data;

                } else if (words.size() == 1) {
                    // found an array
                    if (!arrayFlag) {
                        arrayFlag = true;
                    } else {
                        // write the previous array to the map
                        // std::cout << "time for a new array" << std::endl;
                        data[array_char] = array_data;
                        // clear for next array
                        array_data.clear();
                    }
                    array_char = words[0][0];
                } else if (words.size() > 1 && isdigit(words[0][0])) {
                    // push floats onto the vec
                    for (auto it = words.begin()+1; it != words.end(); it++) {
                        // array_data.push_back(atof((*it).c_str()));
                        array_data.push_back(*it);
                    }

                }



                break;
                }
        }

        data[array_char] = array_data;


    }

    void FileData::printData()
    {
        std::cout << "*************     ^^^^^     ***************" << std::endl;
        std::cout << "              Printing Data                " << std::endl;
        std::cout << "*************     ^^^^^     ***************" << std::endl << std::endl;

        for (auto & m : data) {

            std::cout << std::endl << m.first << ": ";
            if (m.second.size() > 1) {
                std::cout << "\n\t";
                int count = 1;
                for (auto & num : m.second) {
                    std::cout << std::setw(12) << num << " ";
                    if (count++ % 5 == 0) std::cout << "\n\t";
                }
            } else {
                if (m.second.size() > 0)
                    std::cout << m.second[0];
            }
            // std::cout << "Finished with " << m.first << std::endl;
        }
        std::cout << std::endl;

        // std::cout << "Finished print" << std::endl;
    }

    void FileData::printMetaHeaders(std::ofstream* fout)
    {
        std::vector<std::string> names = {"Filename", "Start Date", "End Date", 
                                        "Rat ID", "Experiment", "Group", "Box", 
                                        "Start Time", "End Time", "Program"};

        for (auto it = names.begin(); it != names.end(); ++it) {
            *fout << *it << ", ";
        }

    }

    void FileData::printMetaData(std::ofstream* fout, pformat pf)
    {

        std::vector<std::string> names = {"Filename", "Start Date", "End Date", 
                                        "Rat ID", "Experiment", "Group", "Box", 
                                        "Start Time", "End Time", "Program"};

        std::vector<std::string> vals = {meta.file_name, meta.start_date, meta.end_date,
            meta.rat_id, std::to_string(meta.experiment), std::to_string(meta.group),
            std::to_string(meta.box), meta.start_time, meta.end_time, meta.program};

        // std::cout << "in printMetaData, pf: " << (pf == single) << std::endl;

        if (pf == single) {

            std::cout << "*************     ^^^^^     ***************" << std::endl;
            std::cout << "                 MetaData                  " << std::endl;
            std::cout << "*************     ^^^^^     ***************" << std::endl << std::endl;


            for (int i = 0; i < names.size(); i++) {
                StringUtil::prettyWrite(names[i], vals[i]);
            }

        } else if (pf == comma) {
            // print format is 

            for (int i = 0; i < vals.size(); i++) {
                *fout << vals[i] << ", ";
            }
        }
    }
