#version 400

in vec2 UV;
out vec4 frag_colour;

uniform sampler2D text;

void main() {
  frag_colour = vec4(texture(text, UV).rgb, 1.0);
}