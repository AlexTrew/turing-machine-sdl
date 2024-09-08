#ifndef TILE_RENDERER
#define TILE_RENDERER
#include <SDL2/SDL.h>

class TileRenderer{
  SDL_Renderer* _renderer;
public:
  TileRenderer(SDL_Renderer* renderer);
  void run(int x_pos, int y_pos, int w, int h, SDL_Texture* texture);
};

#endif
