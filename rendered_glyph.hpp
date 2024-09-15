#ifndef RENDERED_GLYPH
#define RENDERED_GLYPH

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>

SDL_Texture* get_glyph_texture(SDL_Renderer* renderer, TTF_Font* font,
                               Uint32 glyph_char, SDL_Colour* foreground_colour,
                               SDL_Colour* background_colour);

// make sure you call this at the end of the program!
void clear_glyph_texture_cache();
#endif
