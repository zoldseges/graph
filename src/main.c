#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define BUTTON_COUNT 3

TTF_Font *font;

int pressed_button = -1;

void button1_pressed(void){
  pressed_button = 0;
}

void button2_pressed(void){
  pressed_button = 1;
}

void button3_pressed(void){
  pressed_button = 2;
}

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
	      RUN,
	      ADD_NODE
  } state;
  int hover_button;
} app;


struct Button{
  int x, y, w, h;
  SDL_Color color;
  void (*callback)(void);
  int focused;
};

void displaytext(SDL_Renderer *renderer, const char *text,
		int x, int y){
  SDL_Color bg = {255, 0, 0, 255};
  SDL_Color fg = {  0, 0, 0, 255};

  SDL_Surface *surface = TTF_RenderText_Shaded(font, text,
					       bg, fg);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,
						      surface);
  int w = 0;
  int h = 0;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect dstrect = {x, y, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
						  
}

void event_handler(SDL_Event event, struct App *app, struct Button buttons[]){
  switch (event.type) {
  case SDL_MOUSEMOTION: {
    int tmp_button = -1;
    for (int i = 0; i < BUTTON_COUNT; i++){
      int x0 = buttons[i].x;
      int y0 = buttons[i].y;
      int x1 = x0 + buttons[i].w;
      int y1 = y0 + buttons[i].h;
      if (x0 <= event.motion.x && event.motion.x <= x1 && y0 <= event.motion.y && event.motion.y <= y1){
	tmp_button = i;
	break;
      }
    }
    app->hover_button = tmp_button;
  } break;
  }
}

int main(int argc, char *argv[]){
  struct Button button1 = {
			   200,
			   400,
			   80,
			   40,
			   { 0xFF,
			     0xFF,
			     0xFF,
			     0xFF
			   },
			   button1_pressed,
			   0
  };

  struct Button button2 = {
			   300,
			   400,
			   80,
			   40,
			   { 0xFF,
			     0xFF,
			     0xFF,
			     0xFF
			   },
			   button2_pressed,
			   0
  };

  struct Button button3 = {
			   400,
			   400,
			   80,
			   40,
			   { 0xFF,
			     0xFF,
			     0xFF,
			     0xFF
			   },
			   button3_pressed,
			   0
  };

  
  struct Button buttons[] = { button1, button2, button3 };

  i_sec(SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window = p_sec(SDL_CreateWindow("Graph",
					   0,0,800,600,
					   SDL_WINDOW_RESIZABLE));
  SDL_Renderer *renderer =
    p_sec(SDL_CreateRenderer(window,
			     -1,
			     SDL_RENDERER_ACCELERATED));
  SDL_Event event;
  app.state = RUN;
  app.hover_button = -1;

  int cursor_x;
  int cursor_y;
  Uint32 mousebutton;

  // TODO: error check
  TTF_Init();
  font = TTF_OpenFont("NotoSansDisplay-Regular.ttf", 21);
  while(app.state != QUIT){
    while(SDL_PollEvent(&event))
      {
	switch(event.type){
	case SDL_QUIT: {
	  app.state = QUIT;
	}break;
        default: {
	  event_handler(event, &app, buttons);
	} break;
	}
      }

    mousebutton = SDL_GetMouseState(&cursor_x, &cursor_y);
    if(((mousebutton & SDL_BUTTON_LMASK) != 0) &&
       app.hover_button != -1){
      buttons[app.hover_button].callback();
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for( int i = 0; i < BUTTON_COUNT; i++){
      struct Button *btn = &buttons[i];
      struct SDL_Rect rect = {
			      btn->x,
			      btn->y,
			      btn->w,
			      btn->h
      };
      if (i == app.hover_button){
	SDL_SetRenderDrawColor(renderer, 255,
			       0,
			       0,
			       255);
      } else {
	SDL_SetRenderDrawColor(renderer, btn->color.r,
			       btn->color.g,
			       btn->color.b,
			       btn->color.a);
      }
      SDL_RenderFillRect(renderer, &rect);
      
    }

    if (pressed_button >= 0 && pressed_button < BUTTON_COUNT){
      int x = buttons[pressed_button].x;
      int y = buttons[pressed_button].y - 50;
      displaytext(renderer, "Pressed", x, y);
    }
    pressed_button = -1;
    
    SDL_RenderPresent(renderer);
  }
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
