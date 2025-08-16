#pragma once

namespace SystemEvents {
    void broadcast(int event_type, void* data);
    void listen(int event_type, void (*callback)(void*, void*), void* context);
}
