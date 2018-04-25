#include "window.h"

Window *create_window(char *title, int width, int height) {
    Window *window = malloc(sizeof(Window));
    window->win = SDL_CreateWindow(title, 0, 0, width, height, 0);
    window->rend = SDL_CreateRenderer(window->win, -1, SDL_RENDERER_ACCELERATED);
    return window;
}

int destroy_window(Window *window) {
    if (!window) return 1;
    SDL_DestroyRenderer(window->rend);
    SDL_DestroyWindow(window->win);
    free(window);
    return 0;
}

void draw_background(SDL_Renderer *rend, SDL_Color color) {
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderClear(rend);
}

void draw_rect(SDL_Renderer *rend, SDL_Rect *rect, SDL_Color color) {
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, rect);
}

int handle_events(void) {
    SDL_Event event;
    int mouse_x = -3;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return -1;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, NULL);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE) {
                    mouse_x = -2;
                }
                break;
        }
    }
    return mouse_x;
}

