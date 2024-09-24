#ifndef DISPLAY
#define DISPLAY

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#import <vector>
#include "texture_builder.hpp"

const int X_RES = 1920;
const int Y_RES = 1280;

const int NO_OF_TILES_X = 64;
const int NO_OF_TILES_Y = 48;

const int TILE_WIDTH = X_RES / NO_OF_TILES_X;
const int TILE_HEIGHT = Y_RES / NO_OF_TILES_Y;

SDL_Colour SDL_COLOUR_BLACK{0, 0, 0};

SDL_Colour SDL_COLOUR_WHITE{255, 255, 255};

SDL_Colour SDL_COLOUR_GREY{220, 220, 220};

struct ScreenPosition {
  int x;
  int y;
};

class Display {

  SDL_Window* _window = nullptr;
  SDL_Renderer* _renderer = nullptr;
  TTF_Font* _font = nullptr;

  std::unique_ptr<ScreenPosition> get_on_screen_position(int global_x_position,
                                                         int global_y_position);
  void display_glyph_at_screen_position(
      std::unique_ptr<ScreenPosition> screen_position_ptr,
      SDL_Texture* glyph_texture);

  void display_text_at_screen_position(
      std::unique_ptr<ScreenPosition> screen_position_ptr, int grid_w,
      int grid_h, std::string text_to_display, SDL_Colour colour);

 public:
  Display();
  ~Display();
  void process(const std::vector<char>& state, const int viewport_position_x);
};

#endif