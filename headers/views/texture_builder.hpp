#ifndef TEXTURE_BUILDER
#define TEXTURE_BUILDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "headers/util/colour.hpp"
SDL_Texture* get_accelerated_glyph_texture(SDL_Renderer* renderer,
                                           TTF_Font* font, Uint32 glyph_char,
                                           Colour foreground_colour);

SDL_Texture* get_accelerated_text_texture(SDL_Renderer* renderer,
                                          TTF_Font* font, std::string text,
                                          Colour foreground_colour);

// make sure you call this at the end of the program!
void clear_glyph_texture_cache();
#endif
