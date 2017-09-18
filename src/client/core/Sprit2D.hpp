#ifndef SPRITE_RENDERER_HPP
# define SPRITE_RENDERER_HPP

# include <GL/glew.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "Texture.hpp"
# include "Shader.hpp"


class Sprit2D
{
public:
	// Constructor (inits shaders/shapes)
	Sprit2D();
	// Destructor
	~Sprit2D();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void setShader(Shader &shader);
private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif // !SPRITE_RENDERER_HPP