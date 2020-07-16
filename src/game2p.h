#ifndef GAME2P_H
#define GAME2P_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <array>
#include <memory>
#include <random>

class Game2P {
public:
  Game2P(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore(int idx) const;
  int GetSize(int idx) const;

private:
  // Fixed to 2 snakes and 2 food nibs
  std::array<std::unique_ptr<Snake>, 2> snakes;
  std::array<std::unique_ptr<SDL_Point>, 2> food_nibs{};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::array<int, 2> scores{{0}};

  void MoveSnake(int idx);
  void UpdateSnakeState(int idx);
  void PlaceFood(int idx);
};

#endif