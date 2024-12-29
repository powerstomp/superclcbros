#ifndef _STATESELECTSTAGE_H
#define _STATESELECTSTAGE_H

#include "StateMenu.h"

class StateSelectStage : public StateMenu {
private:
	void AddStage(const std::string name, const std::string& mapPath);

public:
	StateSelectStage(Game* game);
};

#endif
