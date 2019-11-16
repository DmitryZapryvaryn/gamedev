#pragma once

#include <algorithm>
#include <image.hpp>

#include <math.h>
#include <vector>

namespace MyRender {

struct Vec2 {
  int x;
  int y;

  Vec2() : x(0), y(0) {}
  Vec2(int _x, int _y) : x(_x), y(_y) {}

  Vec2 operator+(const Vec2 &other) const {
    return Vec2(x + other.x, y + other.y);
  }

  Vec2 operator-(const Vec2 &other) const {
    return Vec2(x - other.x, y - other.y);
  }
};

std::vector<Vec2> get_line_positions(const Vec2 &start, const Vec2 &end) {

  std::vector<Vec2> result;

  auto plot_line_high = [&](const Vec2 &begin_pos, const Vec2 &end_pos) {
    int dx = end_pos.x - begin_pos.x;
    int dy = end_pos.y - begin_pos.y;

    int xi = 1;

    if (dx < 0) {
      xi = -1;
      dx = -dx;
    }

    int D = 2 * dx - dy;
    int x = begin_pos.x;

    for (int y = begin_pos.y; y <= end_pos.y; ++y) {
      result.push_back({x, y});
      if (D > 0) {
        x += xi;
        D -= 2 * dy;
      }

      D += 2 * dx;
    }
  };

  auto plot_line_low = [&](const Vec2 &begin_pos, const Vec2 &end_pos) {
    int dx = end_pos.x - begin_pos.x;
    int dy = end_pos.y - begin_pos.y;

    int yi = 1;

    if (dy < 0) {
      yi = -1;
      dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = begin_pos.y;

    for (int x = begin_pos.x; x <= end_pos.x; ++x) {
      result.push_back({x, y});
      if (D > 0) {
        y += yi;
        D -= 2 * dx;
      }

      D += 2 * dy;
    }
  };

  if (std::abs(end.y - start.y) < std::abs(end.x - start.x)) {
    if (start.x > end.x) {
      plot_line_low(end, start);
    } else {
      plot_line_low(start, end);
    }
  } else {
    if (start.y > end.y) {
      plot_line_high(end, start);
    } else {
      plot_line_high(start, end);
    }
  }

  return result;
}

template <size_t w, size_t h>
void set_background(Image<w, h> &canvas, const Color &c) {
  std::fill(canvas.data.begin(), canvas.data.end(), c);
}

template <size_t w, size_t h>
void draw(Image<w, h> &canvas, const std::vector<Vec2> &positions,
          const Color &c = {255u, 0u, 0u}) {
  for (const auto &pos : positions) {
    size_t i = static_cast<unsigned>(pos.y) * canvas.width() +
               static_cast<unsigned>(pos.x);
    auto &pixel = canvas.data.at(i);
    pixel = c;
  }
}

} // namespace MyRender
