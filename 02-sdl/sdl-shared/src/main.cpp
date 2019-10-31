#include <SDL_version.h>

#include <cstdlib>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const SDL_version &ver) {
  return out << static_cast<int>(ver.major) << '.'
             << static_cast<int>(ver.minor) << '.'
             << static_cast<int>(ver.patch);
}

int main() {
  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);

  std::cout << "Compiled: " << compiled << "\n";
  std::cout << "Linked: " << linked << "\n";

  return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
