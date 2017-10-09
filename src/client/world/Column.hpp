#ifndef COLUMN_HPP
#define COLUMN_HPP value

#include "Chunk.hpp"
#include "Generation\GeneratorChunk.hpp"

class Column
{
public:
	Column();
	~Column();

	void load(GeneratorChunk& generator);
	

private:
	std::vector<Chunk> _chunks;
	glm::ivec2 _position;
	bool _load;
};


#endif