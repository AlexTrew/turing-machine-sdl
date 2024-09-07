#ifndef RENDERED_GLYPH
#define RENDERED_GLYPH


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class RenderedGlyphFactory{
public:
  void run(SDL_Renderer& renderer, char glyph, SDL_Color text_color); 
};

#endif

