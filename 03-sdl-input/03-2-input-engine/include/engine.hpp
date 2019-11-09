#pragma once

// TODO: exclude SDL dependencie
#include <SDL2/SDL.h>

namespace MyEngine {

/*enum class Event {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    QUIT
};*/

class Engine {
public:
  Engine();
  bool handle_input();
  ~Engine();

private:
  SDL_Window *window;
  void handle_keys(const SDL_Event &event);
};

} // namespace MyEngine
