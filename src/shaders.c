/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:28:07 by lvasseur          #+#    #+#             */
/*   Updated: 2018/02/22 16:40:26 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
	GLuint		VertexShaderID;
	GLuint		FragentShaderID;
	std::string	VertexShaderCode;

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
	}
	return 0;
}
