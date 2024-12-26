#ifndef UI_INPUT
#define UI_INPUT
#include <memory>
#include <vector>
#include "cfg.hpp"
#include "display.hpp"
#include "ui.hpp"
#include "ui_state.hpp"

class UIManager {

 public:
  void initialise_ui(std::unique_ptr<UIState>& ui_state);

  void handle_mouse_click(int mouse_x, int mouse_y,
                          std::vector<std::shared_ptr<GuiPanel>> ui_panels);

  bool mouse_is_over_button(int mouse_x, int mouse_y, int button_x,
                            int button_y, int button_w, int button_h);
};
#endif
