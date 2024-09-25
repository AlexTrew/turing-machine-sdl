#include "turing_machine.hpp"
#include <cassert>
#include <memory>
#include <iostream>


UpdateInstruction* TuringMachine::get_update_instruction(TuringMachineState& state) {

  if (state.turing_machine_memory[state.head_index] == '0') {
    return new UpdateInstruction(MoveDirection::RIGHT, '1');
  } else if (state.turing_machine_memory[state.head_index] == '1') {
    return new UpdateInstruction(MoveDirection::LEFT, '0');
  };
  assert(false);
}

TuringMachineState& TuringMachine::process(TuringMachineState& state) {

  std::unique_ptr<UpdateInstruction> update_instruction_ptr = std::unique_ptr<UpdateInstruction>(get_update_instruction(state));

  int new_head_index = 0;
  switch (update_instruction_ptr->direction) {
    case MoveDirection::RIGHT:
      new_head_index = state.head_index + 1;
      break;
    case MoveDirection::LEFT:
      new_head_index = state.head_index - 1;
      break;
    default:
      assert(false);
  }


  state.turing_machine_memory[state.head_index] = update_instruction_ptr->new_value;
  state.head_index = new_head_index;

  return state;


};
