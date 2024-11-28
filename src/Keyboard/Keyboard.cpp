#include "Keyboard.h"

#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <iostream>

Keyboard::Keyboard() {
	// Initialize default key bindings
	BindKey(sf::Keyboard::Left, Action::MOVE_LEFT);
	BindKey(sf::Keyboard::Right, Action::MOVE_RIGHT);
	BindKey(sf::Keyboard::Space, Action::JUMP);
	BindKey(sf::Keyboard::Up, Action::JUMP);
	BindKey(sf::Keyboard::Down, Action::DUCK);
	BindKey(sf::Keyboard::Z, Action::FIRE);
}

void Keyboard::BindKey(sf::Keyboard::Key key, Action action) {
	keyMap[key] = action;
}

void Keyboard::UnbindKey(sf::Keyboard::Key key) {
	keyMap.erase(key);
}

void Keyboard::HandleKeyPress(sf::Keyboard::Key key) {
	auto it = keyMap.find(key);
	if (it == keyMap.end()) {
		return;
	}

	onAction[static_cast<size_t>(it->second)].Emit();
}

void Keyboard::SaveKeyBindings(const std::string& filePath) {
	// Open the file for writing
	std::ofstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open file for writing keybindings: " << filePath
				  << std::endl;
		return;
	}

	for (const auto& pair : keyMap) {
		file << static_cast<int>(pair.first) << " " << static_cast<int>(pair.second)
			 << std::endl;
	}

	file.close();
}

void Keyboard::LoadKeyBindings(const std::string& filePath) {
	// Open the file for reading
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open file for reading keybindings: " << filePath
				  << std::endl;
		return;
	}

	// Clear the current key bindings
	keyMap.clear();

	// Read key bindings from the file
	int key, action;
	while (file >> key >> action) {
		keyMap[static_cast<sf::Keyboard::Key>(key)] = static_cast<Action>(action);
	}

	file.close();
}
