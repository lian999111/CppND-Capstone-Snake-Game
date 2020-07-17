#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <array>
#include <memory>

class Controller {
 public:
  void HandleInput(bool &running, std::array<std::unique_ptr<Snake>, 2> &snakes, bool &is_paused) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif