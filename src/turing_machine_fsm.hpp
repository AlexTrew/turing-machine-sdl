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

class TuringMachineFSMStateSpace {
 public:
  int current_state_id = 0;
  std::map<int, TuringMachineFSMState> id_x_fsm_state = {};
  TuringMachineFSMStateSpace() {
    TuringMachineFSMState state_0 = TuringMachineFSMState();

    state_0.read_char_x_behaviour_instruction = {
        {'#', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::RIGHT, '0', 1))},
        {'0', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::LEFT, '0', 0))},
        {'1', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::LEFT, '1', 0))},
    };

    id_x_fsm_state[0] = state_0;

    TuringMachineFSMState state_1 = TuringMachineFSMState();

    state_1.read_char_x_behaviour_instruction = {
        {'#', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::LEFT, '1', 2))},
        {'0', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::RIGHT, '1', 2))},
        {'1', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::RIGHT, '0', 1))},
    };

    id_x_fsm_state[1] = state_1;

    TuringMachineFSMState state_2 = TuringMachineFSMState();

    state_2.read_char_x_behaviour_instruction = {
        {'#', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::RIGHT, '1', -1))},
        {'0', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::LEFT, '0', 2))},
        {'1', std::shared_ptr<TuringMachineUpdate>(
                  new TuringMachineUpdate(MoveDirection::LEFT, '1', 2))},
    };

    id_x_fsm_state[2] = state_2;

    TuringMachineFSMState state_stop = TuringMachineFSMState();
    id_x_fsm_state[-1] = state_stop;
  };
};

class TuringMachineFSM {
  std::shared_ptr<TuringMachineFSMStateSpace> _state_space;

 public:
  TuringMachineFSM() {
    _state_space = std::unique_ptr<TuringMachineFSMStateSpace>(
        new TuringMachineFSMStateSpace);
  }
  std::shared_ptr<TuringMachineUpdate> run(char input);
};
#endif
