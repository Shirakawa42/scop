/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:27:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/29 16:50:52 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	g_translation;
t_mat4	g_matrix;
t_mat4	g_translation;
float	g_delta_time;
GLint	g_which;

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
	float			*uv;
	int				sizeuv;
	GLuint			textureID;
	GLuint			texture;
	t_mat4			projection;
	t_obj			obj;

	obj.vertex = NULL;
	obj.indices = NULL;
	obj.isize = 0;
	obj.vsize = 0;

	if (ac < 2)
		return (-1);
	if (parse(av[1], &obj) == -1)
		return (-1);

	g_delta_time = 0.0f;
	g_matrix = scaling_matrix(1.0f);
	g_translation = translation_matrix(0.0f, 0.0f, -1.25f);
	projection = projection_matrix();
	center_object(&obj.vertex, obj.vsize);
	uv = generate_uv(obj.vertex, obj.vsize, &sizeuv);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	int error;

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
	glBufferData(GL_ARRAY_BUFFER, obj.vsize * sizeof(float), obj.vertex, GL_STATIC_DRAW);

	GLuint tbo = 0;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeuv * sizeof(float), uv, GL_STATIC_DRAW);

	GLuint	ibo;
	glGenBuffers(1, &ibo);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.isize * sizeof(unsigned int), obj.indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindVertexArray(0);

	texture = load_bmp("../texture/unicorn.bmp");

	GLuint vs = create_shader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = create_shader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint shader_programme = create_program(vs, fs);

	GLint	matrixID = glGetUniformLocation(shader_programme, "mvp");
	GLint	whichID = glGetUniformLocation(shader_programme, "which");
	glfwSetKeyCallback(window, key_callback);
	glEnable(GL_MULTISAMPLE);

	g_which = 0;
	while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, matrix_matrix_mul(matrix_matrix_mul(g_matrix, g_translation), projection).m);
		glUniform1i(whichID, g_which);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, obj.isize, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);

		glfwPollEvents();
		events();
		time_handle();
		glfwSwapBuffers(window);
		if (((error = glGetError()) != GL_NO_ERROR))
		{
			ft_putendl(gluErrorString(error));
		}
	}
	glfwTerminate();
	free(obj.indices);
	free(obj.vertex);
	free(uv);
	return 0;
}
