#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <mutex>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // head_w_pos is the horizontal position of head propotional to grid_width
  Snake(int grid_width, int grid_height, float head_w_pos)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width * head_w_pos),
        head_y(grid_height / 2) {}

  void Update();
  void CheckAlive(Snake &other_snake);  // checks if the snake collides itself or other snake

  void GrowBody();
  bool SnakeCell(int x, int y) const;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  bool CheckSnakeCell(int x, int y) const;

  bool growing{false};
  int grid_width;
  int grid_height;

  // Snakes will be manipulated from different threads
  // To make Snake thread-safe
  // mutable because mtx_ can be locked in a const function that does read-only stuff
  mutable std::mutex mtx_;
};

#endif