#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <filesystem>


#include "StringUtil.h"
#include "Tests.h"
#include "FileData.h"
#include "PatchData.h"
#include "HelperFoo.h"

namespace fs = std::filesystem;

// #define TEST_STRING_UTIL
// #define TEST_FILE_DATA
// #define TEST_PATCH_ADE
// #define DATE_TEST
#define NORMAL_OP


extern void PatchData_test();
extern void StringUtil_Test();
extern void FileData_test();
extern void FileName_test();

int main(int argc, char *argv[])
{

#ifdef TEST_STRING_UTIL
    StringUtil_Test();
#endif

#ifdef TEST_FILE_DATA
    FileData_test();
#endif

#ifdef TEST_PATCH_ADE
    PatchData_test();
#endif

#ifdef DATE_TEST
    FileName_test();
#endif


#ifdef NORMAL_OP

    std::string fname = hf::getFileName();
    fs::path executable_path = fs::absolute(fs::path(argv[0])).parent_path();
    fs::path data_directory = executable_path / "data";
    fs::path outFileCorrectPath = executable_path / fname;

    std::ofstream fout(outFileCorrectPath);
    std::vector<PatchData> files;

    if (!fout) {
        std::cout << "Could not open " << fname << std::endl;
        return 1;
    }

    // std::stringstream ss;
    // ss << fs::current_path() << "/data";
    // std::string path = ss.str(); 

    // fs::path p{"data"};

    // Get the path to the directory containing the executable

    // Construct the path to the "data" directory relative to the executable

    for (auto const& file : fs::directory_iterator{data_directory}) {
        std::cout << "Processing " << file.path() << std::endl;
        
        size_t found = std::string(file.path()).find("!2");
        if (found == std::string::npos) continue; // skip files that aren't recognized data files


        PatchData p(file.path());
        files.push_back(p);
        if (files.size() == 1) {
            p.printHeaders(&fout); 
            fout << std::endl;
        }
        fout << p;
    }
    std::cout << "\nFinished writing data to " << outFileCorrectPath << std::endl;

    fout.close();
    

#endif

    return 0;
}
