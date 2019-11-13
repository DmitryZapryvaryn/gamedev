#pragma once

#include <render_line.hpp>

namespace MyRender {

std::vector<Vec2> get_triangle_positions(const Vec2 &vertice1,
                                         const Vec2 &vertice2,
                                         const Vec2 &vertice3) {

  // v1 -> v2
  auto edge1 = get_line_positions(vertice1, vertice2);

  // v2 -> v3
  auto edge2 = get_line_positions(vertice2, vertice3);

  // v3 -> v1
  auto edge3 = get_line_positions(vertice3, vertice1);

  std::vector<Vec2> result;

  result.reserve(edge1.size() + edge2.size() + edge3.size());
  std::move(edge1.begin(), edge1.end(), std::back_inserter(result));
  std::move(edge2.begin(), edge2.end(), std::back_inserter(result));
  std::move(edge3.begin(), edge3.end(), std::back_inserter(result));

  return result;
}

} // namespace MyRender
