#include "PatchData.h"
#include "StringUtil.h"
#include <string>
#include <bits/stdc++.h>


/************************
 * 
 * Timer Class
 * 
************************/


// constructors
Timer::Timer() : start(""), end("") {}
Timer::Timer(std::string s, std::string n) : start(s), end(s) {}


// returns float val of end-start
float Timer::diff()
{
    return std::atof(end.c_str())-std::atof(start.c_str());
}


/************************
 * 
 * PatchData Class
 * 
************************/

PatchData::PatchData(std::string _filename_) : FileData(_filename_)
{
    // grab specific vars from control variables (usually A array)
    for (int i = 0; i < NUM_CVAR; i++) {
        cvars[cvar_names[i]] = data[cvar_array][cvar_indices[i]];
    }

    // grab specific vars from dependent vars (Located in C array (mark) or the B array (mike))
    for (int i = 0; i < NUM_DVAR; i++) {
        dvars[dvar_names[i]] = data[dvar_array][dvar_indices[i]];
    }

    analyze();
}

// finds last occurance of wd_id in the data vector starting at idx and iterating backwards
std::string PatchData::findLastOccurrence(int idx, std::string wd_id) {
    auto rit = data[dvar_array].crbegin() + idx;
    auto rend = data[dvar_array].crend();

    while (rit != rend) {
        if (*rit == wd_id) {
            // Check if it's not the last element
            auto next_rit = rit + 1;
            if (next_rit != data[dvar_array].crend())
                return *next_rit; // Return the element after wd_id
            else
                return ""; // wd_id found at the end of the vector
        }
        ++rit;
    }
    return ""; // wd_id not found
}




void PatchData::analyze()
{
    std::vector<std::string> arr = data[PatchData::dvar_array];
    int maxDvarLength = arr.size(); 
    std::string pokeID, WD_ID, WD_t, key;


    Timer t;

    for (size_t i = 0; i < maxDvarLength; i++) {
        if (!beginData && (i == maxDvarLength-1)) continue; // end of array and still hasn't found first patch change (animal is teh suck)
        else if (!beginData && (arr[i+1] != "-20")) continue; // reached the last ele and it's not a reward
        else if (!beginData && (arr[i+1] == "-20")) {
            beginData = true;
            continue;
        }
        else if (arr[i] == "-20") {

            // Mark timers and calc times

            if (t.start == "") {
                // first patch change - don't calc time diff
                t.start = std::atof(arr[i+1].c_str()); // mark start of new epoch
            } else {
                // mark end time and calc time diff
                t.end = std::atof(arr[i+1].c_str());
                timeList.push_back(t.diff());

                // check for null change (no rewards during that patch and they changed)
                if (auto search = rewards.find(t.start); search != rewards.end()){
                    nullChanges.push_back(t.start);
                }

                t.start = arr[i+1]; // mark start time of next epoch
            }

            // calc travel time
            // ask amy about what its supposed to represent
            // perhaps look at -3 or -4 signal when light turns on

            // Pokes
            pokeID = arr[i-2];  // it's back 2 spots in amy's data file but ahead in marks
            // pokeID = arr[i+2];  // for the location of the flag  in mark's data files
            WD_ID = (pokeID == "-14") ? "-23" : "-24";
            
            // find last occurance of the WD_ID
            WD_t = findLastOccurrence(i-2, WD_ID);
            if (WD_t != "") {
                travelTimes.push_back(atof(WD_t.c_str()));
            }

            key = t.start;

            if (data[dvar_array][i] == "-7") {
                leftRewards[key] = leftRewards[key]+1;
                rewards[key] = rewards[key]+1;
                continue;
            } else if (data[dvar_array][i] == "-8") {
                rightRewards[key] = rightRewards[key]+1;
                rewards[key] = rewards[key]+1;
                continue;
            } else if (data[dvar_array][i] == "-12") {
                ++leftPokes;
                continue;
            } else if (data[dvar_array][i] == "-14") {
                ++rightPokes;
                continue;
            } 

        }
    }

    key = t.start;  // grab last key value to remove associated data
    bool isLeft = (leftRewards.find(key) != leftRewards.end());
    bool isRight = (rightRewards.find(key) != rightRewards.end());
    bool isEither = (rewards.find(key) != rewards.end());

    if (isLeft)
        leftRewards.erase(key);
    if (isRight)
        rightRewards.erase(key);
    if (isEither)
        rewards.erase(key);

    // No need to remove time from timeList as it wont have been collected

    // Avg (Patch time / patch changes)


    // set either to 0 (avoid div by zero error) or the avg
    float avg = std::accumulate(timeList.begin(), timeList.end(), 0);
    avg = (timeList.size() == 0) ? 0 : (avg/timeList.size());
    
    // convert to strings for the map
    data["patchChanges"] = StringUtil::makeVecStrNum(timeList.size());
    data["AvgPatchTime"] = StringUtil::makeVecStrNum(avg);

    

}





// static variable declarations

int DATA_START_INDEX = 51;
std::string PatchData::validFileFormats[NUM_VALID_FILEFORMATS] = {"Amy_Patch_Depletion"};
std::string PatchData::cvar_array = "A";
std::string PatchData::dvar_array = "C";
std::string PatchData::cvar_names[NUM_CVAR] = { "PatchChangeDelay",
                            "InterRewardDelay",
                            "FirstRewardDelay",
                            "PatchStartingWater",
                            "RewardDecreaseFactor",
                            "MaximumTotalWater",
                            "MaximumSessionDuration" };
int PatchData::cvar_indices[NUM_CVAR] = {3,4,5,6,7,8,9};
std::string PatchData::dvar_names[NUM_DVAR] = { "TotalWater",
                            "SessionDuration" };
int PatchData::dvar_indices[NUM_DVAR] = {20, 21};
