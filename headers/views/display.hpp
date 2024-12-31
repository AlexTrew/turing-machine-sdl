#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "headers/models/state.hpp"
#include "headers/models/ui_state.hpp"
#include "headers/util/colour.hpp"
#include "headers/views/cfg.hpp"
#include "headers/views/texture_builder.hpp"
#include "headers/views/ui.hpp"

struct ScreenPosition {
  int x;
  int y;
};

class Display {

  SDL_Window* _window = nullptr;
  SDL_Renderer* _renderer = nullptr;
  TTF_Font* _font = nullptr;

  void display_glyph_at_screen_position(
      std::shared_ptr<ScreenPosition> screen_position, char glyph_char,
      Colour fg_colour);

  void display_text_at_screen_position(
      std::shared_ptr<ScreenPosition> screen_position_ptr, int grid_w,
      int grid_h, std::string text_to_display, Colour colour);

  void display_table_at_screen_position(
      std::shared_ptr<ScreenPosition> screen_position, int grid_w, int grid_h,
      int no_of_columns, int no_of_rows);

  std::shared_ptr<ScreenPosition> convert_world_position_to_on_screen_position(
      int global_x_position, int global_y_position);

 public:
  Display();
  ~Display();

  void process(const std::unique_ptr<TuringMachineState>& state_ptr,
               const std::unique_ptr<UIState>& ui_state_ptr);
};
#endif
