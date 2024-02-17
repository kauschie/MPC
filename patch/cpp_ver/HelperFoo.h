#pragma once
#include <string>
#include <unordered_map>

namespace hf 
{
    int getFreqSum(std::unordered_map<std::string, int> um);
    float getFreqSum(std::unordered_map<std::string, float> um);
}
