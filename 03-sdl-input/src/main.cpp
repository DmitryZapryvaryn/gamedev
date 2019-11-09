#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include <memory>

void handle_input(const SDL_Event &event) {
  switch (event.key.keysym.sym) {
  case SDLK_UP:
    std::cout << "Up\n";
    break;
  case SDLK_DOWN:
    std::cout << "Down\n";
    break;
  case SDLK_LEFT:
    std::cout << "Left\n";
    break;
  case SDLK_RIGHT:
    std::cout << "Right\n";
    break;
  }
}

int main() {

  // Init SDL_INIT_TIMER, SDL_INIT_AUDIO, SDL_INIT_VIDEO, SDL_INIT_EVENTS,
  // SDL_INIT_JOYSTICK, SDL_INIT_HAPTIC, SDL_INIT_GAMECONTROLLER,
  // SDL_INIT_SENSOR
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "Could not init sdl: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  // Init unique_ptr deleter
  std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> window =
      std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(
          SDL_CreateWindow("Game Title", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, 800, 600,
                           SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                               SDL_WINDOW_INPUT_FOCUS),
          SDL_DestroyWindow);

  if (window == nullptr) {
    std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  // main loop
  bool is_continue = true;

  while (is_continue) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        is_continue = false;
        break;
      case SDL_KEYDOWN:
        handle_input(event);
        break;
      default:
        break;
      }
    }
  }

  SDL_Quit();
  return EXIT_SUCCESS;
}
