#include "inc/models/turing_machine_fsm.hpp"
#include <iostream>
#include <memory>

std::shared_ptr<TuringMachineUpdate> TuringMachineFSM::run(char input) {
  int current_state_id = _state_space->current_state_id;
  std::shared_ptr<TuringMachineFSMState> current_fsm_state_ptr =
      _state_space->id_x_fsm_state_ptr[current_state_id];

  std::shared_ptr<TuringMachineUpdate> update_to_apply_ptr =
      current_fsm_state_ptr->read_char_x_behaviour_instruction[input];

  _state_space->current_state_id = update_to_apply_ptr->new_state_id;
  return update_to_apply_ptr;
};
