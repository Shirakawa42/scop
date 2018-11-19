# ifndef SCOP_H

# define SCOP_H

# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "glew.h"
# include <GLFW/glfw3.h>

# define OPENGL_VERSION "4.0"
# define ANTI_ALIASING 4
# define W 720
# define H 720

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct	s_mat4
{
	float	m[16];
}				t_mat4;

typedef struct	s_inputs
{
	short int up;
	short int down;
	short int left;
	short int right;
	short int zoomin;
	short int zoomout;
}				t_inputs;

extern t_mat4	g_matrix;
extern t_mat4	g_translation;
extern t_inputs	g_inputs;
extern float	g_delta_time;

GLuint		create_program(GLuint vertex, GLuint fragment);
GLuint		create_shader(char *filename, int shadertype);
char		*load_file(char *filename);
t_mat4		rotation_matrix_x(float angle);
t_mat4		rotation_matrix_y(float angle);
t_mat4		rotation_matrix_z(float angle);
t_mat4		matrix_matrix_mul(t_mat4 m, t_mat4 n);
t_vec3		matrix_mul(t_mat4 matrix, t_vec3 vec);
t_mat4		scaling_matrix(float scale);
void		key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void		events();
void		time_handle();
int			parse(char *file, float **vertex, unsigned int **indices, int *vsize, int *isize);
void		center_object_and_distance(float **vertex, int size);
float		*generate_uv(float *vertex, int size, int *sizeuv);
GLuint		load_bmp(char *filename);

#endif