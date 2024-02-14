#pragma once
#include "FileData.h"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#define NUM_CVAR 7
#define NUM_DVAR 2
#define NUM_VALID_FILEFORMATS 1

class Timer {

    public:
        std::string start, end;
        Timer();
        Timer(std::string s, std::string n);
        float diff();
};

class PatchData : public FileData
{
    private:
        static std::string validFileFormats[NUM_VALID_FILEFORMATS];
        static int DATA_START_INDEX;
        static std::string cvar_array;
        static std::string dvar_array;

        static std::string cvar_names[NUM_CVAR];
        static int cvar_indices[NUM_CVAR];
        static std::string dvar_names[NUM_DVAR];
        static int dvar_indices[NUM_DVAR];

        // private member vars
        bool beginData = false;
       std::string findLastOccurrence(int idx, std::string wd_id);


        // private member functions
        void analyze();

    public:
        // member vars
        std::unordered_map<std::string, std::string> cvars;
        std::unordered_map<std::string, std::string> dvars;
        std::unordered_map<std::string, int> rewards;
        std::unordered_map<std::string, int> rejectVols;
        std::unordered_map<std::string, int> consumedVols;
        std::unordered_map<std::string, int> leftRewards;
        std::unordered_map<std::string, int> rightRewards;
        std::vector<float> travelTimes, timeList;
        std::vector<std::string> nullChanges;
        int leftPokes, rightPokes;
        
        // member functions
        PatchData(std::string _filename_);
        
        




};