#include "scop.h"

GLuint	load_bmp(char *filename)
{
	unsigned char	header[54];
	unsigned int	dataPos;
	unsigned int	width;
	unsigned int	height;
	unsigned int	image_size;
	unsigned char	*data;
	int				fd;
	GLuint			textureID;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putendl("not a correct BMP file !");
		exit(0);
	}
	if (read(fd, header, 54) != 54)
	{
		ft_putendl("not a correct BMP file !");
		exit(0);
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		ft_putendl("not a correct BMP file !");
		exit(0);
	}
	dataPos    = *(int*)&(header[0x0A]);
	image_size  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	if (image_size == 0)
		image_size = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;
	data = (unsigned char*)malloc(sizeof(unsigned char) * image_size);
	read(fd, data, image_size);
	close(fd);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return (0);
}