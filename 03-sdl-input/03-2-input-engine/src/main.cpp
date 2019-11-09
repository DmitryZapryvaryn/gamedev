#include <engine.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

int main() {

  try {
    std::unique_ptr<MyEngine::Engine> engine =
        std::make_unique<MyEngine::Engine>();

    // main loop
    while (engine->handle_input()) {
    }
  } catch (const std::exception &e) {
    std::cerr << e.what();
  }

  return std::cerr.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
