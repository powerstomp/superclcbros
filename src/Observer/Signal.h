#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <vector>

#include "Slot.h"

template <typename... Args>
class Signal {
private:
	std::vector<Slot<Args...>> slots;

public:
	void Connect(const Slot<Args...>& slot);
	void Emit(Args... args) const;
};

#include "Signal.cpp"
#endif	// SIGNAL_H
