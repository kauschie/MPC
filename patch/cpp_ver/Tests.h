#pragma once
#include "StringUtil.h"
#include "FileData.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

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

}

void FileData_test()
{

    FileData rat1("data/!2024-02-07_07h13m.Subject Q53");

    std::cout << "filename: " << rat1.meta.file_name << std::endl;
    std::cout << "start_date: " << rat1.meta.start_date << std::endl;
    std::cout << "end_date: " << rat1.meta.end_date << std::endl;

    std::cout << "meta.rat_id: " << rat1.meta.rat_id << std::endl;
    std::cout << "meta.experiment: " << rat1.meta.experiment << std::endl;
    std::cout << "meta.group: " << rat1.meta.group << std::endl;
    std::cout << "meta.box: " << rat1.meta.box << std::endl;
    std::cout << "meta.start_time: " << rat1.meta.start_time << std::endl;
    std::cout << "meta.end_time: " << rat1.meta.end_time << std::endl;
    std::cout << "meta.program: " << rat1.meta.program << std::endl;
    rat1.printData();

}