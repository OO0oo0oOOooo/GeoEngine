#include "Texture.h"

#include <cstring>

#include <stb_image/stb_image.h>

void texture_init(texture* tex, size_t width, size_t height, uint8_t* buffer) {
    unsigned int id = 0;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    tex->renderer_id = id;
    tex->buffer = buffer;
    tex->width = width;
    tex->height = height;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_delete(texture* tex) {
    glDeleteTextures(1, &tex->renderer_id);
}

void texture_bind(texture* tex, unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, tex->renderer_id);
}

void texture_unbind(texture* tex) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Using UpdateSubData doesnt adjust the local buffer(m_PixelBuffer) so use this to set
// m_PixelBuffer to whats on the GPU.
void texture_synchronize(texture* tex) {
    glBindTexture(GL_TEXTURE_2D, tex->renderer_id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)tex->buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_update_data(texture* tex, int width, int height, const unsigned char* data) {
    tex->width = width;
    tex->height = height;

    size_t size = width * height * 4;
    memcpy((void*)tex->buffer, data, size);

    glBindTexture(GL_TEXTURE_2D, tex->renderer_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void texture_update_subdata(texture* tex, const unsigned char* data, int width, int height,
                              int offsetX, int offsetY) {
    glBindTexture(GL_TEXTURE_2D, tex->renderer_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
                    data);
}
