#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <iostream>


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void PrintMemoriesValuesBefore();
  void PrintMemoriesValuesAfter();

  // TODO: Declare any necessary private members
 private:
    std::vector<int> memoriesValuesBefore;
    std::vector<int> memoriesValuesAfter;
};

#endif