#include <image.hpp>
#include <render_line.hpp>
#include <render_triangle.hpp>

#include <algorithm>
#include <random>
#include <tuple>
#include <vector>

const static uint16_t WIDTH = 600u;
const static uint16_t HEIGHT = 400u;

const static std::vector<std::vector<MyRender::Vec2>> TEST_VERTICES = {
    {MyRender::Vec2(10, 70), MyRender::Vec2(50, 160), MyRender::Vec2(70, 80)},
    {MyRender::Vec2(180, 50), MyRender::Vec2(150, 1), MyRender::Vec2(70, 180)},
    {MyRender::Vec2(180, 150), MyRender::Vec2(120, 160),
     MyRender::Vec2(130, 180)}};

using line_points = std::vector<std::pair<MyRender::Vec2, MyRender::Vec2>>;
using triangle_points =
    std::vector<std::tuple<MyRender::Vec2, MyRender::Vec2, MyRender::Vec2>>;

line_points generate_lines_pos() {

  line_points result(100);

  using namespace MyRender;
  std::generate(result.begin(), result.end(), []() {
    return std::pair(Vec2(std::rand() % WIDTH, std::rand() % HEIGHT),
                     Vec2(std::rand() % WIDTH, std::rand() % HEIGHT));
  });

  return result;
}

triangle_points generate_triangle_vertices() {
  triangle_points result;

  using namespace MyRender;
  for (int i = 0; i < WIDTH - 60; i += 60) {
    for (int j = 0; j < HEIGHT - 40; j += 40) {
      result.emplace_back(
          std::tuple(Vec2(i, j), Vec2(i + 60, j), Vec2(i, j + 40)));
    }
  }

  return result;
}

int main() {

  // line test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    set_background(img, {255, 255, 255});

    for (const auto &[start_point, end_point] : generate_lines_pos()) {
      const auto line_positions = get_line_positions(start_point, end_point);
      draw(img, line_positions);
    }

    img.save("lines.ppm");
  }

  // triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    set_background(img, {255u, 255u, 255u});

    for (const auto &[v1, v2, v3] : generate_triangle_vertices()) {
      const auto triangle_positions = get_triangle_positions(v1, v2, v3);
      draw(img, triangle_positions);
    }

    img.save("triangles.ppm");
  }

  // indexed triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    set_background(img, {255, 255, 255});

    std::vector<Vec2> vertices = {Vec2(20, 30), Vec2(156, 23), Vec2(90, 300),
                                  Vec2(400, 230)};
    std::vector<uint8_t> indexes = {1, 2, 0, 3, 0, 1};

    draw_indexed_triangle(img, vertices, indexes);

    img.save("triangles_indexed.ppm");
  }

  // fill triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    set_background(img, {0, 0, 0});

    for (const auto &vertices : TEST_VERTICES) {
      const auto filled_triangle_positions =
          rasterize_triangle(vertices[0], vertices[1], vertices[2]);

      draw(img, filled_triangle_positions);
    }

    img.save("filled_triangle.ppm");
  }
}
