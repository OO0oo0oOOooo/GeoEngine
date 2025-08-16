#pragma once

struct event_handler {
    void (*callback)(void* context, void* data);
    void* context;
};

void broadcast_impl_listen(int event_type, void (*callback)(void*, void*), void* context);
void broadcast_impl_send(int event_type, void* data);
