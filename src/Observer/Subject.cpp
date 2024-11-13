#include "Subject.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

void Subject::AddObserver(std::shared_ptr<Observer> observer) {
	observers.push_back(observer);
}

void Subject::RemoveObserver(std::shared_ptr<Observer> observer) {
	auto it = std::find(observers.begin(), observers.end(), observer);
	if (it != observers.end()) {
		observers.erase(it);
	}
}

void Subject::Notify(int data) {
	for (const auto& observer : observers) {
		observer->OnNotify(data);
	}
}
