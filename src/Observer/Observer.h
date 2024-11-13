#ifndef _OBSERVER_H
#define _OBSERVER_H

class Observer {
public:
    virtual void OnNotify(int data) = 0; 
};

#endif