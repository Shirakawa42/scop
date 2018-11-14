/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:17:29 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/14 18:37:52 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3	rotation_matrix_x(t_vec3 vec, float angle)
{
	t_vec3	result;

	result.x = vec.x;
	result.y = cos(angle) * vec.y - sin(angle) * vec.z;
	result.z = sin(angle) * vec.y + cos(angle) * vec.z;
	return (result);
}

t_vec3	rotation_matrix_y(t_vec3 vec, float angle)
{
	t_vec3	result;

	result.x = cos(angle) * vec.x + sin(angle) * vec.z;
	result.y = vec.y;
	result.z = -sin(angle) * vec.x + cos(angle) * vec.z;
	return (result);
}

t_vec3	rotation_matrix_z(t_vec3 vec, float angle)
{
	t_vec3	result;

	result.x = cos(angle) * vec.x - sin(angle) * vec.y;
	result.y = sin(angle) * vec.x + cos(angle) * vec.y;
	result.z = vec.z;
	return (result);
}
