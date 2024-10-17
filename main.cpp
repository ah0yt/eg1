#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

// declare globals
SDL_Renderer* renderer;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

// pixel struct
typedef struct {
    int x;
    int y;
} Pixel;


// Bresenham's algorithm
void drawLine(Pixel start, Pixel end) {
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int error = dx - dy;

    while (true) {
        SDL_RenderDrawPoint(renderer, start.x,start.y);

        if (start.x == end.x && start.y == end.y) {
            break;
        }

        int e2 = 2 * error;
        if (e2 > -dy) {
            error -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            error += dx;
            start.y += sy;
        }
    }
}


int main() {

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize sdl2: " << SDL_GetError() << "\n";
        return 1;
    }

    // create a window
    window = SDL_CreateWindow(
        "Hello World SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        std::cerr << "Could not create window: " << SDL_GetError() << "\n";
        return 1;
    }


    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Could not create render: " <<  SDL_GetError() << "\n";
        return 1;
    }

    // set background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // clear the screen using black color
    SDL_RenderClear(renderer);

    // main render loop
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // declare some points, draw a line
        Pixel start = {0, 0};
        Pixel end = {100, 170};
        drawLine(start, end);

        SDL_RenderSetScale(renderer, 4, 4);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
