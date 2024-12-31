#include "headers/controllers/turing_machine.hpp"
#include <cassert>
#include <memory>
#include "headers/models/state.hpp"

void TuringMachine::process(std::unique_ptr<TuringMachineState>& state_ptr) {

  char read_char = state_ptr->turing_machine_memory[state_ptr->head_index];
  const std::shared_ptr<TuringMachineUpdate>& update_instruction_ptr =
      _fsm->run(read_char);

  int new_head_index = state_ptr->head_index;
  switch (update_instruction_ptr->direction) {
    case MoveDirection::RIGHT:
      new_head_index = state_ptr->head_index + 1;
      break;
    case MoveDirection::LEFT:
      new_head_index = state_ptr->head_index - 1;
      break;
    case MoveDirection::NONE:
      break;
  }

  //make the state array circular
  state_ptr->turing_machine_memory[state_ptr->head_index] =
      update_instruction_ptr->new_value;

  state_ptr->head_index =
      new_head_index % state_ptr->turing_machine_memory.size();
};
