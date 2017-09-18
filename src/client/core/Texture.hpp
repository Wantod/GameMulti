#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
	GLuint ID;
	GLuint Width, Height;

	GLuint Internal_Format; // Format of texture object
	GLuint Image_Format; // Format of loaded image

	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

	Texture();
	~Texture();
	static Texture &load(const GLchar *file, GLboolean alpha);
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

};

#endif // !TEXTURE2D_HPP