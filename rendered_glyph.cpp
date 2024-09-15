#include "rendered_glyph.hpp"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <stdio.h>
#include <cassert>
#include <unordered_map>

std::unordered_map<Uint32, SDL_Texture*> glyph_texture_cache = {};

SDL_Texture* get_glyph_texture(SDL_Renderer* renderer, TTF_Font* font,
                               Uint32 glyph_char, SDL_Colour* foreground_colour,
                               SDL_Colour* background_colour) {

  // See if the glyph cache contains the glyph texture we want. If present, simply return it
  if (glyph_texture_cache.find(glyph_char) != glyph_texture_cache.end()) {
    return glyph_texture_cache[glyph_char];
  }

  // load the glyph character to a surface
  SDL_Surface* glyph_surface =
      TTF_RenderGlyph32_Solid(font, glyph_char, *foreground_colour);

  if (glyph_surface == nullptr) {
    printf("Error loading surface for glyph \"%c\"", glyph_char);
    assert(false);
  }

  // create a hardware accelerated texture from the surface and destroy the surface.
  SDL_Texture* glyph_texture =
      SDL_CreateTextureFromSurface(renderer, glyph_surface);

  SDL_FreeSurface(glyph_surface);

  if (glyph_texture == nullptr) {
    printf("Error loading texture from surface for glyph \"%c\"", glyph_char);
    assert(false);
  }

  // add the new glyph texture to the cache
  glyph_texture_cache[glyph_char] = glyph_texture;

  return glyph_texture;
}

void clear_glyph_texture_cache() {
  for (auto x : glyph_texture_cache) {
    SDL_DestroyTexture(x.second);
  }
  glyph_texture_cache.clear();
}
