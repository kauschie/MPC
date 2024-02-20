#pragma once
#include <string>
#include <unordered_map>
#include <ctime>

namespace hf 
{
    int getFreqSum(std::unordered_map<std::string, int> um);
    float getFreqSum(std::unordered_map<std::string, float> um);

    std::string getFileName();

}
