#include <SDL2/SDL.h>
#include <memory>

#include "display.hpp"
#include "state.hpp"
#include "turing_machine.hpp"

void run_event_loop() {

  Uint64 start_time = SDL_GetTicks64();

  int tm_mem_size = 64;
  int initial_head_position = 0;
  std::unique_ptr<TuringMachineState> turing_machine_state_ptr =
      std::unique_ptr<TuringMachineState>(
          new TuringMachineState(initial_head_position, tm_mem_size));

  std::unique_ptr<TuringMachine> turing_machine_ptr =
      std::unique_ptr<TuringMachine>(new TuringMachine());

  std::unique_ptr<Display> display_manager_ptr =
      std::unique_ptr<Display>(new Display());

  bool quit = false;
  SDL_Event e;

  Uint64 loop_run_time = 0;
  Uint64 frames = 0;

  while (!quit) {
    ++frames;
    loop_run_time = SDL_GetTicks64() - start_time;
    while (SDL_PollEvent(&e) != 0) {
      //user requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    *turing_machine_state_ptr =
        turing_machine_ptr->process(*turing_machine_state_ptr);
    display_manager_ptr->process(*turing_machine_state_ptr);
  }
}

int main(int argc, char** argv) {
  run_event_loop();
  return 0;
}
