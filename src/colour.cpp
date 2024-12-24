#include "colour.hpp"
#include <SDL2/SDL_pixels.h>
#include <sys/types.h>
#include <exception>
#include <unordered_map>

std::unordered_map<Colour, SDL_Colour> colour_lookup = {
    {Colour::BLACK, {0, 0, 0}},
    {Colour::WHITE, {255, 255, 255}},
    {Colour::GREY, {220, 220, 220}},
};

SDL_Colour lookup_sdl_colour(Colour colour_name) {
  return colour_lookup[colour_name];
};
