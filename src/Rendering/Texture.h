#pragma once

struct texture {
    unsigned int renderer_id;
    const uint8_t* buffer;
    size_t width;
    size_t height;
};

void texture_init(texture* tex, size_t width, size_t height, uint8_t* buffer);
void texture_delete(texture* tex);
void texture_bind(texture* tex, unsigned int slot);
void texture_unbind(texture* tex);
void texture_synchronize(texture* tex);
void texture_update_data(texture* tex, int width, int height, const unsigned char* data);
void texture_update_subdata(texture* tex, const unsigned char* data, int width, int height, int offsetX, int offsetY);
