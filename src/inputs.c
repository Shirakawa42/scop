#include "scop.h"

t_inputs	g_inputs;

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	uint8_t		top;

	if (key == 265 && action == GLFW_PRESS)
		g_inputs.up = 1;
	else if (key == 265 && action == GLFW_RELEASE)
		g_inputs.up = 0;
	if (key == 262 && action == GLFW_PRESS)
		g_inputs.right = 1;
	else if (key == 262 && action == GLFW_RELEASE)
		g_inputs.right = 0;
	if (key == 264 && action == GLFW_PRESS)
		g_inputs.down = 1;
	else if (key == 264 && action == GLFW_RELEASE)
		g_inputs.down = 0;
	if (key == 263 && action == GLFW_PRESS)
		g_inputs.left = 1;
	else if (key == 263 && action == GLFW_RELEASE)
		g_inputs.left = 0;
	if (key == 334 && action == GLFW_PRESS)
		g_inputs.zoomin = 1;
	else if (key == 334 && action == GLFW_RELEASE)
		g_inputs.zoomin = 0;
	if (key == 333 && action == GLFW_PRESS)
		g_inputs.zoomout = 1;
	else if (key == 333 && action == GLFW_RELEASE)
		g_inputs.zoomout = 0;
	if (key == 320 && action == GLFW_PRESS)
		g_which = 0;
	else if (key == 321 && action == GLFW_PRESS)
		g_which = 1;
	else if (key == 322 && action == GLFW_PRESS)
		g_which = 2;
	else if (key == 323 && action == GLFW_PRESS)
		g_which = 3;
}

void	events()
{
	if (g_inputs.up == 1)
		g_matrix = matrix_matrix_mul(g_matrix, rotation_matrix_x(-3.0f * g_delta_time));
	else if (g_inputs.down == 1)
		g_matrix = matrix_matrix_mul(g_matrix, rotation_matrix_x(3.0f * g_delta_time));
	if (g_inputs.zoomout == 1)
		g_matrix = matrix_matrix_mul(g_matrix, scaling_matrix((1.0f - g_delta_time)));
	else if (g_inputs.zoomin == 1)
		g_matrix = matrix_matrix_mul(g_matrix, scaling_matrix((1.0f + g_delta_time)));
	if (g_inputs.right == 1)
		g_matrix = matrix_matrix_mul(g_matrix, rotation_matrix_y(3.0f * g_delta_time));
	else if (g_inputs.left == 1)
		g_matrix = matrix_matrix_mul(g_matrix, rotation_matrix_y(-3.0f * g_delta_time));
	else
		g_matrix = matrix_matrix_mul(g_matrix, rotation_matrix_y(1.0f * g_delta_time));
}