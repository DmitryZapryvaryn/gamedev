#pragma once

#include <memory>
#include <vector>

#include <image.hpp>
#include <render_triangle.hpp>

namespace MyRender {

struct vertex {
  double x = 0;
  double y = 0;
  double r = 0;
  double g = 0;
  double b = 0;
  double u = 0;
  double v = 0;
};

double interpolate(const double a, const double b, const double t) {
  return a + (b - a) * t;
}

vertex interpolate(const vertex &v1, const vertex &v2, double t) {
  return {
      interpolate(v1.x, v2.x, t), interpolate(v1.y, v2.y, t),
      interpolate(v1.r, v2.r, t), interpolate(v1.g, v2.g, t),
      interpolate(v1.b, v2.b, t), interpolate(v1.u, v2.u, t),
      interpolate(v1.v, v2.v, t),
  };
}

struct gfx_program {
  ~gfx_program() = default;
  virtual vertex vertex_shader(const vertex &in) = 0;
  virtual color fragment_shader(const vertex &in) = 0;
};

class render_interpolated {
public:
  void set_program(std::unique_ptr<gfx_program> program) {
    program_ = std::move(program);
  }

  void draw_triangles(const std::vector<vertex> &vertices,
                      const std::vector<uint16_t> &indexes) {

    for (size_t i = 0; i < indexes.size(); i += 3) {
      const vertex &v1 = vertices.at(indexes.at(i + 0));
      const vertex &v2 = vertices.at(indexes.at(i + 1));
      const vertex &v3 = vertices.at(indexes.at(i + 2));

      const vertex &v1_ = program_->vertex_shader(v1);
      const vertex &v2_ = program_->vertex_shader(v2);
      const vertex &v3_ = program_->vertex_shader(v3);

      for (const auto &v : rasterize_triangle(v1_, v2_, v3_)) {
        const color c = program_->fragment_shader(v);
        position position(static_cast<int>(v.x), static_cast<int>(v.y));
        img.set_pixel(position, c);
      }
    }
  }

private:
  // std::vector<vertex> fill_triangle(const vertex& top, const vertex& middle,
  // const vertex& bottom);

  std::vector<vertex> rasterize_triangle(const vertex &v1, const vertex &v2,
                                         const vertex &v3) {
    std::array<vertex, 3> vertices = {v1, v2, v3};
    std::sort(vertices.begin(), vertices.end(),
              [](vertex &lhs, vertex &rhs) { return lhs.y < rhs.y; });

    const vertex &top_v = vertice[0];
    const vertex &middle_A_v = vertice[1];
    const vertex &bottom_v = vertice[2];

    position top_pos(static_cast<int>(std::round(top_v.x)),
                     static_cast<int>(std::round(top_v.y)));
    position middle_A_pos(static_cast<int>(std::round(middle_A_v.x)),
                          static_cast<int>(std::round(middle_A_v.y)));
    position bottom_pos(static_cast<int>(std::round(bottom_v.x)),
                        static_cast<int>(std::round(bottom_v.y)));

    if (middle_A_pos.y == bottom_pos.y) {
      return fill_triangle(top_v, middle_A_v, bottom_v);
    } else if (top_pos.y == middle_A_pos.y) {
      return fill_triangle(bottom_v, middle_A_v, top_v);
    } else {
      int x_middel_B =
          top_pos.x + ((middle_A_pos.y - top_pos.y) *
                       (bottom_pos.x - top_pos.x) / (bottom_pos.y - top_pos.y));

      if (top_pos.x > bottom_pos.x) {
        x_middel_B = top_pos.x -
                     ((middle_A_pos.y - top_pos.y) *
                      (top_pos.x - bottom_pos.x) / (bottom_pos.y - top_pos.y));
      }

      position middle_B(x_middel_B, middle_A_pos.y);

      auto top_triangle = fill_triangle(top_v, middle_A_v, middle_B);
      auto bottom_triangle = fill_triangle(bottom_v, middle_A_v, middle_B);

      std::vector<vertex> result(top_triangle.size() + bottom_triangle.size());
      std::move(top_triangle.begin(), top_triangle.end(),
                std::back_inserter(result));
      std::move(bottom_triangle.begin(), bottom_triangle.end(),
                std::back_inserter(result));

      return result;
    }
  }

  std::vector<vertex> fill_triangle(const vertex &top, const vertex &middle,
                                    const vertex &bottom) {

    std::vector<vertex> result;

    return result;
  }

  std::unique_ptr<gfx_program> program_;
  Image<600, 400> img;
};

} // namespace MyRender
