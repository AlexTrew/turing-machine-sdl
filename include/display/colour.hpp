#ifndef COLOUR
#define COLOUR
#include <SDL2/SDL_pixels.h>

enum class Colour { BLACK, WHITE, GREY };

SDL_Colour lookup_sdl_colour(Colour colour_name);

#endif
