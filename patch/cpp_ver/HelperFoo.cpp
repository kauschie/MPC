#include "HelperFoo.h"
#include <unordered_map>
#include <string>

/*
    Takes in an unordered map<std::string key, int val> and returns the sum
    of all of the values in the unordered map
*/
namespace hf 
{

    int getFreqSum(std::unordered_map<std::string, int> um) {
        int sum = 0;
        for (auto & m : um) {
            sum += m.second;
        }
        return sum;
    }

}