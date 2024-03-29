#include "HelperFoo.h"
#include <unordered_map>
#include <string>
#include <vector>

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

    float getFreqSum(std::unordered_map<std::string, float> um) {
        float sum = 0;
        for (auto & m : um) {
            sum += m.second;
        }
        return sum;
    }

    float getVecSum(std::vector<float> v) {
        float sum = 0;
        for (auto && ele : v) {
            sum += ele;
        }
        return sum;
    }

    std::string getFileName()
    {
        time_t now = time(NULL);
        std::tm * timeinfo;
        char buf[180];
        timeinfo = localtime(&now);

        strftime(buf, 180, "%y%m%d%H%M%S_patchdata.csv", timeinfo);
        // std::cout << buf << std::endl;

        return std::string(buf);
    }


}