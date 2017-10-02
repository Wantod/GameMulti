#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "../core/Mesh.hpp"
#include "Entity.hpp"
#include "../Camera.hpp"

class Player : public Entity
{
public:
	Player();
	~Player();
	
	void updateInput(float deltatime, const Camera *camera);

	void update(float deltatime);
	void render(const Camera *camera);

protected:
	float _speedTimeTmp;
	bool _speed;

	Mesh tete;
	Mesh corp;
	Mesh pied1;
	Mesh pied2;
	Mesh bras1;
	Mesh bras2;

	float _speedDeplacement;
};

#endif // ! PLAYER_HPP