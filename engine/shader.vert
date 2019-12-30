#version 320 es

layout(location = 0) in vec2 a_pos;
out mediump vec4 tri_color;

void main()
{
  tri_color = vec4(a_pos, 0.0, 1.0);
  gl_Position = vec4(a_pos.x, a_pos.y, 0.0, 1.0);
}
