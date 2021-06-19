#include <math.h>

extern "C"
{
#include "helper.h"
}

#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED   255,0,0,255

int ww;
int wh;

SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *bg		= NULL;
SDL_Rect 	bg_dst;

SDL_Texture    *slot		= NULL;
SDL_Rect 	slot_dst;

SDL_Texture    *fillbar		= NULL;
SDL_Rect 	fillbar_dst;

SDL_Texture    *button		= NULL;
SDL_Rect 	button_dst;

SDL_Texture    *shadow_top	= NULL;
SDL_Rect 	shadow_top_dst;

SDL_Texture    *shadow_bot	= NULL;
SDL_Rect 	shadow_bot_dst;

SDL_Rect 	button_bounds_dst;

TTF_Font       *font		= NULL;
SDL_Color color={255,0,0,255};
SDL_Texture    *text		= NULL;
SDL_Rect 	text_dst;

int value;
char string[4];

SDL_Point	mouse;
SDL_bool 	mouse_follow	= SDL_FALSE;
SDL_Point 	mouse_offset;

void assets_in	 (void);
void assets_out	 (void);
void render_value(void);
void get_value	 (void);

SDL_Window   	*Window	  = NULL;
SDL_Renderer 	*Renderer = NULL;

int main()
{
	Window = createWindow();
	Renderer = createRenderer(Window);

	assets_in();

	SDL_SetWindowPosition(Window,0,0);
	SDL_SetWindowSize(Window,ww,wh);
	SDL_SetWindowTitle(Window, "SDL2 Slider");
	SDL_ShowWindow(Window);

	SDL_Event event;
	int running = 1;

	while(running){

		SDL_GetMouseState(&mouse.x, &mouse.y);
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				running =0;
			}
			if(event.type == SDL_MOUSEMOTION){
				;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == SDL_BUTTON_RIGHT){
					;
				}
				if(event.button.button == SDL_BUTTON_MIDDLE){
					;
				}
				if(event.button.button==SDL_BUTTON_LEFT){
					if( event.button.button==SDL_BUTTON_LEFT && SDL_PointInRect(&mouse, &button_dst) &&!mouse_follow ){
						mouse_offset.y=mouse.y-button_dst.y;
						mouse_follow=SDL_TRUE;
					}
				}
			}
			if( mouse_follow && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT){
				mouse_follow=SDL_FALSE;
			}
			if(event.type == SDL_KEYDOWN ){
				switch(event.key.keysym.sym ){
					case SDLK_ESCAPE:
						running =0;
						break;

					case SDLK_r:
					case SDLK_BACKSPACE:
						break;

					case SDLK_p:	
					case SDLK_SPACE:
						break;
					
					default:
						break;
				}
			}
		}

		if (mouse_follow){
			button_dst.y = mouse.y-mouse_offset.y;

			//BOUNDS CHECK BUTTON
			//TOP
			if (button_dst.y <= button_bounds_dst.y)
				button_dst.y = button_bounds_dst.y;
			//BOT
			if (button_dst.y+button_dst.h >= button_bounds_dst.y +  button_bounds_dst.h)
				button_dst.y = (button_bounds_dst.y + button_bounds_dst.h)-button_dst.h;
		
			//BOUNDS CHECK shadow top
			shadow_top_dst.y=button_dst.y+button_dst.h;
			if (shadow_top_dst.y+shadow_top_dst.h >= slot_dst.y +  slot_dst.h)
				shadow_top_dst.y = (slot_dst.y +  slot_dst.h)-shadow_top_dst.h;
		
			fillbar_dst.y=button_dst.y+(button_dst.h/2);
			fillbar_dst.h=(slot_dst.y+slot_dst.h)-(button_dst.y+button_dst.h/2);

			get_value();
			render_value();
		}
		//BEGIN RENDERING
		SDL_SetRenderDrawColor(Renderer, WHITE);
		SDL_RenderClear(Renderer);

		SDL_RenderCopy(Renderer, bg, NULL, &bg_dst);
		SDL_RenderCopy(Renderer, slot, NULL, &slot_dst);
		SDL_RenderCopy(Renderer, fillbar, NULL, &fillbar_dst);
		SDL_RenderCopy(Renderer, shadow_top, NULL, &shadow_top_dst);
		SDL_RenderCopy(Renderer, shadow_bot, NULL, &shadow_bot_dst);
		SDL_RenderCopy(Renderer, button, NULL, &button_dst);
		SDL_RenderCopy(Renderer, text, NULL, &text_dst);
		SDL_RenderPresent(Renderer);
		//END   RENDERING
	}

	assets_out();
	exit_(Window, Renderer);

	return 0;
}

