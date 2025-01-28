#include <SDL2/SDL.h>
#include <functional>

class Button {
private:
  SDL_Rect rect;
  SDL_Color color;
  std::function<void()> onClickHandler;

public:
  Button(int x, int y, int w, int h, SDL_Color bgColor);
  void onClick(std::function<void()> callback);
  void handleEvent(SDL_Event* e);
  void render(SDL_Renderer* renderer);
};
