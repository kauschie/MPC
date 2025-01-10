#pragma once
#include <string>
#include <unordered_map>
#include <ctime>
#include <vector>

namespace hf 
{
    int getFreqSum(std::unordered_map<std::string, int> um);
    float getFreqSum(std::unordered_map<std::string, float> um);

    std::string getFileName();

    float getVecSum(std::vector<float> v);


}
