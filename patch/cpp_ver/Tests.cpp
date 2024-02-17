#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

#include "StringUtil.h"
#include "FileData.h"
#include "PatchData.h"
#include "Tests.h"
#include "HelperFoo.h"

// #define DEBUG 


void StringUtil_Test()
{

    std::string line = "    A     25     ";
    std::string empt = "";
    std::vector<std::string> tokens;
    std::string line1 = "V:       0.000";
    std::string line2 = "5:        1.000        2.500        3.330        4.F00        5.001";


    // unit tests for functions in StringUtil
    std::cout << "empt: " << empt << std::endl;
    std::cout << "empt is empty: " << std::boolalpha << StringUtil::isEmpty(empt) << std::endl;
    std::cout << "empt is contains A: " << std::boolalpha << StringUtil::contains(empt, "A") << std::endl;

    std::cout << "line: " << line << std::endl;
    std::cout << "line is empty: " << std::boolalpha << StringUtil::isEmpty(line) << std::endl;
    std::cout << "line is contains A: " << std::boolalpha << StringUtil::contains(line, "A") << std::endl;
    

    tokens = StringUtil::split(line1, ':');
    std::cout << "line1 tokens:\n";
    StringUtil::print_tokens(tokens);
    std::cout << "Number of line1 tokens: " << tokens.size() << std::endl;
    
    std::cout << "testing lower on tokens: ";
    for (auto & tok : tokens) {
        tok = StringUtil::lower(tok);
        std::cout << tok << " ";
    }
    std::cout << "\nTesting upper on tokens: ";
    for (auto & tok : tokens) {
        tok = StringUtil::upper(tok);
        std::cout << tok << " ";
    }
    std::cout << std::endl;


    tokens.clear();
    tokens = StringUtil::split(line2, ':');
    std::cout << "line2 tokens:\n";
    StringUtil::print_tokens(tokens);
    std::cout << "Number of line2 tokens: " << tokens.size() << std::endl;

    std::cout << "testing lower on tokens: ";
    for (auto & tok : tokens) {
        tok = StringUtil::lower(tok);
        std::cout << tok << " ";
    }

    std::cout << "\nTesting upper on tokens: ";
    for (auto & tok : tokens) {
        tok = StringUtil::upper(tok);
        std::cout << tok << " ";
    }
    std::cout << std::endl;

    tokens.clear();
    tokens = StringUtil::split(line2, ':', true, false);
    std::cout << "line2 tokens without split:\n";
    StringUtil::print_tokens(tokens);
    std::cout << "Number of line2 tokens without delim spaces: " << tokens.size() << std::endl;


    std::vector<float> nums = {1, 23.5, 256.66666666, -5.768};
    for (auto & num : nums) {
        std::cout << StringUtil::makeVecStrNum(num)[0] << ' ';
    }
    std::cout << std::endl;

    std::vector<int> nums2 = {6, 7, 8, 9, 10};
    for (auto & num : nums2) {
        std::cout << StringUtil::makeVecStrNum(num)[0] << ' ';
    }
    std::cout << std::endl;


    std::unordered_map<std::string, int> um;
    um["nums1"] = 5;
    um["nums2"] = 10;
    um["nums3"] = 15;

    std::cout << std::endl << "Printing some nums in a unordered map:\n\t";
    for (auto & m : um) {
        std::cout << m.first << ": " << m.second << "\n\t";
    }
    std::cout << "Sum: " <<  hf::getFreqSum(um) << std::endl;



}

void FileData_test()
{

    FileData rat1("../testdata/!2024-02-07_07h13m.Subject Q53");

    rat1.printMetaData();
    rat1.printData();

}

void PatchData_test()
{
    // all of the FileData functionality should still work
    PatchData rat1("../testdata/!2024-02-16_07h16m.Subject Q53");
   
#ifdef DEBUG
    rat1.printData();
#endif // DEBUG


    // test PatchData functionality


    rat1.printMetaData(nullptr, single);
    rat1.printCvars(nullptr, single);
    rat1.printDvars(nullptr, single);
    
    
}