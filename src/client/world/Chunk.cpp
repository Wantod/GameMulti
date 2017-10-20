#include "Chunk.hpp"

Chunk::Chunk(glm::ivec3 pos) : _position(pos)
{
	for (size_t x = 0; x < 16; x++)
		for (size_t y = 0; y < 16; y++)
			for (size_t z = 0; z < 16; z++)
			{
				//setBlock(x, y, z, 0);
				_block[(y << 8) + (z << 4) + x] = 0;
				if (y < 2 || (x == 1 && z == 0))
					_block[(y << 8) + (z << 4) + x] = 1;
					//setBlock(x, y, z, 1);
			}
}

Chunk::~Chunk()
{
}

void Chunk::load()
{
	std::vector<Vertex> vert;
	glm::vec3 color(0, 0.796, 0);

	glm::vec3 color2 = color;
	glm::vec3 color3 = color;
	color2 -= 0.03;
	color3 -= 0.06;

	for (int y = 0; y < 16; y++)
	for (int z = 0; z < 16; z++)
	for (int x = 0; x < 16; x++)
	{
		if (getBlock(x, y, z) == 0)
			continue;

			glm::vec3 point[8] = {
				glm::vec3(0 + x,0+y,1 + z),
				glm::vec3(1 + x,0 + y,1 + z),
				glm::vec3(1 + x,0 + y,0 + z),
				glm::vec3(0 + x,0+y,0 + z),
				glm::vec3(0 + x,1+y,1 + z),
				glm::vec3(1 + x,1+y,1 + z),
				glm::vec3(1 + x,1+y,0 + z),
				glm::vec3(0 + x,1+y,0 + z)
			};


			if (getBlock(x, y, z + 1) == 0) {
				// face
				vert.push_back(Vertex{ point[0], color });
				vert.push_back(Vertex{ point[5], color });
				vert.push_back(Vertex{ point[4], color });
				vert.push_back(Vertex{ point[0], color });
				vert.push_back(Vertex{ point[1], color });
				vert.push_back(Vertex{ point[5], color });
			}

			if (getBlock(x, y, z - 1) == 0) {
				// deriere
				vert.push_back(Vertex{ point[2], color });
				vert.push_back(Vertex{ point[3], color });
				vert.push_back(Vertex{ point[6], color });
				vert.push_back(Vertex{ point[6], color });
				vert.push_back(Vertex{ point[3], color });
				vert.push_back(Vertex{ point[7], color });
			}
			if (getBlock(x, y - 1, z) == 0) {
				// dessou
				vert.push_back(Vertex{ point[0], color3 });
				vert.push_back(Vertex{ point[3], color3 });
				vert.push_back(Vertex{ point[2], color3 });
				vert.push_back(Vertex{ point[0], color3 });
				vert.push_back(Vertex{ point[2], color3 });
				vert.push_back(Vertex{ point[1], color3 });
			}

			if (getBlock(x, y + 1, z) == 0) {
				//dessu
				vert.push_back(Vertex{ point[4], color3 });
				vert.push_back(Vertex{ point[6], color3 });
				vert.push_back(Vertex{ point[7], color3 });
				vert.push_back(Vertex{ point[4], color3 });
				vert.push_back(Vertex{ point[5], color3 });
				vert.push_back(Vertex{ point[6], color3 });
			}

			if (getBlock(x + 1, y, z) == 0) {
				// droit
				vert.push_back(Vertex{ point[1], color2 });
				vert.push_back(Vertex{ point[2], color2 });
				vert.push_back(Vertex{ point[6], color2 });
				vert.push_back(Vertex{ point[1], color2 });
				vert.push_back(Vertex{ point[6], color2 });
				vert.push_back(Vertex{ point[5], color2 });
			}

			if (getBlock(x - 1, y, z) == 0) {
				// gauche
				vert.push_back(Vertex{ point[0], color2 });
				vert.push_back(Vertex{ point[7], color2 });
				vert.push_back(Vertex{ point[3], color2 });
				vert.push_back(Vertex{ point[0], color2 });
				vert.push_back(Vertex{ point[4], color2 });
				vert.push_back(Vertex{ point[7], color2 });
			}
		}
	if (vert.size() > 0) {
		mesh.setVertice(vert);
		mesh.load();
	}
}

void Chunk::update()
{
}

void Chunk::render()
{
	glm::mat4 model(1);
	model = glm::translate(model, glm::vec3(_position.x << 4, _position.y << 4, _position.z << 4));
	mesh.draw(model);
}

const glm::vec3 Chunk::getPos() const {
	return _position;
}

void Chunk::setBlock(int x, int y, int z, unsigned int b) {
	int pos = (y << 8) + (z << 4) + x;
	if (pos & 0XFFF != pos)
		return ;
	_block[pos] = b;
}

unsigned int  Chunk::getBlock(int x, int y, int z) const {
	if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
		return 0;
	return _block[(y << 8) + (z << 4) + x];
}
