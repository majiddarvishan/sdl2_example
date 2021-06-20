#ifndef _HELPER_H_
#define _HELPER_H_

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL2/SDL_ttf.h>

SDL_Window* createWindow();
SDL_Renderer* createRenderer(SDL_Window* w);

void destroy(SDL_Window* Window, SDL_Renderer* Renderer);

#endif
