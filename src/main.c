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

enum states{
	    QUIT,
	    RUN,
	    ADD_NODE
} state;

struct Button{
  int x, y, w, h;
  SDL_Color color;
  void (*callback)(void);
};

void buttontest(){
  printf("ohh yah\n");
}

int main(int argc, char *argv[]){
  struct Button button1 = {
			  400,
			  400,
			  80,
			  40,
			  { 0xFF,
			    0xFF,
			    0xFF,
			    0xFF
			  },
			  buttontest
  };

  struct Button button2 = {
			  500,
			  400,
			  80,
			  40,
			  { 0xFF,
			    0xFF,
			    0xFF,
			    0xFF
			  },
			  buttontest
  };

  void *elements[] = { &button1, &button2 };

  i_sec(SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window = p_sec(SDL_CreateWindow("Graph",
					   0,0,800,600,
					   SDL_WINDOW_RESIZABLE));
  SDL_Renderer *renderer =
    p_sec(SDL_CreateRenderer(window,
			     -1,
			     SDL_RENDERER_ACCELERATED));
  SDL_Event event;
  state = RUN;
  while(state != QUIT){
    while(SDL_PollEvent(&event))
      {
	switch(event.type){
	case SDL_QUIT: {
	  state = QUIT;
	}break;
	}
      }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for( int i = 0; i < 2; i++){
      struct Button *btn = ((struct Button*)elements[i]);
      struct SDL_Rect rect = {
			      btn->x,
			      btn->y,
			      btn->w,
			      btn->h
      };
      SDL_SetRenderDrawColor(renderer, btn->color.r,
			     btn->color.g,
			     btn->color.b,
			     btn->color.a);
      SDL_RenderFillRect(renderer, &rect);
      
    }
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
