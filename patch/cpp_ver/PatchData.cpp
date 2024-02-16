#include "PatchData.h"
#include "StringUtil.h"
#include "HelperFoo.h"
#include <string>
#include <bits/stdc++.h>

// #define DEBUG
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
    float e = std::atof(end.c_str());
    float s = std::atof(start.c_str());
    return e - s;
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
        cvars[cvar_names[i]] = data[cvar_array][(cvar_indices[i]+1)];
    }

    // grab specific vars from dependent vars (Located in C array (mark) or the B array (mike))
    for (int i = 0; i < NUM_DVAR; i++) {
        dvars[dvar_names[i]] = data[dvar_array][dvar_indices[i]];
    }

    // std::cout << "calling analyze" << std::endl;
    analyze();
    // std::cout << "finished analyzing" << std::endl;

    for (auto & ele : data) {
        if (ele.second.size() != 1)
            continue;
        if (ele.first.size() == 1)
            continue;
        dvars[ele.first] = ele.second[0];
    }
}

// finds last occurance of wd_id in the data vector starting at idx and iterating backwards
std::string PatchData::findLastOccurrence(int idx, std::string wd_id) {
    auto rit = data[dvar_array].crend() - idx - 2;
    auto rend = data[dvar_array].crend();

    // std::cout << "crbegin(): " << *(data[dvar_array].crbegin()) << std::endl;
    // std::cout << "index: " << idx << std::endl;

    // std::cout << "crbegin() - idx - 2: " << *(rit) << std::endl;
    // std::cout << "ending at: " << *(rend-1) << std::endl;

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


void PatchData::printCvars()
{
    std::cout << std::endl << "*************     vvvvv     ***************" << std::endl;
    std::cout <<              "             Printing CVARS                " << std::endl;
    std::cout <<              "*************     vvvvv     ***************" << std::endl << std::endl;
    
    std::string keyList[] = {"PatchChangeDelay", "InterRewardDelay", 
                            "FirstRewardDelay", "PatchStartingWater", 
                            "RewardDecreaseFactor", "MaximumTotalWater",
                             "MaximumSessionDuration"};

    for (auto & k : keyList) {
        StringUtil::prettyWrite(k, cvars[k]);
    }

}


void PatchData::printDvars()
{
    std::cout << std::endl << "*************     vvvvv     ***************" << std::endl;
    std::cout <<              "             Printing DVARS                " << std::endl;
    std::cout <<              "*************     vvvvv     ***************" << std::endl << std::endl;
    
    // std::cout << std::left << std::setw(20) << "patchChanges: " << std::right << std::setw(20) << dvars["patchChanges"] << std::endl;
    std::string keyList[] = {"TotalWater", "SessionDuration", "patchChanges", 
                            "AvgPatchTime", "TotalLeftRewards", "TotalRightRewards", 
                            "TotalRewards", "IndifferencePoint", "PatchOnlyWater", 
                            "AvgTravelTime"};
    for (auto & k : keyList) {
        StringUtil::prettyWrite(k, dvars[k]);
    }
}


void PatchData::analyze()
{
    std::vector<std::string> arr = data[PatchData::dvar_array];
    int maxDvarLength = arr.size(); 
    std::string WD_ID, WD_t, key;
    int pokeID;

    // std::cout << "maxDvarLength: " << maxDvarLength << std::endl;

    Timer t;
    t.start = "";
    t.end = "";

    for (size_t i = 0; i < maxDvarLength; i++) {
        // std::cout << "arr[" << i << "]: " << arr[i] << std::endl;

        if (!beginData && (i == maxDvarLength-1)) continue; // end of array and still hasn't found first patch change (animal is teh suck)
        if (!beginData && (arr[i+1] != "-20.000")) continue; // reached the last ele and it's not a reward
        else if (!beginData && (arr[i+1] == "-20.000")) {
            beginData = true;
            continue;
        }
        if (arr[i] == "-20.000") {

            // Mark timers and calc times

            if (t.start == "") {
                // first patch change - don't calc time diff
                // std::cout << "in first patch change" << std::endl;
                t.start = arr[i+1]; // mark start of new epoch
            } else {
                // mark end time and calc time diff
                t.end = arr[i+1];
                // std::cout << "t.start: " << t.start << std::endl;
                // std::cout << "t.end: " << t.end << std::endl;
                // std::cout << "t.diff(): " << t.diff() << std::endl;

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
            pokeID = std::atoi(arr[i-2].c_str());  // it's back 2 spots in amy's data file but ahead in marks
            // pokeID = arr[i+2];  // for the location of the flag  in mark's data files
            WD_ID = (pokeID == -14) ? "-23.000" : "-24.000";
            
            // find last occurance of the WD_ID
            WD_t = findLastOccurrence(i-2, WD_ID);
            if (/*(arr[i-1] != "0.000") &&*/ (WD_t != "")) {
                float end = std::atof(arr[i-1].c_str());
                float beg = std::atof(WD_t.c_str());
                std::cout << "end: " << end << " beg: " << beg << std::endl;
                float prevWD_t = end - beg;
                travelTimes.push_back(prevWD_t);
            }
        }


        key = t.start;

        int val = std::atoi(data[dvar_array][i].c_str());

        // std::cout << "val: " << val << std::endl;
        if (val == -7) {
            // std::cout << "found a -7" << std::endl;
            leftRewards[key] = leftRewards[key]+1;
            rewards[key] = rewards[key]+1;
            continue;
        } else if (val == -8) {
            // std::cout << "Found a -8.000" << std::endl;
            rightRewards[key] = rightRewards[key]+1;
            rewards[key] = rewards[key]+1;
            continue;
        } else if (val == -12) {
            ++leftPokes;
            continue;
        } else if (val == -14) {
            ++rightPokes;
            continue;
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
    
    // convert to vector of strings for the map
    data["patchChanges"] = StringUtil::makeVecStrNum(timeList.size());
    data["AvgPatchTime"] = StringUtil::makeVecStrNum(avg);

    // total rewards on lef/right side
    data["TotalLeftRewards"] = StringUtil::makeVecStrNum(hf::getFreqSum(leftRewards));
    // std::cout << "leftRewards: " << hf::getFreqSum(leftRewards) << std::endl;
    // std::cout << "size of leftRewards: " << leftRewards.size() << std::endl;

    data["TotalRightRewards"] = StringUtil::makeVecStrNum(hf::getFreqSum(rightRewards));
    // std::cout << "rightRewards: " << hf::getFreqSum(rightRewards) << std::endl;
    // std::cout << "size of rightRewards: " << rightRewards.size() << std::endl;
    data["TotalRewards"] = StringUtil::makeVecStrNum(hf::getFreqSum(rewards));
    // std::cout << "rewards: " << hf::getFreqSum(rewards) << std::endl;
    // std::cout << "size of rewards: " << rewards.size() << std::endl;
    
    // get consumed volume and rejected volumes
    float decrease_factor  = std::stof(cvars["RewardDecreaseFactor"]);
    float start_volume = std::stof(cvars["PatchStartingWater"]);
    
    // std::cout << "cvars[\"PatchStartingWater\"]: " << cvars["PatchStartingWater"] << std::endl;
    // std::cout << "start_volume: " << start_volume << std::endl;

    // calc the reject vols and consumed volumes and record each in the consumedVols map
    //
    for (auto & m: rewards) {
        float sv = start_volume;
        // std::cout << "sv(start): " << sv << std::endl;
        consumedVols[m.first] = 0;
        for (int i = 0; i < m.second; i++) {
            consumedVols[m.first] += sv;
            // std::cout << "consumedVols now: " << consumedVols[m.first];
            sv *= (1-decrease_factor);
            // std::cout << " sv now: " << sv << std::endl;
        }
        rejectVols[m.first] = sv;
        // std::cout << "rejectedVols["<< m.first << "]: " << rejectVols[m.first] << std::endl;

    }

    // sum all vals in map
    float indifference_pt = hf::getFreqSum(rejectVols);
    // get average or set to 0 if div-by-zero
    indifference_pt = (rejectVols.size() == 0) ? 0 : (indifference_pt/rejectVols.size());
    // package as vec string for data map
    data["IndifferencePoint"] = StringUtil::makeVecStrNum(indifference_pt);

    data["PatchOnlyWater"] = StringUtil::makeVecStrNum(hf::getFreqSum(consumedVols));
    data["TimeList"] = StringUtil::ftosVec(timeList);
    data["NullChanges"] = nullChanges;

    float avgTravelTime = std::accumulate(travelTimes.begin(), travelTimes.end(), 0);
    avgTravelTime = (travelTimes.size() == 0 ? 0 : avgTravelTime/travelTimes.size());
    data["AvgTravelTime"] = StringUtil::makeVecStrNum(avgTravelTime);

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
