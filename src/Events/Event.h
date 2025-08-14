#pragma once

#include <functional>

template <typename... Args>
class Event {
   public:
    void NotifyHandlers(Args... args) {
        for (const auto& handler : Handlers) {
            handler(args...);
        }
    }

    void AddHandler(const std::function<void(Args...)>& handler) {
        Handlers.push_back(handler);
    }

    void RemoveHandler(const std::function<void(Args...)>& handler) {
        Handlers.erase(std::remove(Handlers.begin(), Handlers.end(), handler), Handlers.end());
    }

    void operator()(Args... args) {
        NotifyHandlers(args...);
    }

    Event& operator+=(const std::function<void(Args...)>& handler) {
        AddHandler(handler);
        return *this;
    }

    Event& operator-=(const std::function<void(Args...)>& handler) {
        RemoveHandler(handler);
        return *this;
    }

   private:
    std::vector<std::function<void(Args...)>> Handlers;
};

// void NotifyHandlers();
// void AddHandler(const EventHandler& handler);
// void RemoveHandler(const EventHandler& handler);
