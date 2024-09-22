#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "texture_builder.hpp"
#include "turing_machine.hpp"

const int X_RES = 1920;
const int Y_RES = 1280;

const int NO_OF_TILES_X = 64;
const int NO_OF_TILES_Y = 48;

const int TILE_WIDTH = X_RES / NO_OF_TILES_X;
const int TILE_HEIGHT = Y_RES / NO_OF_TILES_Y;

SDL_Colour SDL_COLOUR_BLACK{0, 0, 0};

SDL_Colour SDL_COLOUR_WHITE{255, 255, 255};

SDL_Colour SDL_COLOUR_GREY{220, 220, 220};

void close(SDL_Window* window, SDL_Renderer* renderer) {

  //clear the texture cache
  clear_glyph_texture_cache();
  clear_glyph_texture_cache();

  // close sdl image and sdl ttf
  IMG_Quit();
  TTF_Quit();

  //free memory from window and renderer
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void display_text_at_grid_position(int x, int y, int grid_w, int grid_h,
                                   std::string text_to_display, TTF_Font* font,
                                   SDL_Colour colour, SDL_Renderer* renderer) {
  SDL_Texture* text_texture =
      get_accelerated_text_texture(renderer, font, text_to_display, &colour);

  SDL_Rect text_box = {x * TILE_WIDTH, y * TILE_HEIGHT, grid_w * TILE_WIDTH,
                       grid_h * TILE_HEIGHT};
  SDL_RenderCopy(renderer, text_texture, nullptr, &text_box);
}

void display_glyph_at_grid_position(int x, int y, SDL_Texture* glyph_texture,
                                    SDL_Renderer* renderer) {

  SDL_Rect tile = {x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
  SDL_RenderCopy(renderer, glyph_texture, nullptr, &tile);
}

void run_event_loop(SDL_Window* window, SDL_Renderer* renderer) {

  //turing machine utils
  int tape_length = 10000;
  std::vector<char> tm_state = std::vector<char>(tape_length, '0');
  TuringMachine* turing_machine = new TuringMachine();
  int head_position = 10;

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

      // get the updated state of the turing machine.
      head_position = turing_machine->process(tm_state, head_position);

      //render the state to the screen

      int window_start_index = head_position / NO_OF_TILES_X;
      std::string window_start_index_str = std::to_string(window_start_index);

      SDL_RenderClear(renderer);

      // draw lowest z layer
      for (int i = window_start_index;
           i <
           std::min(window_start_index + NO_OF_TILES_X, int(tm_state.size()));
           ++i) {

        SDL_Texture* tape_glyph_texture = get_accelerated_glyph_texture(
            renderer, font, tm_state[i], &SDL_COLOUR_BLACK);
        display_glyph_at_grid_position(i, 30, tape_glyph_texture, renderer);

        //draw the 'H' for head
      }
      SDL_Texture* head_glyph_texture =
          get_accelerated_glyph_texture(renderer, font, 'H', &SDL_COLOUR_BLACK);
      display_glyph_at_grid_position(head_position, 31, head_glyph_texture,
                                     renderer);

      // draw index text
      display_text_at_grid_position(0, 29, window_start_index_str.size(), 1,
                                    window_start_index_str, font,
                                    SDL_COLOUR_GREY, renderer);

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
