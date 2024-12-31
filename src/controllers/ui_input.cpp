#include "inc/controllers/ui_input.hpp"
#include <math.h>
#include <cmath>
#include <iostream>
#include <memory>
#include "inc/views/display.hpp"
#include "inc/views/turing_ui_def.hpp"
#include "inc/views/ui.hpp"

void UIManager::initialise_ui(std::unique_ptr<UIState>& ui_state) {
  ui_state->ui_panels = build_turing_machine_ui_definition();
}

void UIManager::handle_mouse_click(
    int mouse_x, int mouse_y,
    std::vector<std::shared_ptr<GuiPanel>> ui_panels) {
  for (std::shared_ptr<GuiPanel>& ui_panel : ui_panels) {
    if (ui_panel->visible) {
      // check all buttons to see if one is under the mouse cursor
      for (std::shared_ptr<Button>& button : ui_panel->buttons) {

        /* the mouse position is relative to the window, however
	 the button position is relative to the panel, so we convert
	 its position to be relative to the viewport. */

        //check if the cursor is over the button

        if (mouse_is_over_button(mouse_x, mouse_y,
                                 ui_panel->screen_x_pos + button->x_pos,
                                 ui_panel->screen_y_pos + button->y_pos,
                                 button->size_x, button->size_y)) {

          // i haven't quite figured out out what will happen here.
          // some kind of signal system should be implemented
          printf("I have been pressed!\n");
        }
      }
    }
  }
}

bool UIManager::mouse_is_over_button(int mouse_x, int mouse_y,
                                     int button_x_global, int button_y_global,
                                     int button_w_global, int button_h_global) {
  if (mouse_x >= button_x_global && mouse_y >= button_y_global &&
      mouse_x <= button_x_global + button_w_global &&
      mouse_y <= button_y_global + button_h_global) {
    return true;
  }
  return false;
}
