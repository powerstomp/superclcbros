#include <stdexcept>

#include "ServiceLocator.h"

template <typename T>
T& ServiceLocator<T>::Get() {
	return *GetPointer();
}
template <typename T>
T* ServiceLocator<T>::GetPointer() {
	if (!service)
		throw std::runtime_error(
			std::string("Service not provided: ") + typeid(T).name()
		);
	return service.get();
}

template <typename T>
void ServiceLocator<T>::Set(std::unique_ptr<T> newService) {
	service = std::move(newService);
}
template <typename T>
std::unique_ptr<T> ServiceLocator<T>::Take() {
	return std::move(service);
}
