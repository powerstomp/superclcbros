#include "Mario.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Utility/AnimationManager.h"
#include "../Utility/ServiceLocator.h"
#include "../Utility/TextureManager.h"

Mario::Mario(sf::Vector2f position)
	: Player(position),
	  animationRunning{ServiceLocator<AnimationManager>::Get().Get("large_mario_running")
	  } {
	this->sprite =
		sf::Sprite(ServiceLocator<TextureManager>::Get().GetOrLoad("assets/mario.png"));
	this->sprite.scale(3, 3);
}
void Mario::Update() {
	Player::Update();
	animationRunning.Update(sprite);
}
