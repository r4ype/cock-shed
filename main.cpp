#include "button.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>


class Drink {
public:
  int price;
  int count;
  std::string id;
  
};


class Device {
private:
  Drink* stock;
  int stockCount = 4;
  
public:
  Device(int count) : stockCount(count){
    stock = new Drink[stockCount];
  }
  ~Device() {
    delete[] stock;
  }
  void loadStock();
  void recharge(std::string,int);
  void updateStock();
  void showSotck();
  void transaction();
  void updateTransaction();

};

void Device::loadStock(){
std::ifstream inputFile("stockfile.dat");

    if (inputFile.is_open()) {
        std::string line;
        int j = 0;
        //should add if < stockCount
        while (std::getline(inputFile, line) && j < stockCount) {
          bool flag = true;
          std::string temp = "";
          int i = 0;
          for (char x : line){
              if ( x != '-'){
                temp += x;
              }
              else{
                if (i == 0)
                  stock[j].id = temp;
                else if (i == 1)
                  stock[j].price = std::stoi(temp);
                else if (i == 2)
                  stock[j].count = std::stoi(temp);
                temp = "";
                i++;
              
              }
          }
          j++;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

}
void Device::recharge(std::string name,int count){
  for(int i = 0 ;i < stockCount;i++){
    std::cout << stock[i].id << std::endl; 
    if (stock[i].id == name){
      stock[i].count += count;
      std::cout << stock[i].id << " " << stock[i].count << std::endl ;
      return;
    }
  }
  std::cout << name << " not found !!" << std::endl;
}
void lemonade() {
  std::cout << "clicked" << std::endl; 
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cock-shed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Device vendingMachine(4);
    vendingMachine.loadStock();
    vendingMachine.recharge("coca",3);


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
