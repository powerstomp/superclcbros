#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Entity/Mario.h"
#include "../Game.h"
#include "State.h"

class StateMenu : public State {
private:
	Game* game;
	sf::Text titleText;
	Mario mario;

public:
	StateMenu(Game*);

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render(double deltaTime) override;
	virtual void OnSFMLEvent(const sf::Event&) override;
};
