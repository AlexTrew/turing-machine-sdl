#ifndef UI
#define UI
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <vector>

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

struct Button : public GuiPanelElement {};

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
};

struct TextInput : public GuiPanelElement {};

struct GuiPanel {
  /* a "panel" in which other ui elements such as buttons and tables will go */
  std::string label = "";
  bool visible = false;
  int size_x = 0;
  int size_y = 0;
  int screen_x_pos = 0;
  int screen_y_pos = 0;
  std::vector<std::shared_ptr<Table>> tables = {};
  std::vector<std::shared_ptr<Button>> buttons = {};
};

void draw_gui(const std::vector<std::shared_ptr<GuiPanel>>& gui_panels,
              TTF_Font* gui_font, SDL_Renderer* renderer);

#endif
