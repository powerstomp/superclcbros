#ifndef _STATESTART_H
#define _STATESTART_H

#include "StateMenu.h"

class StateStart : public StateMenu {
public:
    StateStart(Game* game);

    virtual void OnEnter() override;
    virtual void Update() override;
    virtual void Render(double deltaTime) override;
    virtual void OnSFMLEvent(const sf::Event& event) override;
};

#endif