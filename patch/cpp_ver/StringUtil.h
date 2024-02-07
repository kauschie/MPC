#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace StringUtil
{
    bool isEmpty(const std::string & s);

    bool contains(const std::string& s, const std::string lookfor);

    std::vector<std::string> split(const std::string & s, char delim, bool skipEmpties = true, bool skipSpaces = true);

    std::string trim(const std::string & str);

    std::string lower(const std::string & str);

    std::string upper(const std::string & str);

    std::string clean(const std::string & str);
    
    void print_tokens(std::vector<std::string> tokens);

} // namespace StringUtil

