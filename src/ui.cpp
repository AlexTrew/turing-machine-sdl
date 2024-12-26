#include "ui.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "colour.hpp"
#include "texture_builder.hpp"

void draw_gui_button(const std::shared_ptr<Button>& gui_panel_element_ptr,
                     TTF_Font* label_font, SDL_Renderer* renderer) {
  SDL_Rect button_rect;
  button_rect.x = gui_panel_element_ptr->x_pos;
  button_rect.y = gui_panel_element_ptr->y_pos;
  button_rect.w = gui_panel_element_ptr->size_x;
  button_rect.h = gui_panel_element_ptr->size_y;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawRect(renderer, &button_rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  SDL_Texture* label_texture = get_accelerated_text_texture(
      renderer, label_font, gui_panel_element_ptr->label, Colour::WHITE);
  SDL_RenderCopy(renderer, label_texture, nullptr, &button_rect);
}

void draw_gui_panel(const std::shared_ptr<GuiPanel>& gui_panel_ptr,
                    TTF_Font* label_font, SDL_Renderer* renderer) {

  SDL_Rect panel_rect;
  panel_rect.x = gui_panel_ptr->screen_x_pos;
  panel_rect.y = gui_panel_ptr->screen_y_pos;
  panel_rect.w = gui_panel_ptr->size_x;
  panel_rect.h = gui_panel_ptr->size_y;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawRect(renderer, &panel_rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  /* Set the viewport the panel panel rect and draw the elements within that viewport,
     so they can be moved around within the panel and not be drawn outside of it.
   */

  SDL_Rect previous_viewport;
  SDL_RenderGetViewport(renderer, &previous_viewport);

  SDL_RenderSetViewport(renderer, &panel_rect);
  for (std::shared_ptr<Button>& button_ptr : gui_panel_ptr->buttons) {
    draw_gui_button(button_ptr, label_font, renderer);
  }

  // reset the viewport
  SDL_RenderSetViewport(renderer, &previous_viewport);
}

void draw_gui(const std::vector<std::shared_ptr<GuiPanel>>& gui_panels,
              TTF_Font* gui_font, SDL_Renderer* renderer) {
  for (const std::shared_ptr<GuiPanel>& gui_panel_ptr : gui_panels) {
    if (gui_panel_ptr->visible)
      draw_gui_panel(gui_panel_ptr, gui_font, renderer);
  };
};
