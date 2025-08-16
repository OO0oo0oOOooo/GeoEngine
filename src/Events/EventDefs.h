#pragma once

// System Event Placeholders
#define EVENT_WINDOW_CLOSE 0
#define EVENT_WINDOW_RESIZE 1

#define EVENT_MOUSE_MOVE 10
#define EVENT_MOUSE_SCROLL 11
#define EVENT_MOUSE_BUTTON 12
#define EVENT_MOUSE_BUTTON_UP 13
#define EVENT_MOUSE_BUTTON_DOWN 14
#define EVENT_MOUSE_BUTTON_REPEAT 15

#define EVENT_KEY_BUTTON 20
#define EVENT_KEY_BUTTON_UP 21
#define EVENT_KEY_BUTTON_DOWN 22
#define EVENT_KEY_BUTTON_REPEAT 23

// Game Event Placeholders
#define EVENT_EDIT_ELEMENT 100
#define EVENT_UPDATE_WORLD 101
#define EVENT_UPDATE_CHUNK 102

union edata4_u {
    uint8_t c[4];
    int32_t i[1];
    float f[1];
};

union edata8_u {
    uint8_t c[8];
    int32_t i[2];
    float f[2];
    double d[1];
};

union edata16_u {
    uint8_t c[16];
    int32_t i[4];
    float f[4];
    double d[2];
};

union edata32_u {
    uint8_t c[32];
    int32_t i[8];
    float f[8];
    double d[4];
};
