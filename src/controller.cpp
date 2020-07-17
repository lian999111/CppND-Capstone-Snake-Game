#include "controller.h"
#include "SDL.h"
#include "snake.h"
#include <iostream>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running,
                             std::array<std::unique_ptr<Snake>, 2> &snakes,
                             bool &is_paused) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN && !is_paused) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(*snakes[0], Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(*snakes[0], Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(*snakes[0], Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(*snakes[0], Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;

      case SDLK_w:
        ChangeDirection(*snakes[1], Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_s:
        ChangeDirection(*snakes[1], Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_a:
        ChangeDirection(*snakes[1], Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_d:
        ChangeDirection(*snakes[1], Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;

      case SDLK_SPACE:
        // Toggle is_paused to true
        is_paused = true;
        break;
      }
    } else if (e.type == SDL_KEYDOWN && is_paused) {
      // During pause, keys are ignored except SPACE
      if (e.key.keysym.sym == SDLK_SPACE) {
        // Toggle is_paused to false
        is_paused = false;
        return;
      }
    }
  }
}

