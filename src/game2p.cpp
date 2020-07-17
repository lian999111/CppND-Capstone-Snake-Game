#include "game2p.h"
#include "SDL.h"
#include <exception>
#include <future>
#include <iostream>

Game2P::Game2P(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()), random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  // Initialize snakes
  snakes[0] = std::make_unique<Snake>(grid_width, grid_height, 0.66);
  snakes[1] = std::make_unique<Snake>(grid_width, grid_height, 0.33);
  // Initialize food_nibs with ptrs to a default SDL_Point
  food_nibs[0] = std::make_unique<SDL_Point>();
  food_nibs[1] = std::make_unique<SDL_Point>();
  // Place food nibs
  PlaceFood(0);
  PlaceFood(1);
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
    controller.HandleInput(running, snakes, is_paused);

    if (is_paused) {
      renderer.RenderPause();
    } else {
      // Create 2 tasks to update snakes and wait for them to finish
      auto ftr_move1 =
          std::async(std::launch::async, &Game2P::MoveSnake, this, 0);
      auto ftr_move2 =
          std::async(std::launch::async, &Game2P::MoveSnake, this, 1);
      ftr_move1.wait();
      ftr_move2.wait();

      auto ftr_update1 =
          std::async(std::launch::async, &Game2P::UpdateSnakeState, this, 0);
      auto ftr_update2 =
          std::async(std::launch::async, &Game2P::UpdateSnakeState, this, 1);
      ftr_update1.wait();
      ftr_update2.wait();

      renderer.Render(snakes, food_nibs);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(scores, frame_count);
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

void Game2P::MoveSnake(int idx) {

  if (!snakes[idx]->alive)
    return;

  int other_idx = 1 - idx;
  snakes[idx]->Update();
}

void Game2P::UpdateSnakeState(int idx) {
  int other_idx = 1 - idx;
  if (!snakes[idx]->CheckAlive(*snakes[other_idx])) {
    return;
  };

  int new_x = static_cast<int>(snakes[idx]->head_x);
  int new_y = static_cast<int>(snakes[idx]->head_y);

  // Check if there's food over here
  if (food_nibs[idx]->x == new_x && food_nibs[idx]->y == new_y) {
    scores[idx]++;
    PlaceFood(idx);
    // Grow snake and increase speed.
    snakes[idx]->GrowBody();
    snakes[idx]->speed += 0.02;
  }
}

void Game2P::PlaceFood(int idx) {
  int x, y;
  int other_idx = 1 - idx;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is neither occupied by both snakes item nor by
    // the other food before placing food.
    if (!snakes[0]->SnakeCell(x, y) && !snakes[1]->SnakeCell(x, y) &&
        (x != food_nibs.at(other_idx)->x || y != food_nibs.at(other_idx)->y)) {
      food_nibs[idx]->x = x;
      food_nibs[idx]->y = y;
      return;
    }
  }
}

int Game2P::GetScore(int idx) const { return scores[idx]; }
int Game2P::GetSize(int idx) const { return snakes[idx]->size; }