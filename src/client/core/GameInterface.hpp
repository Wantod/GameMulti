#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

class GameInterface
{
public:
	GameInterface();
	~GameInterface();
	
	virtual void display();
	virtual void update();
	virtual void resize();
};

#endif