void assets_in(void)
{
	//BEGIN BG
	temp_surface = IMG_Load("./assets/gfx/bg.png");
	bg = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(bg, NULL, NULL, &bg_dst.w, &bg_dst.h);
	ww=bg_dst.w;
	wh=bg_dst.h;
	bg_dst.x=0;
	bg_dst.y=0;
	//END 	BG

	//BEGIN BUTTON
	temp_surface = IMG_Load("./assets/gfx/button.png");
	button = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(button, NULL, NULL, &button_dst.w, &button_dst.h);
	button_dst.x=(120)-(button_dst.w/2);
	button_dst.y=(wh/2)-(button_dst.h/2);
	//END 	BUTTON
		
	//BEGIN SLOT
	temp_surface = IMG_Load("./assets/gfx/slot.png");
	slot = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(slot, NULL, NULL, &slot_dst.w, &slot_dst.h);
	slot_dst.x=(120)-(slot_dst.w/2);
	slot_dst.y=(wh/2)-(slot_dst.h/2);
	//END 	SLOT
	
	//BEGIN FILLBAR
	temp_surface = IMG_Load("./assets/gfx/fillbar.png");
	fillbar = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(fillbar, NULL, NULL, &fillbar_dst.w, &fillbar_dst.h);
	fillbar_dst.x=slot_dst.x+2;
	fillbar_dst.y=button_dst.y+(button_dst.h/2);
	fillbar_dst.h=(slot_dst.y+slot_dst.h)-(button_dst.y+button_dst.h/2);
	//END 	FILLBAR
	
	//BEGIN SHADOW TOP
	temp_surface = IMG_Load("./assets/gfx/shadow_top.png");
	shadow_top = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(shadow_top, NULL, NULL, &shadow_top_dst.w, &shadow_top_dst.h);
	shadow_top_dst.x=slot_dst.x;
	shadow_top_dst.y=button_dst.y+button_dst.h;
	//END 	SHADOW TOP
	
	//BEGIN SHADOW BOT
	temp_surface = IMG_Load("./assets/gfx/shadow_bot.png");
	shadow_bot = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(shadow_bot, NULL, NULL, &shadow_bot_dst.w, &shadow_bot_dst.h);
	shadow_bot_dst.x=slot_dst.x;
	shadow_bot_dst.y=(slot_dst.y+slot_dst.h)-shadow_bot_dst.h;
	//END 	SHADOW BOT
	
	//BEGIN BOUNDS
	button_bounds_dst.w=button_dst.w;
	button_bounds_dst.h=(button_dst.h*5)+10;
	button_bounds_dst.x=button_dst.x;
	button_bounds_dst.y=(button_dst.y-(2*button_dst.h))-4;
	//END 	BOUNDS

	//BEGIN TEXT
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 36);
	get_value();
	render_value();
	//END 	TEXT
}

void assets_out(void)
{
	SDL_DestroyTexture(slot);
	SDL_DestroyTexture(fillbar);
	SDL_DestroyTexture(shadow_top);
	SDL_DestroyTexture(shadow_bot);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(button);
	SDL_DestroyTexture(text);
}

void render_value(void)
{
	sprintf_s(string, 4, "%d", value);
	temp_surface=TTF_RenderText_Blended(font, string , color);
	text=SDL_CreateTextureFromSurface(Renderer,temp_surface);
	SDL_QueryTexture(text, NULL, NULL, &text_dst.w, &text_dst.h);
	text_dst.x=(ww/2)-(text_dst.w/2);
	text_dst.y=(wh/2)-(text_dst.h/2);
}

void get_value(void)
{
	int min=button_bounds_dst.y+button_dst.h/2;
	int max=(button_bounds_dst.y+button_bounds_dst.h)-(button_dst.h/2);
	int b=max-(button_dst.y+button_dst.h/2);
	float step=((float)max-(float)min)/100;
	value=roundf(b/step);
}
