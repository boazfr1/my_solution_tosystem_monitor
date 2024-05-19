#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <utility>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, key, size;
  int value;
  std::vector<std::pair<std::string, int>> memoriesValues;

  std::ifstream stream(kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> key >> value >> size;
      memoriesValues.push_back(std::make_pair(key, value));
      if(key == "MemFree") break;;
    }
  }
  double memoryUtilization = memoriesValues[0].second - memoriesValues[1].second;
  return memoryUtilization; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long upTime;
  std::ifstream stream(kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    
    std::istringstream linestream(line);
    linestream >> upTime;
    
  }
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  std::string line, cpuLabel;
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> cpuLabel;
            if (cpuLabel == "cpu") {
                linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
                long totalJiffies = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
                return totalJiffies;
            }
        }
    }

  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string Spid = std::to_string(pid);
  string line, skipThisOne;
  long utime, stime;
  std::ifstream stream(kProcDirectory + Spid + kStatFilename);
  if (stream.is_open()) {
      while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne
               >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> skipThisOne >> utime >> stime;

      return utime + stime;
    }
  }
  return 0; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line, cpuLabel;
  long user, nice, system, idle, iowait, irq, softirq;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream>> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    long activeJiffies = user + nice + system + irq + softirq;

    return activeJiffies;
  }
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line, cpuLabel;
  long user, nice, system, idle, iowait, irq, softirq;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream>> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    long idleJiffies = idle + iowait;

    return idleJiffies;
  }
  
  return 0; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }