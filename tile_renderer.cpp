#include "tile_renderer.hpp"

TileRenderer::TileRenderer(SDL_Renderer* renderer){
  _renderer = renderer;
}

void TileRenderer::run(int x_pos, int y_pos, int w, int h, SDL_Texture* texture) {
  SDL_Rect tile = {x_pos, y_pos, w, h};
  SDL_RenderCopy(_renderer, texture, nullptr, &tile);
}
