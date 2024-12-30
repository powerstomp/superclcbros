#ifndef _SERVICELOCATOR_H
#define _SERVICELOCATOR_H

#include <memory>

template <typename T>
class ServiceLocator {
private:
	// Inline static means a copy for every translation unit
	// Every different T is a different translation unit
	inline static std::unique_ptr<T> service{};

	static T* GetPointer();

public:
	// Static use only.
	ServiceLocator() = delete;

	static T& Get();
	static void Set(std::unique_ptr<T>);
	static std::unique_ptr<T> Take();
};

#include "ServiceLocator.inl"

#endif
