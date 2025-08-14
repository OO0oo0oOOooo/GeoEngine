#include "Renderer.h"

#include "Vertex.h"

Renderer::Renderer(GLFWwindow* window) : m_Window(window) {
    glGenVertexArrays(1, &m_DummyVAO);
    glBindVertexArray(m_DummyVAO);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &m_DummyVAO);
}

void Renderer::RenderMesh(const render_command& cmd) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, cmd.vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cmd.index_buffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)28);
    glEnableVertexAttribArray(2);

    // for (uint32_t i = 0; i < cmd.layout.attribute_count; i++) {
    //     const auto& attr = cmd.layout.attributes[i];
    //     glVertexAttribPointer(attr.location, attr.component_count, attr.type, attr.normalized,
    //                           cmd.layout.stride, (void*)attr.offset);
    //     glEnableVertexAttribArray(attr.location);
    // }

    glDrawElements(GL_TRIANGLES, cmd.index_count, GL_UNSIGNED_INT,
                   (void*)(cmd.index_offset * sizeof(uint32_t)));
}

vertex_layout Renderer::CreateStandardLayout() {
    vertex_layout layout = {};
    layout.stride = 36 * sizeof(uint8_t);
    layout.attribute_count = 3;

    layout.attributes[0] = {0, 3, GL_FLOAT, false, 0};
    layout.attributes[1] = {1, 4, GL_FLOAT, false, 12};
    layout.attributes[2] = {2, 2, GL_FLOAT, false, 28};

    return layout;
}
