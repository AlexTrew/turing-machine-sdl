#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "rendered_glyph.hpp"
#include "turing_machine.hpp"
#include "tile_renderer.hpp"

const int X_RES = 1920;
const int Y_RES = 1080;

void close(SDL_Window* window, SDL_Renderer* renderer){
  // close sdl image and sdl ttf
  IMG_Quit();
  TTF_Quit();

  //free memory from window and renderer
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void create_tile(SDL_Renderer* renderer, int x, int y, int w, int h){
  SDL_Rect new_viewport;
  new_viewport.x = x;
  new_viewport.y = y;
  new_viewport.w = w;
  new_viewport.h = h;

  SDL_RenderSetViewport(renderer, &new_viewport);
}


void run_event_loop(SDL_Window* window, SDL_Renderer* renderer){



  //turing machine utils
  std::vector<char> tm_state = std::vector<char>(50, '0');
  TuringMachine* turing_machine = new TuringMachine();
  RenderedGlyphBuilder* glyph_builder = new RenderedGlyphBuilder();
  TileRenderer* tile_renderer = new TileRenderer(renderer);
  int head_position = 30;

  const char* head_glyph_char = "H";
  SDL_Texture* head_glyph = glyph_builder->run(renderer, head_glyph_char, {0,0,0});


  // event loop state
  bool quit = false;
  SDL_Event e;


  while(!quit){
    while(SDL_PollEvent(&e) != 0){
      //user requests quit
      if(e.type == SDL_QUIT){
	quit = true;
      }

      head_position = turing_machine->process(tm_state, head_position);
      std::vector<SDL_Texture* > tm_state_glyphs; 

      //draw the state on screen
      SDL_RenderClear(renderer);
      
      for(int i=0; i<tm_state.size(); ++i){
	// i know this is nowhere near a good way of doing this.
	//make the glyphs once, then load them. destroy them after the loop (duh)

	// jesus christ
	char glyph_char_buff[2];
	memcpy(glyph_char_buff, &tm_state[i], 1);
	glyph_char_buff[1] = '\0';

	

	SDL_Texture* glyph = glyph_builder->run(renderer, glyph_char_buff, {0,0,0});
	tm_state_glyphs.push_back(glyph);
	tile_renderer->run(i*50, 500, 50, 70, glyph);
      }

      // draw the 'H' for head
      tile_renderer->run(head_position*50, 570, 50, 70, head_glyph);
      SDL_RenderPresent(renderer);

      //free the textures 
      for (int i=0; i<tm_state_glyphs.size(); ++i){
	SDL_DestroyTexture(tm_state_glyphs[i]);
      }

    }
   
 }

 delete turing_machine;
 delete glyph_builder;
 delete tile_renderer;

}


int main(int argc, char** argv){
  //init sdl subsytems
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("Error intialising SDL2! Error: %s\n", SDL_GetError());
    return -1;
  }

  //Initialize SDL_ttf so we can support the font we are using for the glyphs
  if( TTF_Init() == -1 )
    {
      printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
      return -1;
    }

  //initialise SDL_Image so we can support common image formats
  if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
    printf( "SDL_IMG could not initialize! SDL_ttf Error: %s\n", IMG_GetError() );
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("Turing Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, X_RES, Y_RES, SDL_WINDOW_SHOWN);
  if(window == nullptr){
    printf("Window could not be initialised! %s\n", SDL_GetError());
    close(window, nullptr);
    return -1;
  }

    
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == nullptr){
      printf("Error creating renderer! %s\n", SDL_GetError());
      close(window, nullptr);
      return -1;
  }


  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF , 0xFF);

  run_event_loop(window, renderer);
  
  close(window, renderer);
 
  return 0;
}

