#include "AnimationManager.h"

#include <fstream>
#include <iostream>

bool AnimationManager::Load(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open())
		return false;
	std::string name;
	while (file >> name) {
		std::list<Animation::Frame> frames;

		int duration, x, y, w, h;
		while (file >> duration >> x >> y >> w >> h)
			frames.push_back(Animation::Frame{duration, sf::IntRect{x, y, w, h}});
		file.clear();

		animations.emplace(name, Animation(frames));
		std::cout << "Loaded animation: " << name << '\n';
	}
	return true;
}

Animation AnimationManager::Get(const std::string& name) const {
	return animations.at(name);
}
