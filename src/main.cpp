#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include <memory>
#include <ostream>

#include "display.hpp"
#include "state.hpp"
#include "turing_machine.hpp"
#include "turing_machine_fsm.hpp"

void run_event_loop() {

  int tm_mem_size = 64;
  int initial_head_position = 2;
  std::unique_ptr<TuringMachineState> turing_machine_state_ptr =
      std::unique_ptr<TuringMachineState>(
          new TuringMachineState(initial_head_position, tm_mem_size));

  std::unique_ptr<TuringMachine> turing_machine_ptr =
      std::unique_ptr<TuringMachine>(new TuringMachine());

  std::unique_ptr<Display> display_manager_ptr =
      std::unique_ptr<Display>(new Display());

  bool quit = false;
  bool started = false;
  SDL_Event e;

  display_manager_ptr->process(turing_machine_state_ptr);

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      //user requests quit
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          started = true;
      }
    }

    if (started) {
      turing_machine_ptr->process(turing_machine_state_ptr);
      display_manager_ptr->process(turing_machine_state_ptr);
    }
  }
}

int main(int argc, char** argv) {
  run_event_loop();
  return 0;
}
