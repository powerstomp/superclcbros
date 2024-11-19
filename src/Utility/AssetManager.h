#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include <map>
#include <string>

template <typename T>
class AssetManager {
protected:
	std::map<std::string, T> data;

public:
	bool Load(const std::string&);
	bool Has(const std::string&) const;
	const T& GetOrLoad(const std::string&);
	const T& Get(const std::string&) const;
};

#include "AssetManager.inl"

#endif
