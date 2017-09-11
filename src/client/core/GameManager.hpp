#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP


#include "Window.hpp"

class GameManager
{

public:
	GameManager();
	~GameManager();
	GameManager& instance();

protected:
	void run();
};

#endif // !GAMEMANAGER_HPP