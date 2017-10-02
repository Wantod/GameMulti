#ifndef SHADER_HPP_
# define SHADER_HPP_

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

# include <GL/glew.h>
# include <glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	~Shader();


	void operator=(const Shader& s) {
		_id = s.getId();
	}

	GLuint getId() const { return _id; }
	Shader &use();
	Shader &load(const std::string &filename, GLenum type);
	Shader &link();
	Shader &Shader::compile(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");

	Shader &set(const GLchar *name, GLfloat value);
	Shader &set(const GLchar *name, GLint value);
	Shader &set(const GLchar *name, GLfloat x, GLfloat y);
	Shader &set(const GLchar *name, const glm::vec2 &value);
	Shader &set(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	Shader &set(const GLchar *name, const glm::vec3 &value);
	Shader &set(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	Shader &set(const GLchar *name, const glm::vec4 &value);
	Shader &set(const GLchar *name, const glm::mat4 &matrix);
private:
	std::string &readFile(const std::string& filename);
	GLuint _id;
};

#endif // !SHADER_HPP_
