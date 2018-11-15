#include "scop.h"

t_vec3		matrix_mul(t_mat4 mat, t_vec3 vec)
{
	t_vec3	result;

	result.x = mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z;
	result.y = mat.m[4] * vec.x + mat.m[5] * vec.y + mat.m[6] * vec.z;
	result.z = mat.m[8] * vec.x + mat.m[9] * vec.y + mat.m[10] * vec.z;
	return (result);
}

t_mat4		matrix_matrix_mul(t_mat4 m, t_mat4 n)
{
	t_mat4	result;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			result.m[i * 4 + j] = 0.0f;
			while (k < 4)
			{
				result.m[i * 4 + j] += m.m[i * 4 + k] * n.m[k * 4 + j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_mat4		scaling_matrix(float scale)
{
	t_mat4	mat;
	int		i;

	i = 0;
	while (i < 16)
		mat.m[i++] = 0.0f;
	mat.m[0] = scale;
	mat.m[5] = scale;
	mat.m[10] = scale;
	mat.m[15] = 1.0f;
	return (mat);
}