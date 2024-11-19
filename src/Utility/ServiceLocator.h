#ifndef _SERVICELOCATOR_H
#define _SERVICELOCATOR_H

#include <memory>
#include <stdexcept>

template <typename T>
class ServiceLocator {
private:
	inline static std::unique_ptr<T> service{};

public:
	static T& Get() {
		if (!service)
			throw std::runtime_error(
				std::string("Service not provided: ") + typeid(T).name()
			);
		return *service;
	}
	static void Set(std::unique_ptr<T> newService) {
		service = std::move(newService);
	}
};

#endif
