# include "libft.h"
# include "libmat4.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <GLFW/glfw3.h>

# define OPENGL_VERSION "4.0"
# define ANTI_ALIASING 4

GLuint	LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
