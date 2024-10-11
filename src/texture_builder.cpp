#include <stdio.h>
#include <cassert>
#include <string>
#include <unordered_map>

#include "colour.hpp"
#include "texture_builder.hpp"

// todo use shared pointes in the caches
std::unordered_map<Uint32, SDL_Texture*> glyph_texture_cache = {};
std::unordered_map<std::string, SDL_Texture*> text_texture_cache = {};

SDL_Texture* build_accelerated_texture(SDL_Renderer* renderer,
                                       SDL_Surface* surface) {
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == nullptr) {
    printf("Error loading texture from surface!");
    assert(false);
  }

  return texture;
}
SDL_Texture* get_accelerated_glyph_texture(SDL_Renderer* renderer,
                                           TTF_Font* font, Uint32 glyph_char,
                                           Colour foreground_colour) {

  // See if the glyph cache contains the glyph texture we want. If present, simply return it
  if (glyph_texture_cache.find(glyph_char) != glyph_texture_cache.end()) {
    return glyph_texture_cache[glyph_char];
  }

  // load the glyph character to a surface
  SDL_Surface* glyph_surface = TTF_RenderGlyph32_Solid(
      font, glyph_char, lookup_sdl_colour(foreground_colour));

  if (glyph_surface == nullptr) {
    printf("Error loading surface for glyph \"%c\"", glyph_char);
    assert(false);
  }

  // create a hardware accelerated texture from the surface and destroy the surface.
  SDL_Texture* glyph_texture =
      build_accelerated_texture(renderer, glyph_surface);

  SDL_FreeSurface(glyph_surface);

  // add the new glyph texture to the cache
  glyph_texture_cache[glyph_char] = glyph_texture;

  return glyph_texture;
}

SDL_Texture* get_accelerated_text_texture(SDL_Renderer* renderer,
                                          TTF_Font* font, std::string text,
                                          Colour foreground_colour) {
  // See if the texture cache contains the string texture we want. If present, simply return it
  if (text_texture_cache.find(text) != text_texture_cache.end()) {
    return text_texture_cache[text];
  }

  // load the string to a surface
  SDL_Surface* text_surface = TTF_RenderText_Solid(
      font, text.c_str(), lookup_sdl_colour(foreground_colour));

  if (text_surface == nullptr) {
    printf("Error loading surface for text \"%s\"", text.c_str());
    assert(false);
  }

  SDL_Texture* text_texture = build_accelerated_texture(renderer, text_surface);

  SDL_FreeSurface(text_surface);

  // add the new glyph texture to the cache
  text_texture_cache[text] = text_texture;

  return text_texture;
}

void clear_glyph_texture_cache() {
  for (auto x : glyph_texture_cache) {
    SDL_DestroyTexture(x.second);
  }
  glyph_texture_cache.clear();
}

void clear_text_texture_cache() {
  for (auto x : text_texture_cache) {
    SDL_DestroyTexture(x.second);
  }
  text_texture_cache.clear();
}
