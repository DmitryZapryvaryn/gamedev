#include <image.hpp>
#include <render_line.hpp>
#include <render_triangle.hpp>

#include <algorithm>
#include <random>
#include <tuple>
#include <vector>

const static uint16_t WIDTH = 600u;
const static uint16_t HEIGHT = 400u;

const static std::vector<std::vector<MyRender::position>> TEST_VERTICES = {
    {MyRender::position(10, 70), MyRender::position(50, 160), MyRender::position(70, 80)},
    {MyRender::position(180, 50), MyRender::position(150, 1), MyRender::position(70, 180)},
    {MyRender::position(180, 150), MyRender::position(120, 160),
     MyRender::position(130, 180)}};

using line_points = std::vector<std::pair<MyRender::position, MyRender::position>>;
using triangle_points =
    std::vector<std::tuple<MyRender::position, MyRender::position, MyRender::position>>;

line_points generate_lines_pos() {

  line_points result(100);

  using namespace MyRender;
  std::generate(result.begin(), result.end(), []() {
    return std::pair(position(std::rand() % WIDTH, std::rand() % HEIGHT),
                     position(std::rand() % WIDTH, std::rand() % HEIGHT));
  });

  return result;
}

triangle_points generate_triangle_vertices() {
  triangle_points result;

  using namespace MyRender;
  for (int i = 0; i < WIDTH - 60; i += 60) {
    for (int j = 0; j < HEIGHT - 40; j += 40) {
      result.emplace_back(
          std::tuple(position(i, j), position(i + 60, j), position(i, j + 40)));
    }
  }

  return result;
}

int main() {

  // line test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    img.set_background({255, 255, 255});

    for (const auto &[start_point, end_point] : generate_lines_pos()) {
      const auto line_positions = get_line_positions(start_point, end_point);
      img.draw(line_positions);
    }

    img.save("lines.ppm");
  }

  // triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    img.set_background({255u, 255u, 255u});

    for (const auto &[v1, v2, v3] : generate_triangle_vertices()) {
      const auto triangle_positions = get_triangle_positions(v1, v2, v3);
      img.draw(triangle_positions);
    }

    img.save("triangles.ppm");
  }

  // indexed triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    img.set_background({255, 255, 255});

    std::vector<position> vertices = {position(20, 30), position(156, 23), position(90, 300),
                                  position(400, 230)};
    std::vector<uint8_t> indexes = {1, 2, 0, 3, 0, 1};

    draw_indexed_triangle(img, vertices, indexes);

    img.save("triangles_indexed.ppm");
  }

  // fill triangle test
  {
    using namespace MyRender;
    Image<600u, 400u> img;
    img.set_background({0, 0, 0});

    for (const auto &vertices : TEST_VERTICES) {
      const auto filled_triangle_positions =
          rasterize_triangle(vertices[0], vertices[1], vertices[2]);

      img.draw(filled_triangle_positions);
    }

    img.save("filled_triangle.ppm");
  }
}
