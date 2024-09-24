#include "display.hpp"
#include <SDL2/SDL_image.h>
#include <SDL_stdinc.h>
#include <cassert>
#include <vector>

void Display::process(const std::vector<char>& state,
                      const int viewport_position_x) {
  SDL_RenderClear(_renderer);

  std::string window_start_index_str = std::to_string(window_start_index);

  // draw the glyphs of the tape
  for (int i = window_start_index;
       i < std::min(window_start_index + NO_OF_TILES_X, int(tm_state.size()));
       ++i) {

    SDL_Texture* tape_glyph_texture = get_accelerated_glyph_texture(
        _renderer, _font, head_position, &SDL_COLOUR_BLACK);
    display_glyph_at_screen_position(get_on_screen_position(i, 10),
                                     tape_glyph_texture);

    //draw the 'H' for head
  }
  SDL_Texture* head_glyph_texture =
      get_accelerated_glyph_texture(_renderer, _font, 'H', &SDL_COLOUR_BLACK);
  display_glyph_at_screen_position(get_screen_position(head_position, 11),
                                   head_glyph_texture);

  // draw index info
  display_text_at_screen_position(get_on_screen_position(0, 8), 4, 1, "index",
                                  SDL_COLOUR_GREY);

  display_text_at_screen_position(get_on_screen_position(0, 9),
                                  window_start_index_str.size(), 1,
                                  window_start_index_str, SDL_COLOUR_GREY);

  display_text_at_screen_position(
      get_on_screen_position(NO_OF_TILES_X / 2 - 10, 2), 15, 1,
      "Alex's Turing machine", SDL_COLOUR_BLACK);

  SDL_RenderPresent(_renderer);
  SDL_Delay(5);
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

  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (_renderer == nullptr) {
    printf("Error creating renderer! %s\n", SDL_GetError());
    assert(false);
  }

  _font = TTF_OpenFont("Ubuntu-Regular.ttf", 15);
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
