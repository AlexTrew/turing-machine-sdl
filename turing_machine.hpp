#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <vector>

enum class MoveDirection { LEFT, RIGHT };

struct TuringMachineState {
  int head_index;
  std::vector<char>& tm_state;
};

struct UpdateInstruction {
  MoveDirection direction;
  char new_value;

  UpdateInstruction(MoveDirection direction, int new_value);
};

class TuringMachine {

  const UpdateInstruction* get_update_instruction(
      const TuringMachineState& state);

  int get_updated_head_index(int head_index,
                             const MoveDirection& move_direction);
  void update_state_in_place(TuringMachineState state);

 public:
  TuringMachine(int tape_length, int initial_head_position);

  int process();
};

#endif
