#ifndef TEXTRENDERER_HP
#define TEXTRENDERER_HP

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Core/Texture.hpp"
#include "../Core/Shader.hpp"


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance;     // Horizontal offset to advance to next glyph
};


class TextRenderer
{
public:
	std::map<GLchar, Character> Characters;
	Shader TextShader;
	TextRenderer(GLuint width, GLuint height);
	~TextRenderer();

	void Load(std::string font, GLuint fontSize);
	void update(GLuint width, GLuint height);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

private:
	GLuint VAO, VBO;
};

#endif // !TEXTRENDERER_HP