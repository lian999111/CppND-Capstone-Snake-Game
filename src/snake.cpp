#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.

  // Lock when updating the snake
  std::lock_guard<std::mutex> lck(mtx_);
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::CheckAlive(Snake &other_snake) {
  // Require 2 snakes to be locked, use std::lock to avoid deadlock
  std::lock(mtx_, other_snake.mtx_);

  std::lock_guard<std::mutex> lck_self(mtx_, std::adopt_lock);
  std::lock_guard<std::mutex> lck_other(other_snake.mtx_, std::adopt_lock);

  auto current_head_cell_x = static_cast<int>(head_x);
  auto current_head_cell_y = static_cast<int>(head_y);

  // Check if the snake collides itself.
  for (auto const &item : body) {
    if (current_head_cell_x == item.x && current_head_cell_y == item.y) {
      alive = false;
      return;
    }
  }

  // Check if the snake collides the other
  if (other_snake.CheckSnakeCell(current_head_cell_x, current_head_cell_y)) {
    alive = false;
  }
}

void Snake::GrowBody() { 
  std::lock_guard<std::mutex> lock(mtx_);
  growing = true; 
}

bool Snake::SnakeCell(int x, int y) const {
  std::lock_guard<std::mutex> lock(mtx_);
  // Calls the private CheckSnakeCell() that doesn't lock
  return CheckSnakeCell(x, y);
}

void Snake::UpdateHead() {
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // The original checking of alive state is moved out of this function
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::CheckSnakeCell(int x, int y) const {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
