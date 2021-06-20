#pragma once

#include "helper.h"

class playerControl
{
public:
    playerControl() = default;
    virtual ~playerControl() = default;

    void init();
    void start();
    void stop();

private:
    void assets_in();
    void assets_out();
    void render_value();
    void get_value();

private:
    SDL_Texture* bg = NULL;
    SDL_Rect 	bg_dst;

    SDL_Texture* slot = NULL;
    SDL_Rect 	slot_dst;

    SDL_Texture* fillbar = NULL;
    SDL_Rect 	fillbar_dst;

    SDL_Texture* button = NULL;
    SDL_Rect 	button_dst;

    SDL_Texture* shadow_top = NULL;
    SDL_Rect 	shadow_top_dst;

    SDL_Texture* shadow_bot = NULL;
    SDL_Rect 	shadow_bot_dst;

    SDL_Rect 	button_bounds_dst;

    TTF_Font* font = NULL;
    SDL_Color color = { 255,0,0,255 };
    SDL_Texture* text = NULL;
    SDL_Rect 	text_dst;

    int value;
    

    SDL_Point	mouse;
    SDL_bool 	mouse_follow = SDL_FALSE;
    SDL_Point 	mouse_offset;

    SDL_Window* Window = NULL;
    SDL_Renderer* Renderer = NULL;

    int windowWidth;
    int windowsHeight;
};

