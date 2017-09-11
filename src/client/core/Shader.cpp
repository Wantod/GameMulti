#include "Shader.hpp"

Shader::Shader()
{
	_id = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(this->_id);
}

Shader &Shader::use()
{
	glUseProgram(this->_id);
	return *this;
}

std::string &Shader::readFile(const std::string& filename)
{
	std::ifstream file(filename);		// Create input file stream
	std::stringstream buffer;			// Create buffer	
	buffer << file.rdbuf();				// Read file into buffer
	std::string content = buffer.str();	// Convert buffer to string
	return content;
}

Shader& Shader::load(const std::string &filename, GLenum type)
{
	std::string fileContent = readFile(filename);	// Read shader file

	GLuint shader = glCreateShader(type);			// Create shader
	const char* source = fileContent.c_str();		// Create source from file
	glShaderSource(shader, 1, &source, 0);			// Set shader source
	glCompileShader(shader);						// Compile shader

	// IF shader hasn't compiled, print error data
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei length;
		char log[1024];
		glGetShaderInfoLog(shader, 1024, &length, log);
		std::cout << "Could not compile shader: " << shader << ": " << filename << std::endl;
		std::cout << log << std::endl;
		glDeleteShader(shader);
		return *this;
	}

	// attache le shader au programme
	glAttachShader(_id, shader);
	glDeleteShader(shader);
	return *this;
}

Shader &Shader::link()
{
	glLinkProgram(_id);
	GLint success;
	glGetProgramiv(_id, GL_LINK_STATUS, & success);
	if (!success)
	{
		GLsizei length;
		char log[1024];
		glGetShaderInfoLog(_id, 1024, &length, log);
		std::cout << "Could not compile shader: " << _id << ": " << vertexPath << std::endl;
		std::cout << log << std::endl;
		glDeleteShader(_id);
	}
	return *this;
}

Shader &Shader::compile(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath)
{
	loadShader(vertexPath, GL_VERTEX_SHADER);
	loadShader(fragmentPath, GL_FRAGMENT_SHADER);
	if (geometryPath != "")
		loadShader(geometryPath, GL_GEOMETRY_SHADER);
	return link();
}


void Shader::set(const GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(this->_id, name), value);
	return *this;
}
void Shader::set(const GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(this->_id, name), value);
	return *this;
}
void Shader::set(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(this->_id, name), x, y);
	return *this;
}
void Shader::set(const GLchar *name, const glm::vec2 &value)
{
	glUniform2f(glGetUniformLocation(this->_id, name), value.x, value.y);
	return *this;
}
void Shader::set(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(this->_id, name), x, y, z);
	return *this;
}
void Shader::set(const GLchar *name, const glm::vec3 &value)
{
	glUniform3f(glGetUniformLocation(this->_id, name), value.x, value.y, value.z);
	return *this;
}
void Shader::set(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(this->_id, name), x, y, z, w);
	return *this;
}
void Shader::set(const GLchar *name, const glm::vec4 &value)
{
	glUniform4f(glGetUniformLocation(this->_id, name), value.x, value.y, value.z, value.w);
	return *this;
}
void Shader::set(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	return *this;
}