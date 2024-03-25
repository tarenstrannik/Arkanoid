#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

#include <functional>
#include <vector>

template<typename... Args>
class GenericEvent {
public:
    using EventCallback = std::function<void(Args...)>;
    using CallbackID = std::size_t;

    CallbackID Subscribe(const EventCallback& callback);
    void Unsubscribe(CallbackID id);
    void Invoke(Args... args);

private:
    std::vector<EventCallback> _callbacks;
    std::vector<CallbackID> _callbackIDs;
    CallbackID _nextID = 0;
};
#endif  // GENERIC_EVENT_H