#include <engine.hpp>

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

int main() {

  try {
    std::unique_ptr<MyEngine::Engine> engine =
        std::make_unique<MyEngine::Engine>();

    // main loop
    while (engine->handle_input()) {

      std::ifstream file("vertexes.txt");
      assert(file);

      MyEngine::triangle tr;
      file >> tr;

      engine->draw_triangle(tr);

      file >> tr;
      engine->draw_triangle(tr);

      engine->swap_buffers();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what();
  }

  return std::cerr.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
