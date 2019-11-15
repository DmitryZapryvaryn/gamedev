#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <string>

namespace MyRender {

struct Color {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

template <size_t w, size_t h> struct Image {

  using pixels = std::array<Color, w * h>;

  void save(const std::string &path) {
    std::ofstream file_out;
    file_out.open(path, std::ios_base::binary);
    file_out << "P6\n" << w << ' ' << h << "\n" << 255 << "\n";

    for (const auto &c : data) {
      file_out << c.r << c.g << c.b;
    }
  }

  pixels load(const std::string &path);

  size_t width() { return w; }
  size_t height() { return h; }

  // fields
  pixels data;
};

} // namespace MyRender
