#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "display.hpp"
#include "turing_machine.hpp"

void run_event_loop() {

  Uint64 start_time = SDL_GetTicks64();

  int tape_length = 100000000;
  std::unique_ptr<TuringMachine> turing_machine_ptr =
      std::unique_ptr<TuringMachine>(
          new TuringMachine(tape_length, tape_length / 2));

  std::unique_ptr<Display> display_manager_ptr =
      std::unique_ptr<Display>(new Display());

  int head_position = 10;

  // event loop state
  bool quit = false;
  SDL_Event e;

  Uint64 loop_run_time = 0;
  Uint64 frames = 0;

  // draw the title once

  while (!quit) {
    ++frames;
    loop_run_time = SDL_GetTicks64() - start_time;
    while (SDL_PollEvent(&e) != 0) {
      //user requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }
}

int main(int argc, char** argv) {
  //init sdl subsytems

  run_event_loop();

  return 0;
}
