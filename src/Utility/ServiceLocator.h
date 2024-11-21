#ifndef _SERVICELOCATOR_H
#define _SERVICELOCATOR_H

#include <memory>

template <typename T>
class ServiceLocator {
private:
	inline static std::unique_ptr<T> service{};

public:
	static T& Get();
	static void Set(std::unique_ptr<T>);
	static std::unique_ptr<T> Take();
};

#include "ServiceLocator.inl"

#endif
