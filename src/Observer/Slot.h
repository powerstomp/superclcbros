#ifndef SLOT_H
#define SLOT_H

#include <functional>

template <typename... Args>
using Slot = std::function<void(Args...)>;

#endif	// SLOT_H