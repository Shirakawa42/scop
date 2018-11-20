#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

out vec2 UV;
out vec3 color;

uniform mat4 	mvp;
uniform int		which;

vec2 sphere_mapping() {
	return (vec2(asin(vertex_position.x) / 3.14 + 0.5, asin(vertex_position.y) / 3.14 + 0.5));
}

vec2 cylinder_mapping() {
	return (vec2(atan(vertex_position.z, vertex_position.x) / 3.14 * 0.5 + 0.5, vertex_position.y / 10.0) * 3);
}

void main() {
	gl_Position = mvp * vec4(vertex_position, 1.0);
	UV = vec2(0.0, 0.0);
	color = normalize(normal);
	if (which == 1)
		UV = sphere_mapping();
	if (which == 2)
		UV = cylinder_mapping();
	if (which == 3)
		UV = vertexUV;
}