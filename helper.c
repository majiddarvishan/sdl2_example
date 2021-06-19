#include "helper.h"

//SDL_Window   	*Window	  = NULL;
//SDL_Renderer 	*Renderer = NULL;

SDL_Window* createWindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
    TTF_Init();
    //BEGIN ICON
    SDL_Surface* icon;
    icon = IMG_Load("./assets/gfx/icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
    //END 	ICON

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* w)
{
    SDL_Renderer* Renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    return Renderer;
}

//void init(SDL_Window* Window, SDL_Renderer* Renderer)
//{
//SDL_Init(SDL_INIT_EVERYTHING);
//Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
//TTF_Init();
////BEGIN ICON
//SDL_Surface *icon;
//icon=IMG_Load("./assets/gfx/icon.png");
//SDL_SetWindowIcon(Window, icon);
//SDL_FreeSurface(icon);
////END 	ICON
//
//Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
//
//}

void exit_(SDL_Window* Window, SDL_Renderer* Renderer)
{
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
