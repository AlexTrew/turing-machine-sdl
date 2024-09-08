#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <vector>


enum class MoveDirection{
  LEFT,
  RIGHT
};

struct UpdateInstruction{
  MoveDirection direction;
  char new_value;

  UpdateInstruction(MoveDirection direction, int new_value);
};

class TuringMachine{

  const UpdateInstruction* get_update_instruction(const std::vector<char>& tm_state, int head_index);
  int get_updated_head_index(int head_index, const MoveDirection& move_direction);
  void update_state_in_place(std::vector<char>& tape_state, int head_index, const char write_value);

public:
  int process(std::vector<char>& tm_state, int head_position);
};

#endif
