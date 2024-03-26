#include "GenericEvent.h"
#include "../Structures/Vector2.h"
#include "../ScreenObjects/Brick.h"

template<typename... Args>
typename GenericEvent<Args...>::CallbackID GenericEvent<Args...>::Subscribe(const EventCallback& callback) {
    CallbackID id = _nextID++;
    _callbacks.push_back(callback);
    _callbackIDs.push_back(id);
    return id;
}

template<typename... Args>
void GenericEvent<Args...>::Unsubscribe(CallbackID id) {
    auto it = std::find(_callbackIDs.begin(), _callbackIDs.end(), id);
    if (it != _callbackIDs.end()) {
        size_t index = std::distance(_callbackIDs.begin(), it);
        _callbacks.erase(_callbacks.begin() + index);
        _callbackIDs.erase(it);
    }
}
template<typename... Args>
void GenericEvent<Args...>::UnsubscribeAll() {
    _callbacks.clear();
    _callbackIDs.clear();
}
template<typename... Args>
void GenericEvent<Args...>::Invoke(Args... args) {
    for (const auto& callback : _callbacks) {
        callback(args...);
    }
}
//список темплейтов
template class GenericEvent<>;
template class GenericEvent<int>;
template class GenericEvent<Vector2>;
template class GenericEvent<Figure*>;