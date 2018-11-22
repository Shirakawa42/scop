/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:10:05 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/22 16:24:00 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float	*generate_uv(float *vertex, int size, int *sizeuv)
{
	int		i;
	float	*uv;
	float	min_x;
	float	min_y;
	float	max_x;
	float	max_y;
	float	k_x;
	float	k_y;

	*sizeuv = size - (size / 3);
	uv = (float*)malloc(sizeof(float) * *sizeuv);
	max_x = 0.0f;
	max_y = 0.0f;
	min_x = 0.0f;
	min_y = 0.0f;
	i = 0;
	while (i < size)
	{
		max_x = fmaxf(max_x, vertex[i]);
		min_x = fminf(min_x, vertex[i]);
		max_y = fmaxf(max_y, vertex[i + 1]);
		min_y = fminf(min_y, vertex[i + 1]);
		i += 3;
	}
	k_x = 1 / (max_x - min_x);
	k_y = 1 / (max_y - min_y);
	i = 0;
	while (i < size)
	{
		uv[i - (i / 3)] = (vertex[i] - min_x) * k_x;
		uv[(i + 1) - (i / 3)] = (vertex[i + 1] - min_y) * k_y;
		i += 3;
	}
	return (uv);
}

void	center_object(float **vertex, int size)
{
	int		i;
	float	max_x;
	float	max_y;
	float	min_x;
	float	min_y;
	float	max_z;
	float	min_z;
	float	*vertices;
	float	scale;

	i = 0;
	max_x = 0.0f;
	max_y = 0.0f;
	min_x = 0.0f;
	min_y = 0.0f;
	min_z = 0.0f;
	max_z = 0.0f;
	scale = 0.0f;
	vertices = *vertex;
	while (i < size)
	{
		if (vertices[i] > max_x)
			max_x = vertices[i];
		if (vertices[i + 1] > max_y)
			max_y = vertices[i + 1];
		if (vertices[i] < min_x)
			min_x = vertices[i];
		if (vertices[i + 1] < min_y)
			min_y = vertices[i + 1];
		if (vertices[i + 2] < min_z)
			min_z = vertices[i + 2];
		if (vertices[i + 2] > max_z)
			max_z = vertices[i + 2];
		if (max_x > scale)
			scale = max_x;
		if (max_y > scale)
			scale = max_y;
		if (max_z > scale)
			scale = max_z;
		if (fabsf(min_x) > scale)
			scale = fabsf(min_x);
		if (fabsf(min_y) > scale)
			scale = fabsf(min_y);
		if (fabsf(min_z) > scale)
			scale = fabsf(min_z);
		i += 3;
	}
	g_matrix = matrix_matrix_mul(g_matrix, scaling_matrix(0.70f / scale));
	i = 0;
	max_x = (min_x + max_x) / 2;
	max_y = (min_y + max_y) / 2;
	max_z = (min_z + max_z) / 2;
	while (i < size)
	{
		vertices[i] -= max_x;
		vertices[i + 1] -= max_y;
		vertices[i + 2] -= max_z;
		i += 3;
	}
}

static void	add_vertex(char *str, float **vertex, int *size, int *error)
{
	float	*v;
	int		i;

	i = 0;
	v = *vertex;
	if (v == NULL)
		v = (float*)malloc(sizeof(float) * 3);
	else
		v = (float*)realloc(v, (*size + 3) * sizeof(float));
	if (v == NULL)
		*error = -1;
	*vertex = v;
	while (i < 3 && v != NULL)
	{
		while (*str && (*str < '0' || *str > '9') && *str != '-')
			*str++;
		v[*size] = ft_atof(str);
		*size += 1;
		while (*str && *str != ' ')
			*str++;
		i++;
		if (!*str && i < 3)
			*error = -1;
	}
}

static int	nb_indices_in_line(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] && (str[i] < '0' || str[i] > '9'))
			i++;
	}
	return (nb);
}

static int	add_indice2(int nb, unsigned int **indices, int *size, char *str)
{
	int				i;
	unsigned int	*v;

	v = *indices;
	i = 0;
	while (i < nb)
	{
		v[*size] = ft_atoi(str) - 1;
		*size += 1;
		while (*str >= '0' && *str <= '9')
			*str++;
		while (*str && (*str < '0' || *str > '9'))
			*str++;
		i++;
		if (!*str && i < nb)
			return (-1);
	}
	if (nb == 4)
	{
		v[*size] = v[*size - 1];
		v[*size - 1] = v[*size - 2];
		v[*size + 1] = v[*size - 4];
		*size += 2;
	}
	return (0);
}

static void	add_indice(char *str, unsigned int **indice, int *size, int *error)
{
	unsigned int	*v;
	int				i;
	int				nb;
	int				malloc_quads;

	i = 0;
	nb = nb_indices_in_line(str);
	malloc_quads = 0;
	if (nb == 4)
		malloc_quads = 2;
	v = *indice;
	if (v == NULL)
		v = (unsigned int*)malloc(sizeof(unsigned int) * (nb + malloc_quads));
	else
		v = (unsigned int*)realloc(v, (*size + nb + malloc_quads) *
				sizeof(unsigned int));
	if (v == NULL)
	{
		*error = -1;
		return ;
	}
	*indice = v;
	if (add_indice2(nb, indice, size, str) == -1)
		*error = -1;
}

int			parse(char *file, float **vertex, unsigned int **indices,
		int *vsize, int *isize)
{
	char 	*str;
	int		fd;
	int		error;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	str = NULL;
	while ((error = get_next_line(fd, &str)))
	{
		if (error == -1)
			return (-1);
		if (ft_strncmp(str, "v ", 2) == 0)
			add_vertex(&str[2], vertex, vsize, &error);
		else if (ft_strncmp(str, "f ", 2) == 0)
			add_indice(&str[2], indices, isize, &error);
		if (error == -1)
			return (-1);
	}
	return (0);
}
