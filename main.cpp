#include "button.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>


class Drink {
public:
  int price;
  int count;
  int id;
  
};


class Device {
private:
  Drink stock[4];
  
public:
  void loadStock();
  void recharge();
  void updateStock();
  void showSotck();
  void transaction();
  void updateTransaction();

};

void Device::loadStock(){
std::ifstream inputFile("stockfile.dat");

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

}

void lemonade() {
 std::cout << "clicked"; 
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cock-shed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Device vendingMachine;
    vendingMachine.loadStock();
    Drink cocacola;
    cocacola.price = 10;
    cocacola.count = 0;
    cocacola.id = 1;

    Drink alis;
    cocacola.price = 5;
    cocacola.count = 0;
    cocacola.id = 2;

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
