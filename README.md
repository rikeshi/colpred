# colpred

Interactive neural network color predictor

## Usage

Click with the `mouse` on the side that has the clearest text over the background color.
This feeds your decision as a training example to the neural network.

Press `spacebar` to get the next prediction without training the network.

Training the network to properly predict the best foreground color takes quite some clicks, so it's not really worth it for such a simple task. :D

## Dependencies

- [SDL 2.0](https://www.libsdl.org/index.php) for drawing the window (`SDL.h`) and text (`SDL_ttf.h`)
