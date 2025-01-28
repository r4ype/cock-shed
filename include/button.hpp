#include <SDL2/SDL.h>
#include <functional>
#include <texture_manager.h>

class Button {
private:
  SDL_Rect rect;
  SDL_Color color;
  std::function<void()> onClickHandler;
  SDL_Texture *texture;

public:
  Button(int x, int y, int w, int h, SDL_Color bgColor, std::string image );
  void onClick(std::function<void()> callback);
  void handleEvent(SDL_Event* e);
  void render(SDL_Renderer* renderer);
};
