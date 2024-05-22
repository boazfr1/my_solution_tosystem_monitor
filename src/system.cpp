#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <filesystem>


#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
    return cpu_;
}



// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> holderProcesses = LinuxParser::Pids();
  
  for (int processNumber : holderProcesses) {
    Process process;
    process.setPid(processNumber);
    processes_.push_back(process);
  }
      std::cout << "hi boaz frid 1 " << "\n";

  for(auto i : processes_){
    std::cout << "i.Pid()" << i.Pid() << "\n";
  }
        std::cout << "hi boaz frid 2 " << "\n";

  return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
  return LinuxParser::UpTime(); 
}