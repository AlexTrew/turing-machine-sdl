#ifndef RENDERED_GLYPH
#define RENDERED_GLYPH


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class RenderedGlyphBuilder{
public:
  SDL_Texture* run(SDL_Renderer *renderer, const char *glyph, SDL_Color text_color); 
};

#endif

