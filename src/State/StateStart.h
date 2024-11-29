#ifndef _STATESTART_H
#define _STATESTART_H

#include "StateMenu.h"

class StateStart : public StateMenu {
public:
    StateStart(Game* game);

    void OnEnter() override;
};

#endif