#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

void Process::setPid(int pid){
    if (pid >= 0)
    {
        this->Pid_ = pid;
    }
}

// TODO: Return this process's ID
int Process::Pid() {
    return this->Pid_;  
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    return 0; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this->Pid()); 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(this->Pid()); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(this->Pid()); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(this->Pid()); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }