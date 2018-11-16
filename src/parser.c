#include "scop.h"

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
	{
		*error = -1;
		return ;
	}
	*vertex = v;
	while (i < 3)
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

static void	add_indice(char *str, unsigned int **indice, int *size, int *error)
{
	unsigned int	*v;
	int				i;
	int				nb;

	i = 0;
	nb = nb_indices_in_line(str);
	v = *indice;
	if (v == NULL)
		v = (unsigned int*)malloc(sizeof(unsigned int) * nb);
	else
		v = (unsigned int*)realloc(v, (*size + nb) * sizeof(unsigned int));
	if (v == NULL)
	{
		*error = -1;
		return ;
	}
	*indice = v;
	while (i < nb)
	{
		v[*size] = ft_atoi(str);
		*size += 1;
		while (*str >= '0' && *str <= '9')
			*str++;
		while (*str && (*str < '0' || *str > '9'))
			*str++;
		i++;
		if (!*str && i < nb)
			*error = -1;
	}
}

int			parse(char *file, float **vertex, unsigned int **indices, int *vsize, int *isize)
{
	char 	*str;
	int		fd;
	int		error;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	str = NULL;
	while (error = get_next_line(fd, &str))
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