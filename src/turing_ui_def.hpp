#include <memory>
#include <vector>
#include "display.hpp"
#include "ui.hpp"

// todo: move this to a file called "ui_definition.hpp with a cpp file"

std::vector<std::shared_ptr<GuiPanel>> build_turing_machine_ui_definition() {

  std::shared_ptr<Button> test_element_ptr =
      std::shared_ptr<Button>(new Button());

  test_element_ptr->size_x = 100;
  test_element_ptr->size_y = 50;
  test_element_ptr->x_pos = 10;
  test_element_ptr->y_pos = 50;
  test_element_ptr->label = "Run";

  std::shared_ptr<GuiPanel> input_table_panel_ptr =
      std::shared_ptr<GuiPanel>(new GuiPanel());

  // define the size and scale of the panel
  input_table_panel_ptr->size_x = X_RES / 2;
  input_table_panel_ptr->size_y = 800;
  input_table_panel_ptr->screen_x_pos = X_RES / 4;
  input_table_panel_ptr->screen_y_pos = 400;
  input_table_panel_ptr->visible = true;
  input_table_panel_ptr->buttons = {test_element_ptr};

  return {input_table_panel_ptr};
}
