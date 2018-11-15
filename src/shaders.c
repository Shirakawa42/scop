/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:28:07 by lvasseur          #+#    #+#             */
/*   Updated: 2018/03/06 13:45:07 by lvasseur         ###   ########.fr       */
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

	shader = glCreateShader(shadertype);
	file = load_file(filename);
	glShaderSource(shader, 1, (const char **)&file, NULL);
	glCompileShader(shader);
	free(file);
	return (shader);
}

GLuint		create_program(GLuint vertex, GLuint fragment)
{
	GLuint	program_id;

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex);
	glAttachShader(program_id, fragment);
	glLinkProgram(program_id);
	glDetachShader(program_id, vertex);
	glDetachShader(program_id, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return (program_id);
}
