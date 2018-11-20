#include "scop.h"

static t_vec3	sub_vec(t_vec3 x, t_vec3 y)
{
	t_vec3	result;

	result.x = x.x - y.y;
	result.y = x.y - y.y;
	result.z = x.z - y.z;
	return (result);
}

static t_vec3	create_vec(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

float		*calculate_normals(float *ve, int size)
{
	float	*normals;
	int		i;
	int		j;
	t_vec3	v;
	t_vec3	w;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;

	normals = (float*)malloc(sizeof(float) * (size / 3));
	i = 0;
	j = 0;
	while (i < size)
	{
		p1 = create_vec(ve[i], ve[i + 1], ve[i + 2]);
		p2 = create_vec(ve[i + 3], ve[i + 4], ve[i + 5]);
		p3 = create_vec(ve[i + 6], ve[i + 7], ve[i + 8]);
		v = sub_vec(p2, p1);
		w = sub_vec(p3, p1);
		normals[j] = (v.y * w.z) - (v.z * w.y);
		normals[j + 1] = (v.z * w.x) - (v.x * w.z);
		normals[j + 2] = (v.x * w.y) - (v.y * w.x);
		i += 9;
		j += 3;
	}
	return (normals);
}

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