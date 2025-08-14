#pragma once

struct shader {
    unsigned int program_id;
};

void shader_init(shader* shader, const char* fileName);
void shader_delete(shader* shader);
void shader_bind(shader* shader);
void shader_unbind(shader* shader);
void shader_set_uniform_1f(shader* shader, const char* name, float value);
void shader_set_uniform_2f(shader* shader, const char* name, glm::vec2 value);
void shader_set_uniform_3f(shader* shader, const char* name, glm::vec3 value);
void shader_set_uniform_4f(shader* shader, const char* name, glm::vec4 value);
void shader_set_uniform_1i(shader* shader, const char* name, int value);
void shader_set_uniform_2i(shader* shader, const char* name, glm::ivec2 value);
void shader_set_uniform_3i(shader* shader, const char* name, glm::ivec3 value);
void shader_set_uniform_4i(shader* shader, const char* name, glm::ivec4 value);
void shader_set_uniform_mat_2f(shader* shader, const char* name, const glm::mat2& matrix);
void shader_set_uniform_mat_3f(shader* shader, const char* name, const glm::mat3& matrix);
void shader_set_uniform_mat_4f(shader* shader, const char* name, const glm::mat4& matrix);

std::pair<std::string, std::string> shader_read_file(std::string filePath);
