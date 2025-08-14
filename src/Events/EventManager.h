#pragma once

#include "Event.h"

class EventManager {
   public:
    EventManager(const EventManager&) = delete;
    EventManager() = default;

    static EventManager& GetInstance() {
        static EventManager instance;
        return instance;
    }

    Event<int, int> WindowResizeEvent;
    Event<> WindowCloseEvent;

    Event<double, double> MouseMoveEvent;
    Event<double, double> MouseScrollEvent;

    Event<int, int, int> MouseButtonEvent;  // button: 0 = left, 1 = right | action: 1 = down, 0 =
                                            // up, 2 = repeat | mods: modifier keys
    Event<int> MouseButtonDownEvent;
    Event<int> MouseButtonUpEvent;
    Event<int> MouseButtonRepeatEvent;

    Event<int, int, int, int> KeyEvent;  // key: key code | scancode: key code | action: 1 = down, 0
                                         // = up, 2 = repeat | mods: modifier keys
    Event<int> KeyDownEvent;
    Event<int> KeyUpEvent;
    Event<int> KeyRepeatEvent;

    Event<> UpdateWorldEvent;
    Event<int, int> UpdateChunkEvent;

    Event<int, int> EditElementAtWorldPosition;  // TODO: Refactor painting and remove this
};
