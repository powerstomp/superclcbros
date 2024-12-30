#ifndef _STATE_H
#define _STATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class State {
public:
	virtual void OnEnter() = 0;
	virtual void OnExit() {
	}
	virtual void Update() = 0;
	virtual void Render(double deltaTime) = 0;
	virtual void OnSFMLEvent(const sf::Event&) = 0;

	// Is this just a setup state?
	// Example: Start -> [Select player -> Select stage] -> Play
	// [intermediary stages] can all be popped in Game::PopState()
	virtual bool IsIntermediary() const {
		return false;
	}
};

#endif
