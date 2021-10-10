#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define BUTTON_COUNT 4
#define BUTTON_HEIGHT 50
#define BUTTON_X_MARGIN 10
#define BUTTON_Y_MARGIN 5
#define MSG_HEIGHT 50

#define COLOR_DEF_R 0xFF
#define COLOR_DEF_G 0xFF
#define COLOR_DEF_B 0xFF
#define COLOR_DEF_A 0xFF

#define COLOR_FOC_R 0xDA
#define COLOR_FOC_G 0x70
#define COLOR_FOC_B 0xD6
#define COLOR_FOC_A 0x80

#define COLOR_SEL_R 0xF0
#define COLOR_SEL_G 0x60
#define COLOR_SEL_B 0x60
#define COLOR_SEL_A 0x80

TTF_Font *font_22;
TTF_Font *font_52;

// SDL error checker
void i_sec(int code)
{
  if (code < 0){
    fprintf(stderr, "SDL had an errror: %s\n", SDL_GetError());
    exit(1);
  }
}

void * p_sec(void * code)
{
  if (code == NULL){
    fprintf(stderr, "SDL had an errror: %s\n", SDL_GetError());
    exit(1);
  }
  return code;
}

struct App
{
  int window_width;
  int window_height;
  
  enum states{
	      QUIT,
	      RUN,
	      SELECT,
	      ADD_NODE,
	      ADD_EDGE
  } state;
  
  SDL_Rect canvas;
  SDL_Rect UI;

  int cursor_x;
  int cursor_y;

  struct Button *buttons;
  int hovered_button;
  int selected_button;

  Uint32 mouse_click;
} app;

struct Button
{
  char *label;
  SDL_Rect pos;
  void (*callback)(struct App *app);
  int focused;
};

enum justify {
  TOP_LEFT,
  MIDDLE
};

void click_select(struct App *app)
{
  app->selected_button = 0;
  app->state = SELECT;
}

void click_delete(struct App *app)
{
  app->selected_button = 1;
  SDL_Delay(100);
  app->selected_button = 0;
}

void click_add_node(struct App *app)
{
  app->selected_button = 2;
  app->state = ADD_NODE;
}

void click_add_edge(struct App *app)
{
  app->selected_button = 3;
  app->state = ADD_EDGE;
}

