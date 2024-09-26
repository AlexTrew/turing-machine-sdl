#ifndef TURINGMACHINE
#define TURINGMACHINE
#include <memory>
#include <vector>

#include "state.hpp"

class TuringMachine {

  std::unique_ptr<UpdateInstruction> get_update_instruction(
      const TuringMachineState& state);

 public:
  const UpdateInstruction& get_update_instruction(TuringMachineState& state,
                                                  char read_char);

  TuringMachineState& process(TuringMachineState& state);
};
#endif
