#include "util.h"

void rng_init(void) {
    srand(time(NULL));
}

SDL_Color random_color(void) {
    int n = rand();
    return (SDL_Color) { n >> 16 & 0xff, n >> 8 & 0xff, n & 0xff, 0xff };
}
