/*
 *  gcc main.c text.c window.c util.c -o main `sdl2-config --cflags --libs` -lSDL2_ttf -Iinclude
 */

#include "main.h"

#define WIN_W 800
#define WIN_H 400
#define FONT_PATH "/usr/share/fonts/TTF/DroidSans.ttf"
#define FONT_SIZE 94
#define PRED_SIZE 40
#define COLOR_B (SDL_Color) { 0, 0, 0, 255 }
#define COLOR_W (SDL_Color) { 255, 255, 255, 255 }

int predict_color(NeuralNetwork *nn, SDL_Color color) {
    float ax[] = { color.r / 255.0, color.g / 255.0, color.b / 255.0 };
    Matrix *prediction = nn_predict(nn, ax);
    printf("prediction = B: %1.4f, W: %1.4f\n",
            prediction->data[0], prediction->data[1]);
    return (prediction->data[0] < prediction->data[1]) ? 1 : 0;
}

int main(void) {
    // init
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    rng_init();

    // window
    Window *window = create_window("Color Predictor", WIN_W, WIN_H);
    NeuralNetwork *nn = create_nn(3, 9, 2);
    nn->lr = 0.4;

    // text
    TTF_Font *font = open_font(FONT_PATH, FONT_SIZE);
    if(!font) {
        printf("Could not open font: %s\n", FONT_PATH);
        return 1;
    }
    Text *black = create_text(window->rend, "black", font, COLOR_B);
    Text *white = create_text(window->rend, "white", font, COLOR_W);
    close_font(font);
    int black_x = WIN_W / 4 - black->rect->w / 2;
    int white_x = WIN_W / 2 + black_x;
    int text_y = WIN_H / 3 - FONT_SIZE / 2;
    set_text_position(black, black_x, text_y);
    set_text_position(white, white_x, text_y);

    // seperator
    SDL_Rect sep = { WIN_W / 2 - 1, 0, 2, WIN_H };

    // initial background color
    SDL_Color color_bg = random_color();

    // prediction indicator
    int p = predict_color(nn, color_bg);
    int pred_black_x = WIN_W / 4 - PRED_SIZE / 2;
    SDL_Rect pred = { p * WIN_W / 2 + pred_black_x,
                      WIN_H - WIN_H / 3 - PRED_SIZE / 2,
                      PRED_SIZE, PRED_SIZE };
    SDL_Color color_pred = (p) ? COLOR_W : COLOR_B;

    // loop
    while (1) {
        int r = handle_events();
        // quit
        if (r == -1) break;
        if (r == -2) {
            // generate new bg color
            color_bg = random_color();
            // predict foreground color
            int p = predict_color(nn, color_bg);
            // set prediction indicator
            color_pred = (p) ? COLOR_W : COLOR_B;
            pred.x = p * WIN_W / 2 + pred_black_x;
        } else if (r != -3) {
            // color chosen
            int x = (r > WIN_W / 2);
            printf("chosen: %s\n", x ? "white" : "black");
            float ay[] = { !x, x };
            // train with backprop
            nn_train(nn, ay);
            // generate new bg color
            color_bg = random_color();
            // predict foreground color
            int p = predict_color(nn, color_bg);
            // set prediction indicator
            color_pred = (p) ? COLOR_W : COLOR_B;
            pred.x = p * WIN_W / 2 + pred_black_x;
        }

        // draw the window components
        draw_background(window->rend, color_bg);
        draw_rect(window->rend, &sep, (SDL_Color) { 0x7f, 0x7f, 0x7f, 0xff });
        render_text(window->rend, black);
        render_text(window->rend, white);
        draw_rect(window->rend, &pred, color_pred);
        SDL_RenderPresent(window->rend);

        // wait 1/30th of a second
        SDL_Delay(1000/30);
    }

    destroy_text(black);
    destroy_text(white);
    destroy_nn(nn);
    destroy_window(window);
    SDL_Quit();

    return 0;
}
