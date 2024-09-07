#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

#include "turing_machine.hpp"

const int X_RES = 800;
const int Y_RES = 600;

void close(SDL_Window* window, SDL_Renderer* renderer){

  /*free memory from window and renderer*/
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}


void run_event_loop(SDL_Window* window, SDL_Renderer* renderer, TuringMachineMemoryState* tape, TuringMachineFSMState* fsm, int head_position){
  bool quit = false;
  SDL_Event e;

  int count = 0;
  while(count <= 10 && !quit){
    /*
    while(SDL_PollEvent(&e) != 0){
      //user requests quit
      if(e.type == SDL_QUIT){
	quit = true;
      }
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    */
    head_position = fsm->state_transition(*tape, head_position);

    // print the states to stdout for now
    for (char glyph: tape->state){
      std::printf("%c ", glyph);
				 }
    std::printf("\n");
    
    ++count;
  }
}


int main(int argc, char** argv){
  //init sdl subsytems
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("Error intialising SDL2! Error: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("Turing Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, X_RES, Y_RES, SDL_WINDOW_SHOWN);
  if(window == nullptr){
    printf("Window could not be initialised! %s\n", SDL_GetError());
    close(window, nullptr);
    return -1;
  }

    
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == nullptr){
      printf("Error creating renderer! %s\n", SDL_GetError());
      close(window, nullptr);
      return -1;
  }


  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF , 0xFF);
  

  TuringMachineMemoryState* turing_machine_tape = new TuringMachineMemoryState();
  turing_machine_tape->state = std::vector<char>(30, '0');
  std::cout << "hello hello" << std::endl;

  TuringMachineFSMState* turing_machine_fsm = new TuringMachineFSMState();
  run_event_loop(window, renderer, turing_machine_tape, turing_machine_fsm, 15);
  
  delete turing_machine_tape;
  
  close(window, renderer);
 
  return 0;
}
