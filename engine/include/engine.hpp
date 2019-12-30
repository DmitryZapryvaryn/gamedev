#pragma once

#include <SDL2/SDL.h>
#include <istream>

namespace MyEngine {

struct vertex {
  vertex() : x(0.f), y(0.f) {}

  float x, y;
};

std::istream &operator>>(std::istream &in, vertex &v);

struct triangle {
  triangle() : v({vertex(), vertex(), vertex()}) {}

  vertex v[3];
};

std::istream &operator>>(std::istream &in, triangle &tr);

class Engine {
public:
  explicit Engine();
  ~Engine();

  float get_time_from_init();

  bool handle_input();
  void draw_triangle(const triangle &t);
  void swap_buffers();

private:
  SDL_Window *window;
  SDL_GLContext gl_context;
  int program_id;
  void handle_keys(const SDL_Event &event);
};

} // namespace MyEngine
