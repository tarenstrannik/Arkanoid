#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

#include <functional>
#include <list>

template<typename... Args>
class GenericEvent {
public:
    using EventCallback = std::function<void(Args...)>;

    void Subscribe(const EventCallback& callback);
    void Unsubscribe(const EventCallback& callback);
    void Invoke(Args... args);

private:
    std::list<EventCallback> _callbacks;
};

#endif  // GENERIC_EVENT_H