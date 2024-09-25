#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <vector>
#include <memory>

#include "state.hpp"

enum class MoveDirection { LEFT, RIGHT };

struct UpdateInstruction {
  MoveDirection direction;
  char new_value = '0';

  UpdateInstruction(MoveDirection direction, int new_value){
    this->direction = direction;
    this->new_value = new_value;
  }
};

class TuringMachine {

  std::unique_ptr<UpdateInstruction> get_update_instruction(
      const TuringMachineState& state);

 public:

  UpdateInstruction* get_update_instruction(TuringMachineState& state); 

  TuringMachineState& process(TuringMachineState& state);

};
#endif
