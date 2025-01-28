#include "button.hpp"

Button::Button(int x, int y, int w, int h, SDL_Color bgColor, SDL_Renderer* renderer, std::string image) {
    rect = {x, y, w, h};
    color = bgColor;
    texture = TextureManager::loadTexture(image, renderer);
}

void Button::onClick(std::function<void()> callback) {
    onClickHandler = callback;
}

void Button::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        if (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h) {
            if (onClickHandler) onClickHandler();
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
