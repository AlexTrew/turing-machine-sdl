#ifndef UI
#define UI
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "cfg.hpp"

struct GuiPanelElement {
  std::string label = "";
  /*I think that sdl constructs such as renderers and textures needs to be destroyed by their
    bespoke SDL_Destroy/Free whatever methods, so smart
    pointers are not appropriate. The reason I say this is I have found deleting them in other ways to cause
    memory issues. I would like to look into this further though.
   */
  int x_pos = 0;
  int y_pos = 0;
  int size_x = 0;
  int size_y = 0;
};

struct Button : public GuiPanelElement {
  std::string label = "";
  int x_pos = 0;
  int y_pos = 0;
  int size_x = 0;
  int size_y = 0;

  Button(std::string label, int x_pos, int y_pos, int size_x, int size_y)
      : label(label),
        x_pos(x_pos),
        y_pos(y_pos),
        size_x(size_x),
        size_y(size_y){};
};

struct TableColumn {
  std::string name = "";
  std::string value = "";
  bool modifiable = false;
};

struct TableRow {
  std::vector<TableColumn> columns = {};
};

struct Table : public GuiPanelElement {
  std::vector<TableRow> rows = {};
  bool extendable = false;
  std::string label = "";
  int x_pos = 0;
  int y_pos = 0;
  int size_x = 0;
  int size_y = 0;

  Table(std::string label, int x_pos, int y_pos, int size_x, int size_y)
      : label(label),
        x_pos(x_pos),
        y_pos(y_pos),
        size_x(size_x),
        size_y(size_y){};
};

struct TextInput : public GuiPanelElement {
  std::string label = "";
  int x_pos = 0;
  int y_pos = 0;
  int size_x = 0;
  int size_y = 0;

  TextInput(std::string label, int x_pos, int y_pos, int size_x, int size_y)
      : label(label),
        x_pos(x_pos),
        y_pos(y_pos),
        size_x(size_x),
        size_y(size_y){};
};

struct GuiPanel {
  /* a "panel" in which other ui elements such as buttons and tables will go */
  std::string label = "";
  bool visible = false;
  int size_x = 0;
  int size_y = 0;
  int screen_x_pos = 0;
  int screen_y_pos = 0;
  double local_to_global_conversion_x = 0.00;
  double local_to_global_conversion_y = 0.00;
  std::vector<std::shared_ptr<Table>> tables = {};
  std::vector<std::shared_ptr<Button>> buttons = {};

  GuiPanel(std::string label, bool visible, int size_x, int size_y,
           int screen_x_pos, int screen_y_pos,
           std::vector<std::shared_ptr<Table>> tables,
           std::vector<std::shared_ptr<Button>> buttons)
      : label(label),
        visible(visible),
        size_x(size_x),
        size_y(size_y),
        screen_x_pos(screen_x_pos),
        screen_y_pos(screen_y_pos),
        tables(tables),
        buttons(buttons) {
    local_to_global_conversion_x = float(size_x) / X_RES;
    local_to_global_conversion_y = float(size_y) / Y_RES;
  }
};

void draw_gui(const std::vector<std::shared_ptr<GuiPanel>>& gui_panels,
              TTF_Font* gui_font, SDL_Renderer* renderer);

void draw_gui_button(const std::shared_ptr<Button>& gui_panel_element_ptr,
                     TTF_Font* label_font, SDL_Renderer* renderer);

void draw_gui_panel(const std::shared_ptr<GuiPanel>& gui_panel_ptr,
                    TTF_Font* label_font, SDL_Renderer* renderer);

#endif
