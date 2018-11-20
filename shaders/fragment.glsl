#version 400

in vec2 UV;
flat in vec3 color;
out vec4 frag_colour;

uniform sampler2D text;
uniform int		which;

void main() {
	float g = dot(color, vec3(0.299, 0.587, 0.114));
	frag_colour = vec4(texture(text, UV).rgb, 1.0);
	if (which == 0)
		frag_colour = vec4(g, g, g, 1.0);
}