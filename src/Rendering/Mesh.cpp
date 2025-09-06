#include "Mesh.h"

#include "RenderCommand.h"
#include "Renderer.h"

void mesh_create_static(mesh* mesh, const uint8_t* vdata, uint32_t vsize, const uint8_t* idata, uint32_t isize, uint32_t icount) {
    mesh->vertex_buffer = 0;
    mesh->index_buffer = 0;
    mesh->vertex_count = vsize / 36;
    mesh->index_count = icount;
    mesh->vertex_data = vdata;
    mesh->index_data = idata;
    mesh->vertex_size = vsize;
    mesh->index_size = isize;
}

void mesh_upload_to_gpu(mesh* mesh) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertex_size, mesh->vertex_data, GL_STATIC_DRAW);
    mesh->vertex_buffer = vbo;

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_size, mesh->index_data, GL_STATIC_DRAW);
    mesh->index_buffer = ebo;
}

render_command mesh_create_render_command(const mesh* mesh, const vertex_layout& layout) {
    render_command cmd = {};
    cmd.vertex_buffer = mesh->vertex_buffer;
    cmd.index_buffer = mesh->index_buffer;
    cmd.vertex_offset = 0;
    cmd.index_offset = 0;
    cmd.index_count = mesh->index_count;
    cmd.layout = layout;
    return cmd;
}

render_command mesh_create_render_command(const mesh* mesh) {
    render_command cmd = {};
    cmd.vertex_buffer = mesh->vertex_buffer;
    cmd.index_buffer = mesh->index_buffer;
    cmd.vertex_offset = 0;
    cmd.index_offset = 0;
    cmd.index_count = mesh->index_count;
    cmd.layout = Renderer::CreateStandardLayout();
    return cmd;
}

void mesh_delete(mesh* mesh) {
    if (mesh->vertex_buffer != 0) {
        GLuint vbo = mesh->vertex_buffer;
        glDeleteBuffers(1, &vbo);
        mesh->vertex_buffer = 0;
    }

    if (mesh->index_buffer != 0) {
        GLuint ebo = mesh->index_buffer;
        glDeleteBuffers(1, &ebo);
        mesh->index_buffer = 0;
    }
}
