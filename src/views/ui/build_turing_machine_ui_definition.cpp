#include "headers/views/turing_ui_def.hpp"

std::vector<std::shared_ptr<GuiPanel>> build_turing_machine_ui_definition() {

  std::shared_ptr<Button> test_button_ptr =
      std::shared_ptr<Button>(new Button("Run", 300, 30, 100, 50));

  std::shared_ptr<GuiPanel> input_table_panel_ptr =
      std::shared_ptr<GuiPanel>(new GuiPanel("", true, 800, 400, X_RES / 4,
                                             Y_RES / 4, {}, {test_button_ptr}));

  return {input_table_panel_ptr};
}
