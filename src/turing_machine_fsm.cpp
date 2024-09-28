#include "turing_machine_fsm.hpp"
#include <memory>

std::shared_ptr<TuringMachineUpdate> TuringMachineFSM::run(char input) {
  int current_state_id = _state_space->current_state_id;
  TuringMachineFSMState current_fsm_state =
      _state_space->id_x_fsm_state[current_state_id];

  std::shared_ptr<TuringMachineUpdate> update_to_apply =
      current_fsm_state.read_char_x_behaviour_instruction[input];

  _state_space->current_state_id = update_to_apply->new_state_id;

  return update_to_apply;
};
