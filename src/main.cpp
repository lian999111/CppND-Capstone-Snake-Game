#include <iostream>
#include "controller.h"
#include "game2p.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game2P game2p(kGridWidth, kGridHeight);
  game2p.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "1P Score: " << game2p.GetScore(0) << "\n";
  std::cout << "1P Size: " << game2p.GetSize(0) << "\n";
  std::cout << "2P Score: " << game2p.GetScore(1) << "\n";
  std::cout << "2P Size: " << game2p.GetSize(1) << "\n";
  return 0;
}