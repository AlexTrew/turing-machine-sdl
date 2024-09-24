#include "turing_machine.hpp"
#include <cassert>

UpdateInstruction::UpdateInstruction(MoveDirection direction, int new_value) {
  this->direction = direction;
  this->new_value = new_value;
}

const UpdateInstruction* TuringMachine::get_update_instruction() {
  if (_state[_head_position] == '0') {
    return new UpdateInstruction(MoveDirection::LEFT, '1');
  } else if (_state[_head_position] == '1') {
    return new UpdateInstruction(MoveDirection::RIGHT, '0');
  };
  assert(false);
}

int TuringMachine::get_updated_head_index(const MoveDirection& move_direction) {
  switch (move_direction) {
    case MoveDirection::RIGHT:
      return _head_position + 1;
    case MoveDirection::LEFT:
      return _head_position - 1;
    default:
      assert(false);
  }
}

void TuringMachine::update_state_in_place(std::vector<char>& tape_state,
                                          int head_index,
                                          const char write_value) {
  tape_state[head_index] = write_value;
}

int TuringMachine::process() {
  const UpdateInstruction* update_instruction =
      get_update_instruction(_head_position);
  update_state_in_place(_state, _head_position, update_instruction->new_value);
  _head_position =
      get_updated_head_index(_head_position, update_instruction->direction) %
      _state.size();
}
