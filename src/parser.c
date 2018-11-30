/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:10:05 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/30 15:25:16 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		add_vertex(char *str, float **vertex, int *size, int *error)
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
			str++;
		v[*size] = ft_atof(str);
		*size += 1;
		while (*str && *str != ' ')
			str++;
		i++;
		if (!*str && i < 3)
			*error = -1;
	}
}

int			nb_indices_in_line(char *str)
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

static int	add_indice2(int nb, t_obj *obj, char *str)
{
	int				i;
	unsigned int	*v;

	v = obj->indices;
	i = 0;
	while (i < nb)
	{
		v[obj->isize] = ft_atoi(str) - 1;
		obj->isize += 1;
		while (*str >= '0' && *str <= '9')
			str++;
		while (*str && (*str < '0' || *str > '9'))
			str++;
		i++;
		if (!*str && i < nb)
			return (-1);
	}
	if (nb == 4)
	{
		v[obj->isize] = v[obj->isize - 1];
		v[obj->isize - 1] = v[obj->isize - 2];
		v[obj->isize + 1] = v[obj->isize - 4];
		obj->isize += 2;
	}
	return (0);
}

static void	add_indice(char *str, t_obj *obj, int *error)
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
	v = obj->indices;
	if (v == NULL)
		v = (unsigned int*)malloc(sizeof(unsigned int) * (nb + malloc_quads));
	else
		v = (unsigned int*)realloc(v, (obj->isize + nb + malloc_quads) *
				sizeof(unsigned int));
	if (v == NULL)
	{
		*error = -1;
		return ;
	}
	obj->indices = v;
	if (add_indice2(nb, obj, str) == -1)
		*error = -1;
}

int			parse(char *file, t_obj *obj)
{
	char	*str;
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
			add_vertex(&str[2], &obj->vertex, &obj->vsize, &error);
		else if (ft_strncmp(str, "f ", 2) == 0)
			add_indice(&str[2], obj, &error);
		if (error == -1)
			return (-1);
	}
	return (0);
}
