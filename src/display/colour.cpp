#include "colour.hpp"
#include <sys/types.h>
#include <exception>

SDL_Colour lookup_sdl_colour(Colour colour_name) {
  switch (colour_name) {
    case Colour::BLACK:
      return SDL_Colour{0, 0, 0};
    case Colour::WHITE:
      return SDL_Colour{255, 255, 255};
    case Colour::GREY:
      return SDL_Colour{220, 220, 220};
  }
}
