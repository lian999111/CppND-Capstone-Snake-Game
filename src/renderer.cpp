#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height), sdl_font("../font/OpenSans-Regular.ttf", 200) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Color white = {255, 255, 255};
  SDL_Surface *surface_msg = TTF_RenderText_Solid(sdl_font.Get(), "Pause", white);
  pause_msg = SDL_CreateTextureFromSurface(sdl_renderer, surface_msg);

  // We get the message now -> free surface
  SDL_FreeSurface(surface_msg);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_Quit();

  SDL_DestroyTexture(pause_msg);
}

void Renderer::Render(
    const std::array<std::unique_ptr<Snake>, 2> &snakes,
    const std::array<std::unique_ptr<SDL_Point>, 2> &food_nibs) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food1
  SDL_SetRenderDrawColor(sdl_renderer, 0x99, 0xCC, 0xFF, 0xFF);
  block.x = food_nibs[0]->x * block.w;
  block.y = food_nibs[0]->y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render food2
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xB2, 0x66, 0xFF);
  block.x = food_nibs[1]->x * block.w;
  block.y = food_nibs[1]->y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake1's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snakes[0]->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake2's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snakes[1]->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render heads after bodies so the dead head's red is not overriden by body
  // Render snake1's head
  block.x = static_cast<int>(snakes[0]->head_x) * block.w;
  block.y = static_cast<int>(snakes[0]->head_y) * block.h;
  if (snakes[0]->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x66, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake2's head
  block.x = static_cast<int>(snakes[1]->head_x) * block.w;
  block.y = static_cast<int>(snakes[1]->head_y) * block.h;
  if (snakes[1]->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x80, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(const std::array<int, 2> scores,
                                 const int fps) {
  std::string title{"P1 Score: " + std::to_string(scores[0]) + "  P2 Score: " +
                    std::to_string(scores[1]) + "  FPS: " +
                    std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderPause() {
    SDL_Rect msg_rect; // create a rect
    msg_rect.x = 220;  // controls the rect's x coordinate
    msg_rect.y = 270;  // controls the rect's y coordinte
    msg_rect.w = 200;  // controls the width of the rect
    msg_rect.h = 100;  // controls the height of the rect

    SDL_RenderCopy(sdl_renderer, pause_msg, NULL, &msg_rect);
    SDL_RenderPresent(sdl_renderer);
}

