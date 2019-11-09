#include <engine.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace MyEngine {

Engine::Engine() : window(nullptr) {
  // Init SDL_INIT_TIMER, SDL_INIT_AUDIO, SDL_INIT_VIDEO, SDL_INIT_EVENTS,
  // SDL_INIT_JOYSTICK, SDL_INIT_HAPTIC, SDL_INIT_GAMECONTROLLER,
  // SDL_INIT_SENSOR
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::stringstream serr;
    serr << "Could not init sdl: " << SDL_GetError();
    throw std::runtime_error(serr.str());
  }

  window = SDL_CreateWindow(
      "Game Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS);

  if (window == nullptr) {
    std::stringstream serr;
    serr << "Could not create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    throw std::runtime_error(serr.str());
  }
}

bool Engine::handle_input() {

  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {

    switch (sdl_event.type) {
    case SDL_QUIT:
      return false;
      break;
    case SDL_KEYDOWN:
      std::cout << "Pressed ";
      handle_keys(sdl_event);
      break;
    case SDL_KEYUP:
      std::cout << "Released ";
      handle_keys(sdl_event);
      break;
    default:
      break;
    }
  }

  return true;
}

Engine::~Engine() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Engine::handle_keys(const SDL_Event &event) {
  switch (event.key.keysym.sym) {
  case SDLK_UP:
    std::cout << "Up" << std::endl;
    break;
  case SDLK_DOWN:
    std::cout << "Down" << std::endl;
    break;
  case SDLK_LEFT:
    std::cout << "Left" << std::endl;
    break;
  case SDLK_RIGHT:
    std::cout << "Right" << std::endl;
    break;
  }
}

} // namespace MyEngine
