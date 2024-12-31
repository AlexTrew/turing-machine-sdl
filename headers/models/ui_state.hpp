#ifndef UI_STATE
#define UI_STATE
#include <memory>
#include "headers/views/ui.hpp"

struct UIState {
  std::vector<std::shared_ptr<GuiPanel>> ui_panels = {};
};

#endif
