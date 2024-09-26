#ifndef STATE
#define STATE

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum class MoveDirection { LEFT, RIGHT, NONE };

struct UpdateInstruction {
  MoveDirection direction;
  char new_value = '0';

  UpdateInstruction(MoveDirection direction, char new_value) {
    this->direction = direction;
    this->new_value = new_value;
  }
};

struct TuringMachineState {
  int head_index = 0;
  std::vector<char> turing_machine_memory;
  std::unordered_map<char, std::shared_ptr<UpdateInstruction>>
      update_instruction_lookup = {};

  TuringMachineState(int initial_head_index, int memory_size) {
    head_index = initial_head_index;
    turing_machine_memory = std::vector<char>(memory_size, '#');
    turing_machine_memory[12] = '1';
    turing_machine_memory[56] = '1';

    //default
    update_instruction_lookup['#'] = std::shared_ptr<UpdateInstruction>(
        new UpdateInstruction(MoveDirection::RIGHT, '0'));

    update_instruction_lookup['0'] = std::shared_ptr<UpdateInstruction>(
        new UpdateInstruction(MoveDirection::RIGHT, '1'));
    update_instruction_lookup['1'] = std::shared_ptr<UpdateInstruction>(
        new UpdateInstruction(MoveDirection::LEFT, '0'));
  }
};

#endif
