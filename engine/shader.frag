#version 320 es
precision mediump float;

//in mediump vec4 tri_color;
out mediump vec4 color;

uniform float time;
uniform mediump vec2 resolution;

void main() {

    float t = time*0.1;
    float t2 = time*4.0;


    vec2 position = ( gl_FragCoord.xy / resolution.xy ) - 0.5;
    position *= 1.25;
    position.y *= dot(position,position);

    position.y *= 1.0+sin(position.x*3.0+t2)*0.2;

    float foff = 0.7;
    float den = 0.05;
    float amp = 0.15;
    float freq = 12.;
    float offset = 0.1-sin(position.x*0.5)*0.05;


    vec3 colour = vec3 (0.13, 0.3, 0.13) *
         ((1.0 / abs((position.y + (amp * sin(((position.x*4.0 + t) + offset) *freq)))) * den)
        + (1.0 / abs((position.y + (amp * sin(((position.x*4.0 + t) + offset) *freq+foff)))) * den)
        + (1.0 / abs((position.y + (amp * sin(((position.x*4.0 + t) + offset) *freq-foff)))) * den));

    color = vec4( colour, 1.0 );

}
