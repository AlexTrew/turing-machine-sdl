#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <vector>

struct TuringMachineMemoryState{
  std::vector<char> state;
};

enum class MoveDirection{
  LEFT,
  RIGHT
};

class TuringMachineFSMState{
  int move_head_index(int head_index, const MoveDirection& move_direction);
  void write(TuringMachineMemoryState& tape_state, int head_index, const char write_value);

public:
  int state_transition(TuringMachineMemoryState& tape_state, int head_index);
};

#endif
