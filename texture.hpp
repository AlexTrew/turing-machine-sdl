# IFNDEF TEXTURE

#include <SDL2/SDL.h>
class TextureBuilder{
public:
  SDL_Texture* load_texture(std::string img_path, SDL_Renderer* renderer);
}


# ENDIF
