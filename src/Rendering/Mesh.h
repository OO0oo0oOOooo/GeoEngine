#pragma once

#include "RenderCommand.h"

struct mesh {
    uint32_t vertex_buffer;
    uint32_t index_buffer;

    uint32_t vertex_count;
    uint32_t index_count;

    const uint8_t* vertex_data;
    const uint8_t* index_data;
    uint32_t vertex_size;
    uint32_t index_size;
};

void mesh_create_static(mesh* mesh, const uint8_t* vdata, uint32_t vsize, const uint8_t* idata, uint32_t isize, uint32_t icount);
void mesh_upload_to_gpu(mesh* mesh);
render_command mesh_create_render_command(const mesh* mesh, const render_command& layout);
render_command mesh_create_render_command(const mesh* mesh);
void mesh_delete(mesh* mesh);
