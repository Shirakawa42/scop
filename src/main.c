/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:27:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/14 19:15:43 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	g_matrix;
float	g_delta_time;

void	time_handle()
{
	static float	current_frame = 0.0f;
	static float	last_frame = 0.0f;
	static int		fps = 0;
	static float	fpstime = 0.0f;

	current_frame = glfwGetTime();
	if (last_frame == 0.0f)
		last_frame = current_frame;
	g_delta_time = current_frame - last_frame;
	last_frame = current_frame;
	fps++;
	fpstime += g_delta_time;
	if (fpstime >= 1.0f)
	{
		printf("FPS: %d\n", fps);
		fpstime -= 1.0f;
		fps = 0;
	}
}

int		main(int ac, char **av)
{
	float			*points;
	unsigned int	*indices;
	int				sizev;
	int				sizei;

	points = NULL;
	indices = NULL;

	sizei = 0;
	sizev = 0;

	if (ac < 2)
		return (-1);
	if (parse(av[1], &points, &indices, &sizev, &sizei) == -1)
		return (-1);

	g_delta_time = 0.0f;
	g_matrix = scaling_matrix(1.0f);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(W, H, "Scop", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizev * sizeof(float), points, GL_STATIC_DRAW);

	GLuint	ibo;
	glGenBuffers(1, &ibo);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizei * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindVertexArray(0);

	GLuint vs = create_shader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = create_shader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint shader_programme = create_program(vs, fs);

	GLint	matrixID = glGetUniformLocation(shader_programme, "mvp");
	glfwSetKeyCallback(window, key_callback);

	while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, g_matrix.m);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizei, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);

		glfwPollEvents();
		events();
		time_handle();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	free(indices);
	free(points);
	return 0;
}
