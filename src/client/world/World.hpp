#ifndef WORLD_HPP_
# define WORLD_HPP_

# include <iostream>
# include <vector>
# include <complex>
# include <unordered_map>

# include "Chunk.hpp"

class World
{
public:
	World();
	~World();

	void render();
	void update();

	static int const WORLD_SIZE = 12; // 32
	static int const CHUNK_SIZE = 16;

private:
	Chunk chunk;

	std::unordered_map<int, Chunk *> _map;
};

#endif // !WORLD_HPP_