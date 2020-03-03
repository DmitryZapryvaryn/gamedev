#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <string>

namespace MyRender {

struct position {
  int x;
  int y;

  position() : x(0), y(0) {}
  position(int _x, int _y) : x(_x), y(_y) {}

  position operator+(const position &other) const {
    return position(x + other.x, y + other.y);
  }

  position operator-(const position &other) const {
    return position(x - other.x, y - other.y);
  }
};

struct color {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

template <size_t w, size_t h> struct Image {

  using pixels = std::array<color, w * h>;

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

  void set_background(const color &c) {
    std::fill(data.begin(), data.end(), c);
  }

  void set_pixel(const position& position, const color& c) {
    size_t i = static_cast<unsigned>(position.y) * w +
               static_cast<unsigned>(position.x);
      auto &pixel = data.at(i);
      pixel = c;
  }

  void draw(const std::vector<position> &positions,
          const color &c = {255u, 0u, 0u}) {
    for (const auto &pos : positions) {
      set_pixel(pos, c);
    }
  }

  // fields
  pixels data;
};

} // namespace MyRender
