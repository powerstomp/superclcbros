#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <map>
#include <string>

#include "../../Utility/NonCopyable.h"
#include "Animation.h"

class AnimationManager : public NonCopyable {
private:
	std::map<std::string, Animation> animations;

public:
	bool Load(const std::string&);

	Animation Get(const std::string&) const;
};

#endif
