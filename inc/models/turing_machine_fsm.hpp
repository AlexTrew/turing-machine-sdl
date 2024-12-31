#ifndef TURINGMACHINEFSM
#define TURINGMACHINEFSM
#include <map>
#include <memory>

enum class MoveDirection { LEFT, RIGHT, NONE };

struct TuringMachineUpdate {
  MoveDirection direction;
  char new_value = '0';
  int new_state_id = 0;

  TuringMachineUpdate(MoveDirection direction, char new_value,
                      int new_state_id) {
    this->direction = direction;
    this->new_value = new_value;
    this->new_state_id = new_state_id;
  }
};

struct TuringMachineFSMState {
  std::map<char, std::shared_ptr<TuringMachineUpdate>>
      read_char_x_behaviour_instruction = {};
};

struct TuringMachineFSMStateSpace {
  int current_state_id = 0;
  std::map<int, std::shared_ptr<TuringMachineFSMState>> id_x_fsm_state_ptr = {};

  TuringMachineFSMStateSpace() {
    // this is where the rules and states are hard coded until the
    // ui element for is implemented

    std::shared_ptr<TuringMachineFSMState> state_0_ptr =
        std::make_shared<TuringMachineFSMState>(TuringMachineFSMState());

    state_0_ptr->read_char_x_behaviour_instruction = {
        {'#', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::LEFT, '#', 1))},
        {'0', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::RIGHT, '0', 0))},
        {'1', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::RIGHT, '1', 0))},
    };

    id_x_fsm_state_ptr[0] = state_0_ptr;

    std::shared_ptr<TuringMachineFSMState> state_1_ptr =
        std::make_shared<TuringMachineFSMState>(TuringMachineFSMState());

    state_1_ptr->read_char_x_behaviour_instruction = {
        {'#', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::LEFT, '1', -1))},
        {'0', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::LEFT, '1', -1))},
        {'1', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::LEFT, '0', 1))},
    };

    id_x_fsm_state_ptr[1] = state_1_ptr;

    std::shared_ptr<TuringMachineFSMState> state_stop_ptr =
        std::shared_ptr<TuringMachineFSMState>(new TuringMachineFSMState());

    state_stop_ptr->read_char_x_behaviour_instruction = {
        {'#', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::NONE, '#', -1))},
        {'0', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::NONE, '0', -1))},
        {'1', std::make_shared<TuringMachineUpdate>(
                  TuringMachineUpdate(MoveDirection::NONE, '1', -1))},
    };

    id_x_fsm_state_ptr[-1] = state_stop_ptr;
  };
};

class TuringMachineFSM {
  std::unique_ptr<TuringMachineFSMStateSpace> _state_space;

 public:
  TuringMachineFSM() {
    _state_space = std::make_unique<TuringMachineFSMStateSpace>(
        TuringMachineFSMStateSpace());
  }
  std::shared_ptr<TuringMachineUpdate> run(char input);
};
#endif
