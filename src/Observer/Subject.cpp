#include "Subject.h"
#include <algorithm>
#include <vector>
#include "Observer.h"

void Subject::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
	observers.erase(
		std::remove(observers.begin(), observers.end(), observer), observers.end()
	);
}

void Subject::notify(int data) {
	for (Observer* observer : observers) {
		observer->onNotify(data);
	}
}