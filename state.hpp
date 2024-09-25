#ifndef STATE
#define STATE

#include <vector>

struct TuringMachineState {
  int head_index;
  std::vector<char> turing_machine_memory;

  TuringMachineState(int initial_head_index, int memory_size){ 
    head_index = initial_head_index;
    turing_machine_memory = std::vector<char>(memory_size, '0');
  }
  
};

#endif
