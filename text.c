#include "text.h"

Text *create_text(SDL_Renderer *rend, char *msg, TTF_Font *font, SDL_Color color) {
    Text *text = malloc(sizeof(Text));
    SDL_Surface* surf = TTF_RenderText_Solid(font, msg, color);
    text->tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    text->rect = malloc(sizeof(SDL_Rect));
    SDL_QueryTexture(text->tex, NULL, NULL, &text->rect->w, &text->rect->h);
    return text;
}

int destroy_text(Text *text) {
    if (!text) return 1;
    SDL_DestroyTexture(text->tex);
    free(text->rect);
    free(text);
    return 0;
}

int set_text_position(Text *text, int x, int y) {
    if (!text) return 1;
    text->rect->x = x;
    text->rect->y = y;
    return 0;
}

int render_text(SDL_Renderer *rend, Text *text) {
    return SDL_RenderCopy(rend, text->tex, NULL, text->rect);
}

TTF_Font *open_font(char *font_path, int font_size) {
    return TTF_OpenFont(font_path, font_size);
}

void close_font(TTF_Font *font) {
    TTF_CloseFont(font);
    font = NULL;
}
