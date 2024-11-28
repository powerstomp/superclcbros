#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <functional>
#include <vector>

template <typename... Args>
using Slot = std::function<void(Args...)>;

template <typename... Args>
class Signal {
private:
	std::vector<Slot<Args...>> slots;

public:
	void Connect(const Slot<Args...>& slot);
	void Emit(Args... args) const;
};

#include "Signal.inl"
#endif	// _SIGNAL_H
