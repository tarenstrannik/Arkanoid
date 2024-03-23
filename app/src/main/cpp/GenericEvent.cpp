#include "GenericEvent.h"

template<typename... Args>
void GenericEvent<Args...>::Subscribe(const EventCallback& callback) {
    _callbacks.push_back(callback);
}

template<typename... Args>
void GenericEvent<Args...>::Unsubscribe(const EventCallback& callback) {
    _callbacks.remove_if([&callback](const EventCallback& storedCallback) {
        return &callback == &storedCallback;
    });
}

template<typename... Args>
void GenericEvent<Args...>::Invoke(Args... args) {
    for (const auto& callback : _callbacks) {
        callback(args...);
    }
}
//список темплейтов
template class GenericEvent<>;