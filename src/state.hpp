#ifndef STATE
#define STATE

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct TuringMachineState {
  int head_index = 0;
  std::vector<char> turing_machine_memory;

  TuringMachineState(int initial_head_index, int memory_size) {
    turing_machine_memory = std::vector<char>(memory_size, '#');
    head_index = initial_head_index;
    turing_machine_memory[2] = '1';
    turing_machine_memory[3] = '0';
    turing_machine_memory[4] = '1';
    turing_machine_memory[5] = '1';
  }
};

#endif
