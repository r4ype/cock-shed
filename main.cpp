#include "button.hpp"
#include "texture_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL_ttf.h>

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
    void renderDrinks(SDL_Renderer* renderer);
};

void Device::renderDrinks(SDL_Renderer* renderer){
  if (stock[0].count != 0){
    SDL_Rect rect0 = {100,100 , 50,100};
    SDL_Texture* textureall = TextureManager::loadTexture("./assets/" + stock[0].id + ".png", renderer);
    SDL_RenderCopy(renderer,textureall,NULL, &rect0);
  }

  if (stock[1].count != 0){
    SDL_Rect rect0 = {200,100 , 50,100};
    SDL_Texture* textureall = TextureManager::loadTexture("./assets/" + stock[1].id + ".png", renderer);
    SDL_RenderCopy(renderer,textureall,NULL, &rect0);
  }
  if (stock[2].count != 0){
    SDL_Rect rect0 = {300,100 , 50,100};
    SDL_Texture* textureall = TextureManager::loadTexture("./assets/" + stock[2].id + ".png", renderer);
    SDL_RenderCopy(renderer,textureall,NULL, &rect0);
  }
  if (stock[3].count != 0){
    SDL_Rect rect0 = {400,100 , 50,100};
    SDL_Texture* textureall = TextureManager::loadTexture("./assets/" + stock[3].id + ".png", renderer);
    SDL_RenderCopy(renderer,textureall,NULL, &rect0);
  } 
  //inja moshek kod kasif darim : we porerly shoud use a for loop but idk how
}

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
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  SDL_Window* window = SDL_CreateWindow("cock-shed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1042, 653, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  char GameState = 'G' ;
  Drink ls[1];
  ls[0].id = "coca";
  ls[0].count = 4;
  Device vendingMachine(4);
  vendingMachine.loadStock();
  vendingMachine.showSotck();

  SDL_Color red = {255, 0, 0, 255};
  Button lemonadeB(100, 100, 200, 50, red);
  lemonadeB.onClick(lemonade);

  bool running = true;
  SDL_Event event;

  TTF_Font* font = TTF_OpenFont("./assets/ARCADECLASSIC.TTF", 24);
  if (!font) {
    std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }
  SDL_Color textColor = {255, 255, 255, 255}; // White color
  SDL_Surface* cocaSurface = TTF_RenderText_Solid(font, "COCO COLA", textColor);
  SDL_Texture* cocaTexture = SDL_CreateTextureFromSurface(renderer, cocaSurface);
  SDL_FreeSurface(cocaSurface);

  SDL_Surface* fantaSurface = TTF_RenderText_Solid(font, "FANTA", textColor);
  SDL_Texture* fantaTexture = SDL_CreateTextureFromSurface(renderer, fantaSurface);
  SDL_FreeSurface(fantaSurface);

  SDL_Surface* spriteSurface = TTF_RenderText_Solid(font, "SPRITE", textColor);
  SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
  SDL_FreeSurface(spriteSurface);

  SDL_Surface* pepsiSurface = TTF_RenderText_Solid(font, "PEPSI", textColor);
  SDL_Texture* pepsiTexture = SDL_CreateTextureFromSurface(renderer, pepsiSurface);
  SDL_FreeSurface(pepsiSurface);

  vendingMachine.renderDrinks(renderer);


  SDL_Texture* texture = TextureManager::loadTexture("./assets/bg.jpg", renderer);
  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT ||  event.key.keysym.sym == SDLK_q) running = false;
      lemonadeB.handleEvent(&event);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    if (GameState == 'G'){




      SDL_RenderCopy(renderer, texture, NULL, NULL);
      lemonadeB.render(renderer);
      vendingMachine.renderDrinks(renderer);

    }
    if (GameState == 'M'){
      SDL_Rect cocaRect = {100, 100, 100, 50}; // Position and size of the text
      SDL_RenderCopy(renderer, cocaTexture, nullptr, &cocaRect);

      SDL_Rect pepsiRect = {100, 200, 100, 50}; // Position and size of the text
      SDL_RenderCopy(renderer, pepsiTexture, nullptr, &pepsiRect);

      SDL_Rect fantaRect = {100, 300, 100, 50}; // Position and size of the text
      SDL_RenderCopy(renderer, fantaTexture, nullptr, &fantaRect);

      SDL_Rect spriteRect = {100, 400, 100, 50}; // Position and size of the text
      SDL_RenderCopy(renderer, spriteTexture, nullptr, &spriteRect);
    }
    SDL_RenderPresent(renderer);

  }
  SDL_DestroyTexture(cocaTexture);
  SDL_DestroyTexture(pepsiTexture);
  SDL_DestroyTexture(fantaTexture);
  SDL_DestroyTexture(spriteTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  SDL_Quit();
  return 0;
}
