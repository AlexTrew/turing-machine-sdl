#include "rendered-glyph.hpp"


RenderedGlyphBuilder::~RenderedGlyphBuilder(){
  SDL_DestroyTexture(m_rendered_glyph);
}


 RenderedGlyphBuilder::run(SDL_Renderer& renderer, char glyph, SDL_Color text_color){
 
  // load the font for the glyph
  TTF_Font* font = TTF_OpenFont( "Ubuntu-Regular.ttf", 12);
  if(font == nullptr){
    std::cout << "error loading ttf: " <<  TTF_GetError() << std::endl;
  }
  
  // load the glyph as a surface
  SDL_Surface* surface = TTF_RenderText_Solid(font, glyph, text_color);
  if(surface == nullptr){
    std::cout << "error loading rendered text surface! "<< SDL_GetError() << "\n";
  }

  // create a hardware accelerated texture from the surface
  rendered_glyph = SDL_CreateTextureFromSurface(renderer, surface);
  if(rendered_glyph == nullptr){
    std::cout << "error converting glyph surface to texture! "<< SDL_GetError() << "\n"; 
  }

  SDL_FreeSurface(surface);
  TTF_CloseFont(font);

  return rendered_glyph;
}
