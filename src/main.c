/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:27:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/03/23 15:28:34 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		main(void)
{
	GLFWwindow				*win;
	GLuint					VertexArrayID;
	GLuint					vertexBuffer;
	static const GLfloat	g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	GLuint					vertex;
	GLuint					fragment;
	GLuint					program_id;

	if (!glfwInit())
	{
		ft_putstr("Failed to initialize GLFW\n");
		return (-1);
	}
	glfwWindowHint(GLFW_SAMPLES, ANTI_ALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win = glfwCreateWindow(1920, 1080, "Scop", NULL, NULL);
	if (win == NULL)
	{
		ft_putstr("Failed opening GLFW window\n");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(win);

	glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	fragment = create_shader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	vertex = create_shader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
	program_id = create_program(vertex, fragment);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program_id);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(program_id);
	glfwTerminate();
	return (0);
}
