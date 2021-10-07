#include <stdio.h>
#include <SDL2/SDL.h>

// SDL error checker
void i_sec(int code)
{
  if (code < 0){
    fprintf(stderr, "SDL had an errror: %s", SDL_GetError());
    exit(1);
  }
}

void * p_sec(void * code)
{
  if (code == NULL){
    fprintf(stderr, "SDL had an errror: %s", SDL_GetError());
    exit(1);
  }
  return code;
}

struct App{
  enum states{
	     QUIT,
	     RUN
  }state;
};

int main(int argc, char *argv[]){
  i_sec(SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window = p_sec(SDL_CreateWindow("Graph",
					   0,0,800,600,
					   SDL_WINDOW_RESIZABLE));
  SDL_Renderer *renderer =
    p_sec(SDL_CreateRenderer(window,
			     -1,
			     SDL_RENDERER_ACCELERATED));
  struct App app = {
		    .state = RUN,	    
  };
  SDL_Event event;
  while(app.state != QUIT){
    while(SDL_PollEvent(&event))
      {
	switch(event.type){
	case SDL_QUIT: {
	  app.state = QUIT;
	}break;
	}
      }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
