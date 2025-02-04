#include "button.hpp"
#include "texture_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <ctime>

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
    std::string username;
    Drink ShopingCart[4];
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
    int transaction();
    void savestock();
    void renderDrinks(SDL_Renderer* renderer);
    void loadShopingCart();
    void updateShopingCart(std::string,int);
};

void Device::updateShopingCart(std::string drinkName,int k){
  for (int i = 0;i < 4;i++){
    if(ShopingCart[i].id == drinkName){
      ShopingCart[i].count += k;
    }
  }
}

void Device::loadShopingCart(){
  for (int i = 0;i < 4;i++){
    ShopingCart[i] = stock[i];
    ShopingCart[i].count = 0;
  }
}
void Device::renderDrinks(SDL_Renderer* renderer) {
  for (int i = 0; i < stockCount; i++) {
    if (stock[i].count >= 0) {
      SDL_Rect rect = {100 + i * 100, 100, 50, 100};
      SDL_Texture* texture = TextureManager::loadTexture("./assets/" + stock[i].id + ".png", renderer);
      SDL_RenderCopy(renderer, texture, NULL, &rect);
      SDL_DestroyTexture(texture); // Clean up the texture
    }
  }
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
    if (stock[i].id == name && stock[i].count + count >= 0 ){
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

int Device::transaction(){
  int sum = 0;
  std::fstream file;
  file.open("transaction.dat", std::ios::app);
  if (!file){
    std::cout << "cant insert to  transaction file" << std::endl;
  }
  else{
    std::time_t timestamp;
    std::time(&timestamp);
    for (int i = 0;i < 4;i++){
      std::cout << ShopingCart[i].id << " " << ShopingCart[i].count << std::endl;
      if(ShopingCart[i].count > 0){
        sum += ShopingCart[i].count * ShopingCart[i].price;
        file << username +  "  " + ShopingCart[i].id + " " + std::to_string(ShopingCart[i].count) + " " + std::ctime(&timestamp) +'\n';
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

Device vendingMachine(4);

void pepsi() {
  vendingMachine.updateStock("pepsi", -1);
  vendingMachine.updateShopingCart("pepsi", 1);

}

void sprite() {
  vendingMachine.updateStock("sprite", -1);
  vendingMachine.updateShopingCart("sprite", 1);

}


void coca() {
  vendingMachine.updateStock("coca", -1);
  vendingMachine.updateShopingCart("coca", 1);

}


void fanta() {
  vendingMachine.updateStock("fanta", -1);
  vendingMachine.updateShopingCart("fanta", 1);
}

void end() {
  vendingMachine.savestock();
  vendingMachine.transaction();
  std::cin >> vendingMachine.username;
  vendingMachine.loadShopingCart();
}

// recharg page functions


void pepsiM() {
  vendingMachine.updateStock("pepsi", 1);
  vendingMachine.showSotck();
}

void spriteM() {
  vendingMachine.updateStock("sprite", 1);
}


void cocaM() {
  vendingMachine.updateStock("coca", 1);
}


void fantaM() {
  vendingMachine.updateStock("fanta", 1);
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
  vendingMachine.loadStock();
  vendingMachine.showSotck();

  SDL_Color black = {0, 0, 0, 255};
  Button endB(500, 500, 100, 50, black);
  endB.onClick(end);


  SDL_Color blue = {0, 0, 255, 255};
  Button pepsiB(100, 500, 100, 50, blue);
  pepsiB.onClick(pepsi);


  SDL_Color green = {0, 255, 0, 255};
  Button spriteB(200, 500, 100, 50, green);
  spriteB.onClick(sprite);


  SDL_Color red = {255, 0, 0, 255};
  Button cocaB(300, 500, 100, 50, red);
  cocaB.onClick(coca);


  SDL_Color orange = {255, 165, 0, 255};
  Button fantaB(400, 500, 100, 50, orange);
  fantaB.onClick(fanta);


  // recharge page buttons
 
  Button cocaBM(300, 100, 50, 50, green);
  cocaBM.onClick(cocaM);

  Button spriteBM(300, 400, 50, 50, green);
  spriteBM.onClick(spriteM);


  Button fantaBM(300, 300, 50, 50, green);
  fantaBM.onClick(fantaM);


  Button pepsiBM(300, 200, 50, 50, green);
  pepsiBM.onClick(pepsiM);

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



  SDL_Texture* texture = TextureManager::loadTexture("./assets/bg.jpg", renderer);

  Uint32 frameStart, frameTime;
  std::cin >> vendingMachine.username;
  vendingMachine.loadShopingCart();
  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT ||  event.key.keysym.sym == SDLK_q) running = false;
      if(event.key.keysym.sym == SDLK_g) GameState = 'G';
      if(event.key.keysym.sym == SDLK_m) GameState = 'M';
      if(GameState == 'G'){

      cocaB.handleEvent(&event);
      fantaB.handleEvent(&event);
      spriteB.handleEvent(&event);
      pepsiB.handleEvent(&event);
      endB.handleEvent(&event);

      }

      if(GameState == 'M'){

      cocaBM.handleEvent(&event);
      fantaBM.handleEvent(&event);
      spriteBM.handleEvent(&event);
      pepsiBM.handleEvent(&event);


      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    if (GameState == 'G'){
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      cocaB.render(renderer);
      fantaB.render(renderer);
      spriteB.render(renderer);
      pepsiB.render(renderer);
      endB.render(renderer);
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

      cocaBM.render(renderer);
      fantaBM.render(renderer);
      spriteBM.render(renderer);
      pepsiBM.render(renderer);
 
    }
    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 32) SDL_Delay(32 - frameTime);  // Cap at ~60 FPS
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
