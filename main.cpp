#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "rendered_glyph.hpp"
#include "turing_machine.hpp"

const int X_RES = 1920;
const int Y_RES = 1080;

const int TILE_WIDTH = 20;
const int TILE_HEIGHT = 20;

SDL_Colour SDL_COLOUR_BLACK{0, 0, 0};

SDL_Colour SDL_COLOUR_WHITE{255, 255, 255};

void close(SDL_Window* window, SDL_Renderer* renderer) {
  // close sdl image and sdl ttf
  clear_glyph_texture_cache();
  IMG_Quit();
  TTF_Quit();

  //free memory from window and renderer
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void create_tile(SDL_Renderer* renderer, int x, int y, int w, int h) {
  SDL_Rect new_viewport;
  new_viewport.x = x;
  new_viewport.y = y;
  new_viewport.w = w;
  new_viewport.h = h;

  SDL_RenderSetViewport(renderer, &new_viewport);
}

void display_glyph_at_grid_position(int x, int y, SDL_Texture* glyph_texture,
                                    SDL_Renderer* renderer) {

  SDL_Rect tile = {x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
  SDL_RenderCopy(renderer, glyph_texture, nullptr, &tile);
}

void run_event_loop(SDL_Window* window, SDL_Renderer* renderer) {

  //turing machine utils
  std::vector<char> tm_state = std::vector<char>(100, '0');
  TuringMachine* turing_machine = new TuringMachine();
  int head_position = 30;

  TTF_Font* font = TTF_OpenFont("Ubuntu-Regular.ttf", 12);

  // graphical utilities
  // event loop state
  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      //user requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      head_position = turing_machine->process(tm_state, head_position);

      //draw the state on screen
      SDL_RenderClear(renderer);

      for (int i = 0; i < tm_state.size(); ++i) {
        // draw the tape
        SDL_Texture* glyph_texture = get_glyph_texture(
            renderer, font, tm_state[i], &SDL_COLOUR_BLACK, &SDL_COLOUR_WHITE);
        display_glyph_at_grid_position(i, 5, glyph_texture, renderer);

        //draw the 'H' for head
      }
      SDL_Texture* head_glyph_texture = get_glyph_texture(
          renderer, font, 'H', &SDL_COLOUR_BLACK, &SDL_COLOUR_WHITE);
      display_glyph_at_grid_position(head_position, 6, head_glyph_texture,
                                     renderer);

      SDL_RenderPresent(renderer);
    }
  }

  delete turing_machine;
  TTF_CloseFont(font);
}

int main(int argc, char** argv) {
  //init sdl subsytems
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error intialising SDL2! Error: %s\n", SDL_GetError());
    return -1;
  }

  //Initialize SDL_ttf so we can support the font we are using for the glyphs
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return -1;
  }

  //initialise SDL_Image so we can support common image formats
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("SDL_IMG could not initialize! SDL_ttf Error: %s\n", IMG_GetError());
    return -1;
  }

  SDL_Window* window =
      SDL_CreateWindow("Turing Machine", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, X_RES, Y_RES, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    printf("Window could not be initialised! %s\n", SDL_GetError());
    close(window, nullptr);
    return -1;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    printf("Error creating renderer! %s\n", SDL_GetError());
    close(window, nullptr);
    return -1;
  }

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  run_event_loop(window, renderer);

  close(window, renderer);

  return 0;
}
