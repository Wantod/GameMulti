#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "core/Window.hpp"
# include "core/ResourceManager.hpp"
# include "states/Game.hpp"
# include "states/GameInterface.hpp"
# include "states/StateMain.hpp"

class GameManager
{
public:
	GameManager();
	~GameManager();
	//GameManager& instance();

	template<typename S, typename... Args>
	void setState(Args&&... args)
	{
		_stateTmp = std::make_unique<S>(std::forward<Args>(args)...);
		_stateChange = true;
	}

	//InputManager &input;
	std::unique_ptr<Window> window;
protected:
	void run();
	std::unique_ptr<GameInterface> _state;
	std::unique_ptr<GameInterface> _stateTmp;
	bool _stateChange = false;
};

#endif // !GAMEMANAGER_HPP