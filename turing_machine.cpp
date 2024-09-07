#include "turing_machine.hpp"
#include <cassert>

int TuringMachineFSMState::state_transition(TuringMachineMemoryState& tape_state, int head_index){
  if(tape_state.state[head_index] == '0'){
    write(tape_state, head_index, '1');
    return move_head_index(head_index, MoveDirection::RIGHT);
  }
  else if (tape_state.state[head_index] == '1'){
    write(tape_state, head_index, '0');
    return move_head_index(head_index, MoveDirection::LEFT);
  };
  assert(false);
}

int TuringMachineFSMState::move_head_index(int head_index, const MoveDirection& move_direction){
  switch (move_direction){
  case MoveDirection::RIGHT:
    return head_index + 1;
  case MoveDirection::LEFT:
    return head_index - 1;
  default:
    assert(false);
  }
}

void TuringMachineFSMState::write(TuringMachineMemoryState& tape_state, int head_index, const char write_value){
  tape_state.state[head_index] = write_value;
  return;
}

