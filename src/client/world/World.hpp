#ifndef WORLD_HPP_
# define WORLD_HPP_

# include <iostream>
# include <vector>
# include <complex>
# include <unordered_map>
#include <functional>
# include "Column.hpp"

bool operator==(const glm::ivec2& left, const glm::ivec2& right) noexcept;
namespace std
{
	template<>
	struct hash<glm::ivec2>
	{
		size_t operator()(const glm::ivec2& vect) const noexcept
		{
			std::hash<decltype(vect.x)> hasher;

			auto hash1 = hasher(vect.x);
			auto hash2 = hasher(vect.y);

			return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
		}
	};
}

class World
{
public:
	World();
	~World();

	void render();
	void update();

	void setBlock(int x, int y, int z, unsigned int b);
	unsigned int getBlock(int x, int y, int z) const;

private:
	std::unordered_map<glm::ivec2, Column *> _map;
};

#endif // !WORLD_HPP_