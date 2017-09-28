#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
public:
	Player();
	~Player();
	
	void updateInput(float deltatime, const Camera *camera);
};

#endif // ! PLAYER_HPP