#include <SDL2/SDL_image.h>

#include "texture.hpp"


SDL_Texture* TextureBuilder::build_texture_from_image(const std::string& img_path, const SDL_Renderer& renderer){
  //load a surface
  SDL_Surface* surface = IMG_Load(img_path.c_str());

  if(surface == nullptr){
    std::cout<< "error loading image to surface: "<< SDL_GetError() << "\n";
    return nullptr;
  }
  
  //convert the surface to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(texture == nullptr){
     std::cout<< "error converting surface to texture: "<< SDL_GetError() << "\n";
     return nullptr;
  }
  
  //destroy the surface
  SDL_FreeSurface(surface);

  return texture;
}

