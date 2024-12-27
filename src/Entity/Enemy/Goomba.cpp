#include "Goomba.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"

sf::Sprite Goomba::GetSprite() {
	auto sprite =
		sf::Sprite(ServiceLocator<TextureManager>::Get().GetOrLoad("assets/goomba.png"));
	sprite.scale(1.5, 1.5);
	return sprite;
}

Goomba::Goomba(sf::Vector2f position, std::unique_ptr<EntityController> controller)
	: Enemy(GetSprite(), position, 100000, 4, -12, std::move(controller)) {
}
