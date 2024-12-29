#include "Signal.h"

// Connect a new slot (observer) to the signal
template <typename... Args>
void Signal<Args...>::Connect(const Slot<Args...>& slot) {
	slots.push_back(slot);
}

// Emit the signal, invoking all connected slots with the provided arguments
template <typename... Args>
void Signal<Args...>::Emit(Args... args) const {
	for (const auto& slot : slots) {
		slot(args...);
	}
}

template <typename... Args>
void Signal<Args...>::Reset() {
	slots.clear();
}
