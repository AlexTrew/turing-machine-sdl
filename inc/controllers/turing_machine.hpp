#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <memory>
#include <vector>

#include "inc/models/state.hpp"
#include "inc/models/turing_machine_fsm.hpp"

class TuringMachine {
  std::unique_ptr<TuringMachineFSM> _fsm;

 public:
  TuringMachine() {
    _fsm = std::unique_ptr<TuringMachineFSM>(new TuringMachineFSM());
  }
  void process(std::unique_ptr<TuringMachineState>& state_ptr);
};
#endif
