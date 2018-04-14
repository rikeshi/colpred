#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct Text {
    SDL_Texture *tex;
    SDL_Rect *rect;
} Text;

Text *create_text(SDL_Renderer *rend, char *str, TTF_Font *font, SDL_Color color);
int destroy_text(Text *text);
int set_text_position(Text *text, int x, int y);
int render_text(SDL_Renderer *rend, Text *text);
TTF_Font *open_font(char *font_path, int font_size);
void close_font(TTF_Font *font);
