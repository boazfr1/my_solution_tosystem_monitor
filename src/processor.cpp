#include "processor.h"
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;



void getValuesFromCPUFile(string filePath, vector<int>& memoriesValues){
    string os;
    int memory {0};
    string line;
    std::ifstream stream(filePath);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os;
        while (memoriesValues.size() < 10)
        {
            linestream >> memory;
            memoriesValues.push_back(memory);
        }
    }
    
}

long long calculateTotalTime(vector<int>& memoriesValues){
    long long totalTime{0};
    for (auto i: memoriesValues)
    {
        totalTime += i;
    }
    return totalTime;
}


float calculateIdleTime(vector<int>& memoriesValuesBefore, vector<int>& memoriesValuesAfter){ 
    long idleTimeDiff = memoriesValuesAfter[0] - memoriesValuesBefore[0];
    long totalTimeDiff = calculateTotalTime(memoriesValuesAfter) - calculateTotalTime(memoriesValuesBefore);

    float idle_percentage = 0.0f;
    if (totalTimeDiff != 0) {
        idle_percentage = (static_cast<float>(totalTimeDiff - idleTimeDiff) / totalTimeDiff) * 100.0f;
    }
    return idle_percentage;
}


float Processor::Utilization() {
    getValuesFromCPUFile("/proc/stat", this->memoriesValuesBefore);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    getValuesFromCPUFile("/proc/stat", this->memoriesValuesAfter);
    float idle_time = calculateIdleTime(this->memoriesValuesBefore, this->memoriesValuesAfter);
    
    return 100.0f - idle_time;
}

void Processor::PrintMemoriesValuesBefore(){
    for(int i: this->memoriesValuesBefore)
        std::cout << "memory before = " << i << "\n";
  }
  void Processor::PrintMemoriesValuesAfter(){
    for(int i: this->memoriesValuesAfter)
        std::cout << "memory after = " << i << "\n";
  }