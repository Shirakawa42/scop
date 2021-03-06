/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:28:07 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/30 14:03:34 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char		*load_file(char *filename)
{
	char	buf[BUFF_SIZE];
	char	*file;
	char	*tmp;
	int		r;
	int		fd;

	file = ft_strnew(BUFF_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(0);
	while ((r = read(fd, buf, BUFF_SIZE)))
	{
		buf[r] = '\0';
		tmp = ft_strdup(file);
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	close(fd);
	return (file);
}

GLuint		create_shader(char *filename, int shadertype)
{
	GLuint		shader;
	char		*file;
	GLint		success;

	success = 0;
	shader = glCreateShader(shadertype);
	file = load_file(filename);
	glShaderSource(shader, 1, (const char **)&file, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		ft_putstr("Failed to compile shader\n");
		exit(0);
	}
	free(file);
	return (shader);
}

GLuint		create_program(GLuint vertex, GLuint fragment)
{
	GLuint		program_id;
	GLint		success;

	success = 0;
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex);
	glAttachShader(program_id, fragment);
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		ft_putstr("Failed to link program\n");
		exit(0);
	}
	glDetachShader(program_id, vertex);
	glDetachShader(program_id, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return (program_id);
}
