#include <image.hpp>
#include <render_line.hpp>
#include <render_triangle.hpp>

#include <algorithm>
#include <random>
#include <tuple>
#include <vector>

const static uint16_t WIDTH = 600u;
const static uint16_t HEIGHT = 400u;

using line_points = std::vector<std::pair<MyRender::Vec2, MyRender::Vec2>>;
using triangle_points =
    std::vector<std::tuple<MyRender::Vec2, MyRender::Vec2, MyRender::Vec2>>;

line_points generate_lines_pos() {

  line_points result(100);

  std::generate(result.begin(), result.end(), []() {
    return std::pair(MyRender::Vec2{std::rand() % WIDTH, std::rand() % HEIGHT},
                     MyRender::Vec2{std::rand() % WIDTH, std::rand() % HEIGHT});
  });

  return result;
}

triangle_points generate_triangle_vertices() {
  triangle_points result;

  for (int i = 0; i < WIDTH - 60; i += 60) {
    for (int j = 0; j < HEIGHT - 40; j += 40) {
      result.emplace_back(std::tuple(MyRender::Vec2{i, j},
                                     MyRender::Vec2{i + 60, j},
                                     MyRender::Vec2{i, j + 40}));
    }
  }

  return result;
}

int main() {

  // line test
  {
    MyRender::Image<600u, 400u> img;
    MyRender::set_background(img, {255u, 255u, 255u});

    for (const auto &[start_point, end_point] : generate_lines_pos()) {
      const auto line_positions =
          MyRender::get_line_positions(start_point, end_point);
      MyRender::draw(img, line_positions);
    }

    img.save("lines.ppm");
  }

  // triangle test
  {
    MyRender::Image<600u, 400u> img;
    MyRender::set_background(img, {255u, 255u, 255u});

    for (const auto &[v1, v2, v3] : generate_triangle_vertices()) {
      const auto triangle_positions =
          MyRender::get_triangle_positions(v1, v2, v3);
      MyRender::draw(img, triangle_positions);
    }

    img.save("triangle.ppm");
  }
}
