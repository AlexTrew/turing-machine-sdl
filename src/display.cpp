#include "display.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "colour.hpp"
#include "turing_machine.hpp"
#include "turing_ui_def.hpp"

void Display::process(const std::unique_ptr<TuringMachineState>& state_ptr) {

  int camera_position_x =
      state_ptr->head_index - (state_ptr->head_index % NO_OF_TILES_X);
  SDL_RenderClear(_renderer);

  // draw the glyphs of the tape
  for (int i = camera_position_x;
       i < std::min(camera_position_x + NO_OF_TILES_X,
                    int(state_ptr->turing_machine_memory.size()));
       ++i) {

    SDL_Texture* tape_glyph_texture = get_accelerated_glyph_texture(
        _renderer, _font, state_ptr->turing_machine_memory[i], Colour::WHITE);
    std::shared_ptr<ScreenPosition> glyph_screen_position =
        convert_world_position_to_on_screen_position(i, 10);
    display_glyph_at_screen_position(glyph_screen_position, tape_glyph_texture);
  }

  std::shared_ptr<ScreenPosition> head_glyph_position =
      convert_world_position_to_on_screen_position(state_ptr->head_index, 9);
  SDL_Texture* head_glyph_texture =
      get_accelerated_glyph_texture(_renderer, _font, 'H', Colour::WHITE);
  display_glyph_at_screen_position(head_glyph_position, head_glyph_texture);

  // draw index info
  std::shared_ptr<ScreenPosition> index_screen_position =
      convert_world_position_to_on_screen_position(0, 13);
  display_text_at_screen_position(index_screen_position, 4, 1, "index",
                                  Colour::GREY);

  std::string head_index_str = std::to_string(state_ptr->head_index);
  std::shared_ptr<ScreenPosition> head_index_text_position =
      convert_world_position_to_on_screen_position(0, 14);

  display_text_at_screen_position(head_index_text_position,
                                  head_index_str.size(), 1, head_index_str,
                                  Colour::GREY);

  std::shared_ptr<ScreenPosition> title_text_screen_position =
      convert_world_position_to_on_screen_position(NO_OF_TILES_X / 2 - 10, 2);
  display_text_at_screen_position(title_text_screen_position, 15, 1,
                                  "Alex's Turing machine", Colour::WHITE);

  //draw input table
  std::vector<std::shared_ptr<GuiPanel>> ui_panels =
      build_turing_machine_ui_definition();

  draw_gui(ui_panels, _font, _renderer);

  SDL_RenderPresent(_renderer);
  SDL_Delay(60);
}

std::shared_ptr<ScreenPosition>
Display::convert_world_position_to_on_screen_position(int global_x_position,
                                                      int global_y_position) {
  std::shared_ptr<ScreenPosition> screen_position_ptr =
      std::shared_ptr<ScreenPosition>(new ScreenPosition());
  screen_position_ptr->x = global_x_position % NO_OF_TILES_X;
  screen_position_ptr->y = global_y_position % NO_OF_TILES_Y;
  return screen_position_ptr;
}

void Display::display_text_at_screen_position(
    std::shared_ptr<ScreenPosition> screen_position, int grid_w, int grid_h,
    std::string text_to_display, Colour fg_colour) {
  SDL_Colour fg_sdl_colour = lookup_sdl_colour(fg_colour);
  SDL_Texture* text_texture = get_accelerated_text_texture(
      _renderer, _font, text_to_display, fg_colour);

  SDL_Rect text_box = {screen_position->x * TILE_WIDTH,
                       screen_position->y * TILE_HEIGHT, grid_w * TILE_WIDTH,
                       grid_h * TILE_HEIGHT};
  SDL_RenderCopy(_renderer, text_texture, nullptr, &text_box);
}

void Display::display_glyph_at_screen_position(
    std::shared_ptr<ScreenPosition> screen_position,
    SDL_Texture* glyph_texture) {
  // todo: this should also call the function to build the texture

  SDL_Rect tile = {screen_position->x * TILE_WIDTH,
                   screen_position->y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
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
