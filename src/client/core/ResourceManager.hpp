#ifndef RESOURCE_MANAGER_HPP
# define RESOURCE_MANAGER_HPP

# include <unordered_map>
# include <string>
# include "Sprit2D.hpp"
# include "Shader.hpp"
# include "Text2D.hpp"
# include "Texture.hpp"


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	
	static ResourceManager& get();
	void init();
	void resize(int x, int y);
	
	Shader& getShader(const std::string& fileName);
	Texture &getTexture(std::string name, GLboolean alpha);

	std::unordered_map<std::string, Shader> _shader;
	std::unordered_map<std::string, Texture> _texture;

	Sprit2D sprit;
	TextRenderer text;
	Shader textureShader;
	Shader textShader;
};

#endif // !RESOURCE_MANAGER_HPP