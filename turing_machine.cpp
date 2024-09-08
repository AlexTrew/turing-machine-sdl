#include "turing_machine.hpp"
#include <cassert>



UpdateInstruction::UpdateInstruction(MoveDirection direction, int new_value){
  this->direction = direction;
  this->new_value = new_value;
}

const UpdateInstruction* TuringMachine::get_update_instruction(const std::vector<char>& tape_state, int head_index){
  if(tape_state[head_index] == '0'){
    return new UpdateInstruction(MoveDirection::LEFT, '1');
  }
  else if (tape_state[head_index] == '1'){
    return new UpdateInstruction(MoveDirection::RIGHT, '0');
  };
  assert(false);
}

int TuringMachine::get_updated_head_index(int head_index, const MoveDirection& move_direction){
  switch (move_direction){
  case MoveDirection::RIGHT:
    return head_index + 1;
  case MoveDirection::LEFT:
    return head_index - 1;
  default:
    assert(false);
  }
}

void TuringMachine::update_state_in_place(std::vector<char>& tape_state, int head_index, const char write_value){
  tape_state[head_index] = write_value;
}

int TuringMachine::process(std::vector<char> &tm_state, int head_position){
      const UpdateInstruction* update_instruction = get_update_instruction(tm_state, head_position);
      update_state_in_place(tm_state, head_position, update_instruction->new_value);
      int new_index = get_updated_head_index(head_position, update_instruction->direction) % tm_state.size();
      delete update_instruction;
      return new_index;
}
