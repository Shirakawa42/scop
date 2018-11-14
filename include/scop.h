# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "glew.h"
# include <GLFW/glfw3.h>

# define OPENGL_VERSION "4.0"
# define ANTI_ALIASING 4
# define W 1280
# define H 1280

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

GLuint		create_program(GLuint vertex, GLuint fragment);
GLuint		create_shader(char *filename, int shadertype);
char		*load_file(char *filename);
t_vec3		rotation_matrix_x(t_vec3 vec, float angle);
t_vec3		rotation_matrix_y(t_vec3 vec, float angle);
t_vec3		rotation_matrix_z(t_vec3 vec, float angle);
