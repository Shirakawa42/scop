/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:35:59 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/29 16:37:57 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_uvcalc	init_uvcalc(float *vertex, int size)
{
	int			i;
	t_uvcalc	u;

	u.max_x = 0.0f;
	u.max_y = 0.0f;
	u.min_x = 0.0f;
	u.min_y = 0.0f;
	i = 0;
	while (i < size)
	{
		u.max_x = fmaxf(u.max_x, vertex[i]);
		u.min_x = fminf(u.min_x, vertex[i]);
		u.max_y = fmaxf(u.max_y, vertex[i + 1]);
		u.min_y = fminf(u.min_y, vertex[i + 1]);
		i += 3;
	}
	u.k_x = 1 / (u.max_x - u.min_x);
	u.k_y = 1 / (u.max_y - u.min_y);
	return (u);
}

float		*generate_uv(float *vertex, int size, int *sizeuv)
{
	int			i;
	float		*uv;
	t_uvcalc	u;

	*sizeuv = size - (size / 3);
	if ((uv = (float*)malloc(sizeof(float) * *sizeuv)) == NULL)
		return (NULL);
	u = init_uvcalc(vertex, size);
	i = 0;
	while (i < size)
	{
		uv[i - (i / 3)] = (vertex[i] - u.min_x) * u.k_x;
		uv[(i + 1) - (i / 3)] = (vertex[i + 1] - u.min_y) * u.k_y;
		i += 3;
	}
	return (uv);
}

t_maxmin	init_maxmin(void)
{
	t_maxmin	m;

	m.max_x = 0.0f;
	m.max_y = 0.0f;
	m.min_x = 0.0f;
	m.min_y = 0.0f;
	m.min_z = 0.0f;
	m.max_z = 0.0f;
	return (m);
}

t_maxmin	set_maxmin_and_scale(t_maxmin m, float *scale,
		float *vertices, int i)
{
	if (vertices[i] > m.max_x)
		m.max_x = vertices[i];
	if (vertices[i + 1] > m.max_y)
		m.max_y = vertices[i + 1];
	if (vertices[i] < m.min_x)
		m.min_x = vertices[i];
	if (vertices[i + 1] < m.min_y)
		m.min_y = vertices[i + 1];
	if (vertices[i + 2] < m.min_z)
		m.min_z = vertices[i + 2];
	if (vertices[i + 2] > m.max_z)
		m.max_z = vertices[i + 2];
	if (m.max_x > *scale)
		*scale = m.max_x;
	if (m.max_y > *scale)
		*scale = m.max_y;
	if (m.max_z > *scale)
		*scale = m.max_z;
	if (fabsf(m.min_x) > *scale)
		*scale = fabsf(m.min_x);
	if (fabsf(m.min_y) > *scale)
		*scale = fabsf(m.min_y);
	if (fabsf(m.min_z) > *scale)
		*scale = fabsf(m.min_z);
	return (m);
}

void		center_object(float **vertex, int size)
{
	int			i;
	t_maxmin	m;
	float		*vertices;
	float		scale;

	i = 0;
	m = init_maxmin();
	scale = 0.0f;
	vertices = *vertex;
	while (i < size)
	{
		m = set_maxmin_and_scale(m, &scale, vertices, i);
		i += 3;
	}
	g_matrix = matrix_matrix_mul(g_matrix, scaling_matrix(0.60f / scale));
	i = 0;
	m.max_x = (m.min_x + m.max_x) / 2;
	m.max_y = (m.min_y + m.max_y) / 2;
	m.max_z = (m.min_z + m.max_z) / 2;
	while (i < size)
	{
		vertices[i++] -= m.max_x;
		vertices[i++] -= m.max_y;
		vertices[i++] -= m.max_z;
	}
}
