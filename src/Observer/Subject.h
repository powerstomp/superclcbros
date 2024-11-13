#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"
#include <vector>
#include <algorithm>

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify(int data);
};
#endif