#include "Broadcast.h"
#include "BroadcastImpl.h"

namespace {
// TODO: this and resourcemanagaer g_vars need to be excluded from unity build or something idekanymore
std::unordered_map<int, std::vector<event_handler>> g_system_listeners;
}

void broadcast_impl_listen(int event_type, void (*callback)(void*, void*), void* context) {
    g_system_listeners[event_type].push_back({callback, context});
}

void broadcast_impl_send(int event_type, void* data) {
    for (auto& handler : g_system_listeners[event_type]) {
        handler.callback(handler.context, data);
    }
}

namespace SystemEvents {
void listen(int event_type, void (*callback)(void*, void*), void* context) {
    broadcast_impl_listen(event_type, callback, context);
}

void broadcast(int event_type, void* data) {
    broadcast_impl_send(event_type, data);
}
}
