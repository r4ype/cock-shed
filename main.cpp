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
  int stockCount;

public:
  Device(int count) : stockCount(count){
    stockCount = count;
    stock = new Drink[stockCount];
  }
  ~Device() {
    delete[] stock;
  }
  void loadStock();
  void updateStock(std::string,int);
  void showSotck();
  int transaction(std::string,Drink *,int);
  void savestock();
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

void Device::updateStock(std::string name,int count){
  for(int i = 0 ;i < stockCount;i++){
    if (stock[i].id == name){
      stock[i].count += count;
      return;
    }
  }
  std::cout << name << " not found !!" << std::endl;
}

void Device::showSotck(){
  for(int i = 0;i < stockCount;i++){
    std::cout << stock[i].id << " : price " << stock[i].price << " count " << stock[i].count << std::endl;
  }
}

int Device::transaction(std::string name,Drink *ShopingCart,int count){
  for (int i = 0; i < count; i++){
    for(int j = 0;j < stockCount;j++){
      if(stock[j].id == ShopingCart[i].id){
        if(stock[j].count < ShopingCart[i].count){
          std::cout << "can purches out of stock !!" << std::endl;
          return 0;
        }
      }
    }
  }
  int sum = 0;
  std::fstream file;
  file.open("transaction.dat", std::ios::app);
  if (!file){
    std::cout << "cant insert to  transaction file" << std::endl;
  }
  else{
    for (int i = 0;i < count;i++){
      for(int j = 0;j < stockCount;j++){
        if(stock[j].id == ShopingCart[i].id){
            stock[j].count -= ShopingCart[i].count ;
            sum += ShopingCart[i].count * ShopingCart[i].price;
            file << name +  "  " + ShopingCart[i].id + " " + std::to_string(ShopingCart[i].count) + '\n';
        }
      }
    }
  }
  file.close();
  return sum;

}
void Device::savestock(){
  std::ofstream outFile("example.txt");
  if (!outFile.is_open()){
    std::cerr << "Error opening file !" << std::endl;
    return;
  }
  else{
    for (int i = 0;i < stockCount;i++){
      outFile << stock[i].id + "-" + std::to_string(stock[i].price) + "-" + std::to_string(stock[i].count) + "-" << std::endl;
    }
    outFile.close();
  }

}

void lemonade() {
  std::cout << "clicked" << std::endl;
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cock-shed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
    Drink ls[1];
    ls[0].id = "coca";
    ls[0].count = 3;
    Device vendingMachine(3);
    vendingMachine.loadStock();
    vendingMachine.updateStock("coca", 3);
    vendingMachine.updateStock("gogol", -4);
    vendingMachine.transaction("ehsan",ls,1);
    vendingMachine.showSotck();
    

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
            if(event.type == SDL_QUIT ||  event.key.keysym.sym == SDLK_q) running = false;
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
