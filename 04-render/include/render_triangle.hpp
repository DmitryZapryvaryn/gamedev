#pragma once

#include <render_line.hpp>

#include <algorithm>

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

template <size_t w, size_t h>
void draw_indexed_triangle(Image<w, h> &img, const std::vector<Vec2> &vertices,
                           const std::vector<uint8_t> &indexes) {
  for (size_t i = 0; i < indexes.size(); i += 3) {
    const Vec2 v1 = vertices.at(indexes.at(i + 0));
    const Vec2 v2 = vertices.at(indexes.at(i + 1));
    const Vec2 v3 = vertices.at(indexes.at(i + 2));

    draw(img, get_triangle_positions(v1, v2, v3));
  }
}

std::vector<Vec2> fill_triangle(const Vec2 &top, const Vec2 &middle,
                                const Vec2 &bottom) {

  auto edge1 = get_line_positions(top, bottom);
  auto edge2 = get_line_positions(top, middle);

  std::vector<Vec2> result;

  std::copy(edge1.begin(), edge1.end(), std::back_inserter(result));
  std::copy(edge2.begin(), edge2.end(), std::back_inserter(result));

  std::sort(edge1.begin(), edge1.end(),
            [](const Vec2 &lhs, const Vec2 &rhs) { return lhs.y < rhs.y; });
  std::sort(edge2.begin(), edge2.end(),
            [](const Vec2 &lhs, const Vec2 &rhs) { return lhs.y < rhs.y; });

  size_t i = 0;
  size_t j = 0;
  while (i < edge1.size() && j < edge2.size()) {
    if (edge1[i].y < edge2[j].y) {
      ++i;
    } else if (edge1[i].y > edge2[j].y) {
      ++j;
    } else {
      auto line = get_line_positions(edge1[i], edge2[j]);
      std::move(line.begin(), line.end(), std::back_inserter(result));
      ++i;
      ++j;
    }
  }

  return result;
}

std::vector<Vec2> rasterize_triangle(const Vec2 &vertice1, const Vec2 &vertice2,
                                     const Vec2 &vertice3) {

  std::array<Vec2, 3> vertices = {vertice1, vertice2, vertice3};
  std::sort(vertices.begin(), vertices.end(),
            [](Vec2 &lhs, Vec2 &rhs) { return lhs.y < rhs.y; });

  Vec2 top = vertices[0];
  Vec2 middle_A = vertices[1];
  Vec2 bottom = vertices[2];

  if (middle_A.y == bottom.y) {
    return fill_triangle(top, middle_A, bottom);
  } else if (top.y == middle_A.y) {
    return fill_triangle(bottom, middle_A, top);
  } else {
    int x_middel_B = top.x + ((middle_A.y - top.y) * (bottom.x - top.x) /
                              (bottom.y - top.y));

    if (top.x > bottom.x) {
      x_middel_B = top.x - ((middle_A.y - top.y) * (top.x - bottom.x) /
                            (bottom.y - top.y));
    }

    Vec2 middle_B(x_middel_B, middle_A.y);
    auto top_triangle = fill_triangle(top, middle_A, middle_B);
    auto bottom_triangle = fill_triangle(bottom, middle_A, middle_B);

    std::vector<Vec2> result(top_triangle.size() + bottom_triangle.size());
    std::move(top_triangle.begin(), top_triangle.end(),
              std::back_inserter(result));
    std::move(bottom_triangle.begin(), bottom_triangle.end(),
              std::back_inserter(result));

    return result;
  }
}

} // namespace MyRender
