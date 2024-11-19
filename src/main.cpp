#include <memory>

#include "Game.h"
#include "Utility/ServiceLocator.h"
#include "Utility/TextureManager.h"

int main() {
	ServiceLocator<TextureManager>::Set(std::make_unique<TextureManager>());

	auto game = std::make_unique<Game>();
	game->Run();
}
