#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void onNotify(int data) = 0; 
};

#endif