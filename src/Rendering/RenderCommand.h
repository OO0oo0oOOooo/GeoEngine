#pragma once

struct vertex_attribute {
    uint32_t location;         // Shader attribute location (0=position, 1=color, 2=uv)
    uint32_t component_count;  // 3 for vec3, 4 for vec4, 2 for vec2
    uint32_t type;             // GL_FLOAT, GL_INT, etc.
    bool normalized;           // GL_TRUE/GL_FALSE for normalization
    uint32_t offset;           // Byte offset within vertex struct
};

struct vertex_layout {
    vertex_attribute attributes[8];  // Support up to 8 vertex attributes
    uint32_t attribute_count;       // How many attributes are actually used
    uint32_t stride;                // Total size of one vertex in bytes
};

struct render_command {
    uint32_t vertex_buffer;    // OpenGL VBO handle
    uint32_t index_buffer;     // OpenGL EBO handle
    uint32_t vertex_offset;  // Byte offset into vertex buffer
    uint32_t index_offset;   // Element offset into index buffer
    uint32_t index_count;    // Number of indices to draw
    vertex_layout layout;     // How to interpret vertex data
};
