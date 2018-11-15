#version 400

layout(location = 0) in vec3 vertex_position;

uniform mat4 	mvp;

out vec3 colour;

void main() {
	colour = vec3(1, 0, 0);
	gl_Position = mvp * vec4(vertex_position, 1.0);
}