#include "AssetManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>

template <typename T>
bool AssetManager<T>::Load(const std::string& path) {
	T texture;
	if (!texture.loadFromFile(path))
		return false;
	data[path] = texture;
	return true;
}
template <typename T>
bool AssetManager<T>::Has(const std::string& path) const {
	return data.find(path) != data.end();
}
template <typename T>
const T& AssetManager<T>::GetOrLoad(const std::string& path) {
	auto it = data.find(path);
	if (it != data.end())
		return it->second;
	if (!Load(path))
		throw std::runtime_error("Couldn't load file: " + path);
	return Get(path);
}
template <typename T>
const T& AssetManager<T>::Get(const std::string& path) const {
	return data.at(path);
}
