#include "display.hpp"
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>
#include <vector>
#include "turing_machine.hpp"

SDL_Colour SDL_COLOUR_BLACK{0, 0, 0};

SDL_Colour SDL_COLOUR_WHITE{255, 255, 255};

SDL_Colour SDL_COLOUR_GREY{220, 220, 220};

void Display::process(const TuringMachineState& state) {

  int camera_position_x = state.head_index - (state.head_index % NO_OF_TILES_X);
  SDL_RenderClear(_renderer);

  // draw the glyphs of the tape
  for (int i = camera_position_x;
       i < std::min(camera_position_x + NO_OF_TILES_X,
                    int(state.turing_machine_memory.size()));
       ++i) {

    SDL_Texture* tape_glyph_texture = get_accelerated_glyph_texture(
        _renderer, _font, state.turing_machine_memory[i], &SDL_COLOUR_WHITE);
    display_glyph_at_screen_position(get_on_screen_position(i, 10),
                                     tape_glyph_texture);

    //draw the 'H' for head
  }
  SDL_Texture* head_glyph_texture =
      get_accelerated_glyph_texture(_renderer, _font, 'H', &SDL_COLOUR_WHITE);
  display_glyph_at_screen_position(get_on_screen_position(state.head_index, 9),
                                   head_glyph_texture);

  // draw index info

  display_text_at_screen_position(get_on_screen_position(0, 13), 4, 1, "index",
                                  SDL_COLOUR_GREY);

  std::string head_index_str = std::to_string(state.head_index);
  display_text_at_screen_position(get_on_screen_position(0, 14),
                                  head_index_str.size(), 1, head_index_str,
                                  SDL_COLOUR_GREY);

  display_text_at_screen_position(
      get_on_screen_position(NO_OF_TILES_X / 2 - 10, 2), 15, 1,
      "Alex's Turing machine", SDL_COLOUR_WHITE);

  SDL_RenderPresent(_renderer);
  SDL_Delay(60);
}

std::unique_ptr<ScreenPosition> Display::get_on_screen_position(
    int global_x_position, int global_y_position) {
  std::unique_ptr<ScreenPosition> screen_position_ptr =
      std::unique_ptr<ScreenPosition>(new ScreenPosition());
  screen_position_ptr->x = global_x_position % NO_OF_TILES_X;
  screen_position_ptr->y = global_y_position % NO_OF_TILES_Y;
  return screen_position_ptr;
}

void Display::display_text_at_screen_position(
    std::unique_ptr<ScreenPosition> screen_position_ptr, int grid_w, int grid_h,
    std::string text_to_display, SDL_Colour colour) {
  SDL_Texture* text_texture =
      get_accelerated_text_texture(_renderer, _font, text_to_display, &colour);

  SDL_Rect text_box = {screen_position_ptr->x * TILE_WIDTH,
                       screen_position_ptr->y * TILE_HEIGHT,
                       grid_w * TILE_WIDTH, grid_h * TILE_HEIGHT};
  SDL_RenderCopy(_renderer, text_texture, nullptr, &text_box);
}

void Display::display_glyph_at_screen_position(
    std::unique_ptr<ScreenPosition> screen_position_ptr,
    SDL_Texture* glyph_texture) {

  SDL_Rect tile = {screen_position_ptr->x * TILE_WIDTH,
                   screen_position_ptr->y * TILE_HEIGHT, TILE_WIDTH,
                   TILE_HEIGHT};
  SDL_RenderCopy(_renderer, glyph_texture, nullptr, &tile);
}

Display::Display() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error intialising SDL2! Error: %s\n", SDL_GetError());
  }

  //Initialize SDL_ttf so we can support the font we are using for the glyphs
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }

  //initialise SDL_Image so we can support common image formats
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("SDL_IMG could not initialize! SDL_ttf Error: %s\n", IMG_GetError());
    assert(false);
  }

  _window =
      SDL_CreateWindow("Turing Machine", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, X_RES, Y_RES, SDL_WINDOW_SHOWN);
  if (_window == nullptr) {
    printf("Window could not be initialised! %s\n", SDL_GetError());
    assert(false);
  }

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (_renderer == nullptr) {
    printf("Error creating renderer! %s\n", SDL_GetError());
    assert(false);
  }

  SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0x00);

  _font = TTF_OpenFont("Ubuntu-Regular.ttf", 1000);
}

Display::~Display() {

  TTF_CloseFont(_font);
  // close sdl image and sdl ttf
  IMG_Quit();
  TTF_Quit();

  //free memory from window and renderer
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}
