#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"
#include "sdlfont.h"
#include <array>
#include <memory>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(const std::array<std::unique_ptr<Snake>, 2> &snakes,
              const std::array<std::unique_ptr<SDL_Point>, 2> &food_nibs);
  void UpdateWindowTitle(const std::array<int, 2> scores, const int fps);
  void RenderPause();

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  SDLFont sdl_font;
  SDL_Surface *surface_msg;
  SDL_Texture *pause_msg;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif