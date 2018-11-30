/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:27:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/30 15:21:52 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	g_translation;
t_mat4	g_matrix;
float	g_delta_time;
GLint	g_which;

void		time_handle()
{
	float			current_frame;
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
		ft_putstr("FPS: ");
		ft_putnbr(fps);
		ft_putchar('\n');
		fpstime -= 1.0f;
		fps = 0;
	}
}

static t_obj	init_obj(char **av)
{
	t_obj	obj;

	obj.vertex = NULL;
	obj.indices = NULL;
	obj.uv = NULL;
	obj.isize = 0;
	obj.vsize = 0;
	obj.uvsize = 0;
	if (parse(av[1], &obj) == -1)
	{
		obj.vsize = -1;
		return (obj);
	}
	obj.uv = generate_uv(obj.vertex, obj.vsize, &obj.uvsize);
	return (obj);
}

static void		init_global(void)
{
	g_delta_time = 0.0f;
	g_matrix = scaling_matrix(1.0f);
	g_translation = translation_matrix(0.0f, 0.0f, -1.25f);
	g_which = 0;
}

static int		init_glfw(GLFWwindow **window)
{
	if (!glfwInit()) {
		ft_putendl("ERROR: could not start GLFW3");
		return (-1);
	} 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	*window = glfwCreateWindow(W, H, "Scop", NULL, NULL);
	if (!*window) {
		ft_putendl("ERROR: could not open window with GLFW3");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(*window);
	glfwSetKeyCallback(*window, key_callback);
	return (0);
}

static void	init_opengl(t_buffer_objects *bo, t_obj obj)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenBuffers(1, &bo->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bo->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj.vsize * sizeof(float), obj.vertex, GL_STATIC_DRAW);
	glGenBuffers(1, &bo->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, bo->tbo);
	glBufferData(GL_ARRAY_BUFFER, obj.uvsize * sizeof(float), obj.uv, GL_STATIC_DRAW);
	glGenBuffers(1, &bo->ibo);
	glGenVertexArrays(1, &bo->vao);
	glBindVertexArray(bo->vao);
	glBindBuffer(GL_ARRAY_BUFFER, bo->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.isize * sizeof(unsigned int), obj.indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo->ibo);
	glBindVertexArray(0);
	glEnable(GL_MULTISAMPLE);
}

int		main(int ac, char **av)
{
	GLuint				texture;
	t_mat4				projection;
	t_obj				obj;
	GLFWwindow			*window;
	t_buffer_objects	bo;
	GLuint				shader_programme;
	GLuint				vs;
	GLuint				fs;
	GLint				matrixID;
	GLint				whichID;

	if (ac != 2)
		return (-1);
	if ((obj = init_obj(av)).vsize == -1)
		return (-1);
	init_global();
	projection = projection_matrix();
	center_object(&obj.vertex, obj.vsize);
	if (init_glfw(&window) == -1)
		return (-1);
	//glewExperimental = GL_TRUE;
	//glewInit();
	init_opengl(&bo, obj);
	texture = load_bmp("../texture/unicorn.bmp");
	vs = create_shader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
	fs = create_shader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	shader_programme = create_program(vs, fs);
	matrixID = glGetUniformLocation(shader_programme, "mvp");
	whichID = glGetUniformLocation(shader_programme, "which");
	while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, matrix_matrix_mul(matrix_matrix_mul(g_matrix, g_translation), projection).m);
		glUniform1i(whichID, g_which);
		glBindVertexArray(bo.vao);
		glDrawElements(GL_TRIANGLES, obj.isize, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		glfwPollEvents();
		events();
		time_handle();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	free(obj.indices);
	free(obj.vertex);
	free(obj.uv);
	return (0);
}
