/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:28:07 by lvasseur          #+#    #+#             */
/*   Updated: 2018/03/02 16:07:26 by lvasseur         ###   ########.fr       */
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

	if (!(fd = open(filename, O_RDONLY)))
		return (NULL);
	while (r = read(fd, buf, BUFF_SIZE))
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
	GLint		compile_status;

	compile_status = GL_TRUE;
	shader = glCreateShader(shadertype);
	file = load_file(filename);
	glShaderSource(shader, 1, (const GLchar**)&file, NULL);
	glCompileShader(shader);
	free(file);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE)
	{
		ft_putstr("Erreur dans la compilation du shader\n");
		return -1;
	}
	return (shader);
}
