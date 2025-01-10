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

#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <limits.h>
#endif

namespace fs = std::filesystem;


std::string getExecutableBasePath(char* argv0) {
#ifdef __APPLE__
    // macOS-specific code to get the path of the executable
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        std::string path(buffer);
        // Go up two levels to get to the parent directory of ADE.app
        return fs::path(path).parent_path().parent_path().parent_path().parent_path().string();
    } else {
        std::cerr << "Error getting executable path" << std::endl;
        return "";
    }
#else
    // For Linux, use argv[0] to get the executable path and its base directory
    return fs::absolute(argv0).parent_path().string();
#endif
}


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

    std::string basePath = getExecutableBasePath(argv[0]);
    fs::path baseDirectory(basePath);

    // Construct the paths for the data directory and output file
    fs::path data_directory = baseDirectory / "data";
    std::string fname = hf::getFileName();
    fs::path outFileCorrectPath = baseDirectory / fname;
    std::vector<PatchData> files;

    // Test writing to a file
    std::ofstream fout(outFileCorrectPath);
    if (!fout) {
        std::cout << "Could not open " << outFileCorrectPath.string() << std::endl;
    }

    std::cout << "Successfully opened " << outFileCorrectPath.string() << std::endl;


    // std::stringstream ss;
    // ss << fs::current_path() << "/data";
    // std::string path = ss.str(); 

    // fs::path p{"data"};

    // Get the path to the directory containing the executable

    // Construct the path to the "data" directory relative to the executable

    for (auto const& file : fs::directory_iterator{data_directory}) {
        std::cout << "Processing " << file.path() << std::endl;
        
        size_t found_type1 = std::string(file.path()).find("20");   // new datafile naming convention
        size_t found_type2 = std::string(file.path()).find("!2"); // old style datafile naming convention
        if (found_type1 == std::string::npos && found_type2 == std::string::npos) continue; // skip files that aren't recognized data files

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
