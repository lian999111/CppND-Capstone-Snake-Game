#ifndef GAME2P_H
#define GAME2P_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game2P {
 public:
  Game2P(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake1;
  Snake snake2;
  SDL_Point food1;
  SDL_Point food2;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score1{0};
  int score2{0};

  void UpdateSnake1();
  void UpdateSnake2();
  void PlaceFood1();
  void PlaceFood2();
};

#endif