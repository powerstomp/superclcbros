#ifndef _SUBJECT_H
#define _SUBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

class Subject {
private:
	std::vector<std::shared_ptr<Observer>> observers;

public:
	void AddObserver(std::shared_ptr<Observer> observer);
	void RemoveObserver(std::shared_ptr<Observer> observer);
	void Notify(int data);
};
#endif