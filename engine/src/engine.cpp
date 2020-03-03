#include <engine.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// clang-format off
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <GLES3/gl3.h>
// clang-format on

#define CODE(...) #__VA_ARGS__

/*
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;

template <typename T> static void load_gl_func(std::string func_name, T &func) {
  void *gl_func_pointer = SDL_GL_GetProcAddress(func_name);
  if (gl_func_pointer == nullptr) {
    throw std::runtime_error("can't load GL function " + func_name);
  }

  func = reinterpret_cast<T>(gl_func_pointer);
}
*/
namespace MyEngine {

std::istream &operator>>(std::istream &in, vertex &v) {
  in >> v.x;
  in >> v.y;

  return in;
}

std::istream &operator>>(std::istream &in, triangle &tr) {
  in >> tr.v[0];
  in >> tr.v[1];
  in >> tr.v[2];

  return in;
}

std::string load_shader_src(const std::string &filename) {

  std::ifstream shader_file(filename, std::ios::in);
  if (!shader_file.good()) {
    throw new std::runtime_error("File '" + filename + "' doesn't exist!");
  }
  if (!shader_file.is_open()) {
    throw new std::runtime_error("Could not read file: " +
                                 std::string(filename));
  }

  std::string content;
  std::string line;
  while (std::getline(shader_file, line)) {
    content += line + "\n";
  }

  shader_file.close();

  return content;
}

GLuint init_shader(GLenum type, const GLchar *shader_src) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &shader_src, nullptr);
  glCompileShader(shader);

  GLint compile_status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == 0) {
    char infolog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infolog);
    glDeleteShader(shader);

    std::stringstream serr;
    serr << "Error compiling shader\n" << shader_src << "\n" << infolog;
    throw std::runtime_error(serr.str());
  }

  return shader;
}

Engine::Engine() : window(nullptr), gl_context(nullptr), program_id(0) {
  // Init SDL_INIT_TIMER, SDL_INIT_AUDIO, SDL_INIT_VIDEO, SDL_INIT_EVENTS,
  // SDL_INIT_JOYSTICK, SDL_INIT_HAPTIC, SDL_INIT_GAMECONTROLLER,
  // SDL_INIT_SENSOR
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::stringstream serr;
    serr << "Could not init sdl: " << SDL_GetError();
    throw std::runtime_error(serr.str());
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  window = SDL_CreateWindow(
      "Game Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS);

  if (window == nullptr) {
    std::stringstream serr;
    serr << "Could not create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    throw std::runtime_error(serr.str());
  }

  gl_context = SDL_GL_CreateContext(window);

  if (gl_context == nullptr) {
    std::stringstream serr;
    serr << "Could not create gl context: " << SDL_GetError() << std::endl;
    SDL_Quit();
    throw std::runtime_error(serr.str());
  }

  int gl_major_version = 0;
  SDL_assert(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
                                 &gl_major_version) == 0);

  int gl_minor_version = 0;
  SDL_assert(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
                                 &gl_minor_version) == 0);

  std::cout << "Major: " << gl_major_version << "; minor: " << gl_minor_version
            << std::endl;

  std::string vertex_shader_src = load_shader_src("shader.vert");
  GLuint vertex_shader =
      init_shader(GL_VERTEX_SHADER, vertex_shader_src.c_str());

  std::string fragment_shader_src2 = load_shader_src("shader.frag");
  /* const GLchar *fragment_shader_src =
     R"(
         #version 320 es

         in mediump vec4 tri_color;
         out mediump vec4 color;

         uniform mediump float time;

         void main()
         {
           color = vec4(tri_color.x, tri_color.y, sin(time), 1.0);
         }
         )";*/

  GLuint fragment_shader =
      init_shader(GL_FRAGMENT_SHADER, fragment_shader_src2.c_str());

  program_id = glCreateProgram();
  if (program_id == 0) {
    throw std::runtime_error("Failed to create a gl program");
  }

  glAttachShader(program_id, vertex_shader);
  glAttachShader(program_id, fragment_shader);

  glBindAttribLocation(program_id, 0, "a_pos");
  glLinkProgram(program_id);

  GLint link_status = 0;
  glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
  if (link_status == 0) {
    char infolog[512];
    glGetProgramInfoLog(program_id, 512, nullptr, infolog);
    glDeleteProgram(program_id);

    std::stringstream serr;
    serr << "Error linking program:\n" << infolog;
    throw std::runtime_error(serr.str());
  }

  glUseProgram(program_id);
}

float Engine::get_time_from_init() {
  std::uint32_t ms_from_library_initialization = SDL_GetTicks();
  float seconds = ms_from_library_initialization * 0.001f;
  return seconds;
}

void Engine::draw_triangle(const triangle &t) {
  // bind uniform
  GLint uTimeLocation = glGetUniformLocation(program_id, "time");

  if (uTimeLocation == -1) {
    std::cerr << "can't get uniform location from shader\n";
    throw std::runtime_error("can't get uniform location");
  }

  glUniform1f(uTimeLocation, get_time_from_init());

  GLint uResLocation = glGetUniformLocation(program_id, "resolution");

  if (uResLocation == -1) {
    std::cerr << "can't get uniform location from shader\n";
    throw std::runtime_error("can't get uniform location");
  }

  int w = 0, h = 0;
  SDL_GetWindowSize(window, &w, &h);

  glUniform2f(uResLocation, static_cast<float>(w), static_cast<float>(h));

  // bind vertexes
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), &t.v[0]);
  glEnableVertexAttribArray(0);
  glValidateProgram(program_id);

  GLint link_status = 0;
  glGetProgramiv(program_id, GL_VALIDATE_STATUS, &link_status);
  if (link_status == 0) {
    char infolog[512];
    glGetProgramInfoLog(program_id, 512, nullptr, infolog);
    glDeleteProgram(program_id);

    std::stringstream serr;
    serr << "Error linking program:\n" << infolog;
    throw std::runtime_error(serr.str());
  }

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::swap_buffers() {
  SDL_GL_SwapWindow(window);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Engine::handle_input() {

  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {

    switch (sdl_event.type) {
    case SDL_QUIT:
      return false;
      break;
    case SDL_KEYDOWN:
      std::cout << "Pressed ";
      handle_keys(sdl_event);
      break;
    case SDL_KEYUP:
      std::cout << "Released ";
      handle_keys(sdl_event);
      break;
    default:
      break;
    }
  }

  return true;
}

Engine::~Engine() {
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Engine::handle_keys(const SDL_Event &event) {
  switch (event.key.keysym.sym) {
  case SDLK_UP:
    std::cout << "Up" << std::endl;
    break;
  case SDLK_DOWN:
    std::cout << "Down" << std::endl;
    break;
  case SDLK_LEFT:
    std::cout << "Left" << std::endl;
    break;
  case SDLK_RIGHT:
    std::cout << "Right" << std::endl;
    break;
  case SDLK_ESCAPE:
    SDL_Event quit_event;
    quit_event.type = SDL_QUIT;
    SDL_PushEvent(&quit_event);
    break;
  }
}

} // namespace MyEngine
