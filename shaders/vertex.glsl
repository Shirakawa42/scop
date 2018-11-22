#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
flat out vec3 color;

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
	color = vec3(vertex_position.x * 0.5f + 0.5f, vertex_position.y * 0.5f + 0.5f, vertex_position.z * 0.5f + 0.5f);
	if (color.x < 0.3f)
		color.x += 0.3f;
	if (color.y < 0.3f)
		color.y += 0.3f;
	if (color.z < 0.3f)
		color.z += 0.3f;
	if (which == 1)
		UV = sphere_mapping();
	if (which == 2)
		UV = cylinder_mapping();
	if (which == 3)
		UV = vertexUV;
}