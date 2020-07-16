#include "game2p.h"
#include "SDL.h"
#include <exception>
#include <iostream>
#include <future>

Game2P::Game2P(std::size_t grid_width, std::size_t grid_height)
    : snake1(grid_width, grid_height, 0.33),
      snake2(grid_width, grid_height, 0.66), engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood1();
  PlaceFood2();
}

void Game2P::Run(Controller const &controller, Renderer &renderer,
                 std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake1, snake2);

    // Create 2 tasks to update snakes and wait for them to finish
    auto ftr1 = std::async(std::launch::async, &Game2P::UpdateSnake1, this);
    auto ftr2 = std::async(std::launch::async, &Game2P::UpdateSnake2, this);
    ftr1.wait();
    ftr2.wait();

    renderer.Render(snake1, snake2, food1, food2);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score1, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game2P::UpdateSnake1() {
  
  if (!snake1.alive)
    return;

  snake1.Update();
  snake1.CheckAlive(snake2);

  int new_x = static_cast<int>(snake1.head_x);
  int new_y = static_cast<int>(snake1.head_y);

  // Check if there's food over here
  if (food1.x == new_x && food1.y == new_y) {
    score1++;
    PlaceFood1();
    // Grow snake and increase speed.
    snake1.GrowBody();
    snake1.speed += 0.02;
  }
}

void Game2P::UpdateSnake2() {
  
  if (!snake2.alive)
    return;

  snake2.Update();
  snake2.CheckAlive(snake1);

  int new_x = static_cast<int>(snake2.head_x);
  int new_y = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  if (food2.x == new_x && food2.y == new_y) {
    score2++;
    PlaceFood2();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
  }
}

void Game2P::PlaceFood1() {
  int x, y;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is neither occupied by both snakes item nor by
    // the other food before placing food.
    if (!snake1.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && (x != food2.x || y != food2.y)) {
      food1.x = x;
      food1.y = y;
      return;
    }
  }
}

void Game2P::PlaceFood2() {
  int x, y;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is neither occupied by both snakes item nor by
    // the other food before placing food.
    if (!snake1.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && (x != food1.x || y != food1.y)) {
      food2.x = x;
      food2.y = y;
      return;
    }
  }
}

int Game2P::GetScore() const { return score1; }
int Game2P::GetSize() const { return snake1.size; }