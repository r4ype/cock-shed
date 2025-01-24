#include "button.hpp"
#include <SDL2/SDL.h>
#include <iostream>



class Drink {
public:
  int price;
  int stock;
  int id;
  
};


class Device {
public:
  int showSotck();
  int transaction();
}





void lemonade() {
    std::cout << " [1] sharbat limo kharide shod" << std::endl;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cock-shed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color red = {255, 0, 0, 255};
    Button lemonadeB(100, 100, 200, 50, red);
    lemonadeB.onClick(lemonade);

    bool running = true;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) running = false;
            lemonadeB.handleEvent(&event);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        lemonadeB.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
