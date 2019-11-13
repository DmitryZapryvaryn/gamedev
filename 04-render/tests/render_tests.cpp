#include <image.hpp>
#include <render_line.hpp>
#include <render_triangle.hpp>

#include <algorithm>
#include <random>
#include <tuple>
#include <vector>

std::vector<std::pair<MyRender::Vec2, MyRender::Vec2>> generate_lines_pos() {}

int main() {

    // line test
  {
    MyRender::Image<600u, 400u> img;

    MyRender::set_background(img, {255u, 255u, 255u});
    {
      const auto line_positions = MyRender::get_line_positions(
          {50, 50}, {static_cast<int>(img.width()) - 50,
                     static_cast<int>(img.height()) - 50});
      MyRender::draw(img, line_positions);
    }
    {
      const auto line_positions = MyRender::get_line_positions(
          {static_cast<int>(img.width()) - 50, 50},
          {50, static_cast<int>(img.height()) - 50});
      MyRender::draw(img, line_positions);
    }

    img.save("lines.ppm");
  }
}
