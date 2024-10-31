#include "StateMenu.h"

StateMenu::StateMenu(Game* game) : game{game} {
}

void StateMenu::OnEnter() {
	game->window.setView(view);
}
void StateMenu::Update() {
}

void StateMenu::Render(double deltaTime) {
}
void StateMenu::OnSFMLEvent(const sf::Event& event) {
	// if (event.type == event.KeyPressed)
	// game->PushState(std::make_unique<StatePlay>(game));
}
