#define RENDERED_TEXT
#ifndef RENDERED_TEXT
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* get_rendered_text(const char* text) {
  SDL_Surface* glyph_surface =
      TTF_RenderGlyph32_Solid(font, glyph_char, *foreground_colour);

  if (glyph_surface == nullptr) {
    printf("Error loading surface for glyph \"%c\"", glyph_char);
    assert(false);
  }

  // create a hardware accelerated texture from the surface and destroy the surface.
  SDL_Texture* text_texture =
      SDL_CreateTextureFromSurface(renderer, glyph_surface);

  SDL_FreeSurface(glyph_surface);

  if (text_texture == nullptr) {
    printf("Error loading texture from surface for glyph \"%c\"", glyph_char);
    assert(false);
  }

  glyph_texture_cache[glyph_char] = text_texture;

  return glyph_texture;
}

#endif
