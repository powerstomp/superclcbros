#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Game.h"
#include "State.h"

class StateMenu : public State {
private:
	sf::View view;
	Game* game;

public:
	StateMenu(Game*);

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render(double deltaTime) override;
	virtual void OnSFMLEvent(const sf::Event&) override;
};
