#version 400

in vec2 UV;
in vec3 color;
out vec4 frag_colour;

uniform sampler2D text;
uniform int		which;

void main() {
	frag_colour = vec4(texture(text, UV).rgb, 1.0);
	if (which == 0)
		frag_colour = vec4(color, 1.0);
}