/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:27:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/30 16:50:23 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	g_translation;
t_mat4	g_matrix;
t_mat4	g_projection;
float	g_delta_time;
GLint	g_which;

static void		init_global(void)
{
	g_delta_time = 0.0f;
	g_matrix = scaling_matrix(1.0f);
	g_translation = translation_matrix(0.0f, 0.0f, -1.25f);
	g_which = 0;
	g_projection = projection_matrix();
}

static int		initglfw(GLFWwindow **window)
{
	if (!glfwInit())
	{
		ft_putendl("ERROR: could not start GLFW3");
		return (-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	*window = glfwCreateWindow(W, H, "Scop", NULL, NULL);
	if (!*window)
	{
		ft_putendl("ERROR: could not open window with GLFW3");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(*window);
	glfwSetKeyCallback(*window, key_callback);
	return (0);
}

static void		init_opengl(t_buffer_objects *bo, t_obj obj)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenBuffers(1, &bo->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bo->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj.vsize * sizeof(float), obj.vertex,
			GL_STATIC_DRAW);
	glGenBuffers(1, &bo->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, bo->tbo);
	glBufferData(GL_ARRAY_BUFFER, obj.uvsize * sizeof(float), obj.uv,
			GL_STATIC_DRAW);
	glGenBuffers(1, &bo->ibo);
	glGenVertexArrays(1, &bo->vao);
	glBindVertexArray(bo->vao);
	glBindBuffer(GL_ARRAY_BUFFER, bo->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.isize * sizeof(unsigned int),
			obj.indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo->ibo);
	glBindVertexArray(0);
	glEnable(GL_MULTISAMPLE);
}

static void		glfw_loop(t_buffer_objects bo, t_obj obj,
		t_uniforms u, GLFWwindow **window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(u.shader_programme);
	glUniformMatrix4fv(u.matrix_id, 1, GL_FALSE, matrix_matrix_mul(
			matrix_matrix_mul(g_matrix, g_translation), g_projection).m);
	glUniform1i(u.which_id, g_which);
	glBindVertexArray(bo.vao);
	glDrawElements(GL_TRIANGLES, obj.isize, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	glfwPollEvents();
	events();
	time_handle();
	glfwSwapBuffers(*window);
}

int				main(int ac, char **av)
{
	GLuint				texture;
	t_obj				obj;
	GLFWwindow			*window;
	t_buffer_objects	bo;
	t_uniforms			u;

	if (ac != 2 || (obj = init_obj(av)).vsize == -1 || initglfw(&window) == -1)
		return (-1);
	init_global();
	center_object(&obj.vertex, obj.vsize);
	init_opengl(&bo, obj);
	texture = load_bmp("../texture/unicorn.bmp");
	u.shader_programme = create_program(create_shader("../shaders/vertex.glsl",
			GL_VERTEX_SHADER), create_shader("../shaders/fragment.glsl",
			GL_FRAGMENT_SHADER));
	u.matrix_id = glGetUniformLocation(u.shader_programme, "mvp");
	u.which_id = glGetUniformLocation(u.shader_programme, "which");
	while (!glfwWindowShouldClose(window) && glfwGetKey(window,
			GLFW_KEY_ESCAPE) != GLFW_PRESS)
		glfw_loop(bo, obj, u, &window);
	glfwTerminate();
	free(obj.indices);
	free(obj.vertex);
	free(obj.uv);
	return (0);
}
