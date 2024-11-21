#include "Mario.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Utility/AnimationManager.h"
#include "../Utility/ServiceLocator.h"
#include "../Utility/TextureManager.h"

Mario::Mario(sf::Vector2f position)
	: Player(position),
	  sprite{ServiceLocator<TextureManager>::Get().GetOrLoad("assets/mario.png")},
	  animationRunning{ServiceLocator<AnimationManager>::Get().Get("large_mario_running")
	  },
	  animationStanding{ServiceLocator<AnimationManager>::Get().Get("large_mario_standing"
	  )} {
}
void Mario::Update() {
	animationRunning.Update(sprite);
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(GetPosition());
}

const sf::Sprite* const Mario::GetSprite() const {
	return &sprite;
}
