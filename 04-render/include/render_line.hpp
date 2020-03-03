#pragma once

#include <algorithm>
#include <image.hpp>

#include <math.h>
#include <vector>

namespace MyRender {

std::vector<position> get_line_positions(const position &start, const position &end) {

  std::vector<position> result;

  auto plot_line_high = [&](const position &begin_pos, const position &end_pos) {
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

  auto plot_line_low = [&](const position &begin_pos, const position &end_pos) {
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

} // namespace MyRender
