#include "Mario.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Utility/ServiceLocator.h"
#include "../Utility/TextureManager.h"

Mario::Mario(sf::Vector2f position)
	: Player(position),
	  sprite{ServiceLocator<TextureManager>::Get().GetOrLoad("assets/mario.png")},
	  animationRunning{
		  Animation::Frame{.duration = 3, .dimensions = sf::IntRect{90, 52, 16, 32}},
		  Animation::Frame{.duration = 3, .dimensions = sf::IntRect{120, 52, 16, 32}},
		  Animation::Frame{.duration = 3, .dimensions = sf::IntRect{150, 52, 16, 32}},
	  },
	  animationStanding{
		  Animation::Frame{.duration = 3, .dimensions = sf::IntRect{180, 52, 16, 32}}
	  } {
}
void Mario::Update() {
	animationRunning.Update(sprite);
	sprite.setPosition(GetPosition());
}

const sf::Sprite* const Mario::GetSprite() const {
	return &sprite;
}
