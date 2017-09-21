#include "ResourceManager.hpp"

ResourceManager::ResourceManager(): text(200, 100)
{}

ResourceManager::~ResourceManager()
{
	//delete sprit;
}

ResourceManager& ResourceManager::get()
{
	static ResourceManager res;
	return res;
}

void ResourceManager::init() {
	textureShader = getShader("texture");
	textShader = getShader("text");

	// text
	text.TextShader = textShader;
	text.Load("./data/Fonts/Arial-Unicode-MS.ttf", 12);

	// sprit 2D
	sprit.setShader(textureShader);
}

void ResourceManager::resize(int w, int h) {
	text.update(w, h);
	textureShader.use();
	textureShader.set("sprite", 0);
	textureShader.set("projection", glm::ortho(0.0f, static_cast<GLfloat>(w), static_cast<GLfloat>(h), 0.0f, 0.0f, 1.0f));
}

Shader& ResourceManager::getShader(const std::string& fileName) {

	if (_shader.find(fileName) == _shader.end()) {
		Shader sh;
		sh.compile(std::string("./data/Shaders/"+fileName+".vs"), std::string("./data/Shaders/"+fileName+".frag"));
		_shader.emplace(fileName, sh);
	}

	return _shader[fileName];
}

Texture& ResourceManager::getTexture(std::string name, GLboolean alpha) {

	if (_texture.find(name) == _texture.end()) {
		std::string filename = std::string("./data/Textures/" + name);
		Texture texture = Texture::load(filename.c_str(), alpha);
		_texture.emplace(name, texture);
	}

	return _texture[name];
}