void displaytext(SDL_Renderer *renderer, const char *text,
		 int x, int y, enum justify anchor, TTF_Font *font,
		 SDL_Color color)
{
  SDL_Surface *surface =
    p_sec(TTF_RenderText_Blended(font, text, color));
  SDL_Texture *texture =
    p_sec(SDL_CreateTextureFromSurface(renderer, surface));
  int w = 0;
  int h = 0;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect dstrect = {x, y, w, h};
  switch (anchor) {
  case TOP_LEFT: {
  } break;
  case MIDDLE: {
    dstrect.x = x - w/2;
    dstrect.y = y - h/2;
  } break;
  }
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void event_handler(struct App *app, SDL_Event event){
  switch (event.type) {
  case SDL_MOUSEMOTION: {
    int tmp_button = -1;
    for (int i = 0; i < BUTTON_COUNT; i++){
      int x0 = ((app->buttons)+i)->pos.x;
      int y0 = ((app->buttons)+i)->pos.y;
      int x1 = x0 + ((app->buttons)+i)->pos.w;
      int y1 = y0 + ((app->buttons)+i)->pos.h;
      if (x0 <= event.motion.x &&
	  event.motion.x <= x1 &&
	  y0 <= event.motion.y &&
	  event.motion.y <= y1){
	tmp_button = i;
	break;
      }
    }
    app->hovered_button = tmp_button;
  } break;
  }
}

void render_buttons(struct App *app, SDL_Renderer *renderer){
  int button_width = app->window_width / BUTTON_COUNT;
  for( int i = 0; i < BUTTON_COUNT; i++){
    ((app->buttons) + i)->pos.x = BUTTON_X_MARGIN + i * button_width;
    ((app->buttons) + i)->pos.y = BUTTON_Y_MARGIN + app->canvas.h;
    ((app->buttons) + i)->pos.w = button_width - 2 * BUTTON_X_MARGIN;
    ((app->buttons) + i)->pos.h = BUTTON_HEIGHT - BUTTON_Y_MARGIN;
    SDL_Rect rect = (((app->buttons) + i)->pos);
    if (i == app->hovered_button){
      SDL_SetRenderDrawColor(renderer,
			     COLOR_FOC_R,
			     COLOR_FOC_G,
			     COLOR_FOC_B,
			     COLOR_FOC_A);
      SDL_RenderFillRect(renderer, &rect);
    }
    if (i == app->selected_button) {
      SDL_SetRenderDrawColor(renderer,
			     COLOR_SEL_R,
			     COLOR_SEL_G,
			     COLOR_SEL_B,
			     COLOR_SEL_A);
      SDL_RenderFillRect(renderer, &rect);
    }
    if (i != app->hovered_button &&
	   i != app->selected_button) {
      SDL_SetRenderDrawColor(renderer,
			     COLOR_DEF_R,
			     COLOR_DEF_G,
			     COLOR_DEF_B,
			     COLOR_DEF_A);
      SDL_RenderFillRect(renderer, &rect);
    }
    
    SDL_Color textcolor = { 10, 10, 10, 255};
    displaytext(renderer, ((app->buttons) + i)->label,
	        i * button_width + button_width / 2,
		((app->buttons) + i)->pos.y + BUTTON_HEIGHT / 2,
		MIDDLE, font_22, textcolor);

  }
}


int main(int argc, char *argv[]){
  struct Button select_button = {
			   "Select",
			   {0, 0, 0, 0},
			   click_select,
			   0
  };

  struct Button delete_button = {
			   "Delete",
			   {0, 0, 0, 0},
			   click_delete,
			   0
  };

  struct Button add_node_button = {
			   "Add node",
			   {0, 0, 0, 0},
			   click_add_node,
			   0
  };

  struct Button add_edge_button = {
			   "Add edge",
			   {0, 0, 0, 0},
			   click_add_edge,
			   0
  };

  
  struct Button buttons[] = {
			     select_button,
			     delete_button,
			     add_node_button,
			     add_edge_button
  };
  app.buttons = (struct Button*)&buttons;
    
  i_sec(SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window =
    p_sec(SDL_CreateWindow("Graph", 0,0,800,600,
			   SDL_WINDOW_RESIZABLE));
  SDL_GetWindowSize(window, &app.window_width, &app.window_height);
  
  SDL_Renderer *renderer =
    p_sec(SDL_CreateRenderer(window, -1,
			     SDL_RENDERER_ACCELERATED |
			     SDL_RENDERER_PRESENTVSYNC));
  i_sec(SDL_SetRenderDrawBlendMode(renderer,
				   SDL_BLENDMODE_ADD));
  
  app.canvas.x = 0;
  app.canvas.y = 0;
  app.canvas.w = app.window_width;
  app.canvas.h = app.window_height - (BUTTON_HEIGHT +  MSG_HEIGHT);

  app.UI.x = 0;
  app.UI.y = app.canvas.y;
  app.UI.w = app.window_width;
  app.UI.h = (BUTTON_HEIGHT + MSG_HEIGHT);
  
  SDL_Event event;
  app.state = RUN;
  app.hovered_button = -1;

  i_sec(TTF_Init());
  font_22 = p_sec(TTF_OpenFont("NotoSansDisplay-Regular.ttf", 22));
  font_52 = p_sec(TTF_OpenFont("NotoSansDisplay-Regular.ttf", 52));
  
  while(app.state != QUIT){
    while(SDL_PollEvent(&event))
      {
	switch(event.type){
	case SDL_QUIT: {
	  app.state = QUIT;
	} break;
	case SDL_WINDOWEVENT: {
	  if (event.window.event == SDL_WINDOWEVENT_RESIZED){
	    SDL_GetWindowSize(window,
			      &app.window_width, &app.window_height);
	    app.canvas.h = app.window_height -
	      (BUTTON_HEIGHT +  MSG_HEIGHT);
	    app.UI.h = (BUTTON_HEIGHT + MSG_HEIGHT);	
	  }
	} break;
        default: {
	  event_handler(&app, event);
	} break;
	}
      }

    app.mouse_click = SDL_GetMouseState(&app.cursor_x,
					&app.cursor_y);
    if(((app.mouse_click & SDL_BUTTON_LMASK) != 0) &&
       app.hovered_button != -1){
      app.buttons[app.hovered_button].callback(&app);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    render_buttons(&app, renderer);
    
    if (app.selected_button >= 0 &&
		 app.selected_button < BUTTON_COUNT){
      
    }

    SDL_Rect rect1 = {0, 0, 100, 100};
    SDL_Rect rect2 = {100, 0, 100, 100}; 
    SDL_Rect rect3 = {200, 0, 100, 100};
    SDL_SetRenderDrawColor(renderer,
			   255,
			   0,
			   0,
			   50);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect3);
    SDL_SetRenderDrawColor(renderer,
			   0,
			   255,
			   0,
			   10);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
    SDL_RenderPresent(renderer);
  }
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
