#include "turing_machine.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include "state.hpp"

const UpdateInstruction& TuringMachine::get_update_instruction(
    TuringMachineState& state, char read_char) {

  if (state.update_instruction_lookup.count(read_char) != 0) {
    return *state.update_instruction_lookup[read_char];
  } else {
    assert(false);
  }
}

TuringMachineState& TuringMachine::process(TuringMachineState& state) {

  char read_char = state.turing_machine_memory[state.head_index];
  const UpdateInstruction& update_instruction =
      get_update_instruction(state, read_char);

  int new_head_index = state.head_index;
  switch (update_instruction.direction) {
    case MoveDirection::RIGHT:
      new_head_index = state.head_index + 1;
      break;
    case MoveDirection::LEFT:
      new_head_index = state.head_index - 1;
      break;
    case MoveDirection::NONE:
      break;
  }

  state.turing_machine_memory[state.head_index] = update_instruction.new_value;
  state.head_index = new_head_index % state.turing_machine_memory.size();

  return state;
};
