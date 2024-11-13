#ifndef _SERVICELOCATOR_H
#define _SERVICELOCATOR_H

#include <memory>

template <typename T>
class ServiceLocator {
private:
	inline static std::unique_ptr<T> service{};

public:
	static T& Get() {
		return *service;
	}
	static void Set(std::unique_ptr<T> newService) {
		service = std::move(newService);
	}
};

#endif
