/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.mation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:17:29 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/14 18:37:52 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	rotation_matrix_x(float angle)
{
	t_mat4	rot;
	int		i;

	i = 0;
	while (i < 16)
		rot.m[i++] = 0.0f;
	rot.m[0] = 1.0f;
	rot.m[5] = cos(angle);
	rot.m[6] = -sin(angle);
	rot.m[9] = sin(angle);
	rot.m[10] = cos(angle);
	rot.m[15] = 1.0f;
	return (rot);
}

t_mat4	rotation_matrix_y(float angle)
{
	t_mat4	rot;
	int		i;

	i = 0;
	while (i < 16)
		rot.m[i++] = 0.0f;
	rot.m[0] = cos(angle);
	rot.m[2] = sin(angle);
	rot.m[5] = 1.0f;
	rot.m[8] = -sin(angle);
	rot.m[10] = cos(angle);
	rot.m[15] = 1.0f;
	return (rot);
}

t_mat4	rotation_matrix_z(float angle)
{
	t_mat4	rot;
	int		i;

	i = 0;
	while (i < 16)
		rot.m[i++] = 0.0f;
	rot.m[0] = cos(angle);
	rot.m[1] = -sin(angle);
	rot.m[4] = sin(angle);
	rot.m[5] = cos(angle);
	rot.m[10] = 1.0f;
	rot.m[15] = 1.0f;
	return (rot);
}
