#include "Shader.h"

#include <fstream>
#include <sstream>

void shader_init(shader* shader, const char* fileName) {
    std::pair<std::string, std::string> str =
        shader_read_file(std::string(RESOURCES_PATH) + "shaders/" + fileName + ".glsl");

    const char* vertexShaderSource = str.first.c_str();
    const char* fragmentShaderSource = str.second.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int program_id = glCreateProgram();
    glAttachShader(program_id, vertexShader);
    glAttachShader(program_id, fragmentShader);
    glLinkProgram(program_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shader->program_id = program_id;
}

void shader_delete(shader* shader) {
    if (shader->program_id) glDeleteProgram(shader->program_id);
}

void shader_bind(shader* shader) {
    if (!shader->program_id) return;

    glUseProgram(shader->program_id);
}

void shader_unbind(shader* shader) {
    glUseProgram(0);
}

void shader_set_uniform_1f(shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->program_id, name), value);
}

void shader_set_uniform_2f(shader* shader, const char* name, glm::vec2 value) {
    glUniform2f(glGetUniformLocation(shader->program_id, name), value.x, value.y);
}

void shader_set_uniform_3f(shader* shader, const char* name, glm::vec3 value) {
    glUniform3f(glGetUniformLocation(shader->program_id, name), value.x, value.y, value.z);
}

void shader_set_uniform_4f(shader* shader, const char* name, glm::vec4 value) {
    glUniform4f(glGetUniformLocation(shader->program_id, name), value.x, value.y, value.z, value.w);
}

void shader_set_uniform_1i(shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->program_id, name), value);
}

void shader_set_uniform_2i(shader* shader, const char* name, glm::ivec2 value) {
    glUniform2i(glGetUniformLocation(shader->program_id, name), value.x, value.y);
}

void shader_set_uniform_3i(shader* shader, const char* name, glm::ivec3 value) {
    glUniform3i(glGetUniformLocation(shader->program_id, name), value.x, value.y, value.z);
}

void shader_set_uniform_4i(shader* shader, const char* name, glm::ivec4 value) {
    glUniform4i(glGetUniformLocation(shader->program_id, name), value.x, value.y, value.z, value.w);
}

void shader_set_uniform_mat_2f(shader* shader, const char* name, const glm::mat2& matrix) {
    glUniformMatrix2fv(glGetUniformLocation(shader->program_id, name), 1, GL_FALSE, &matrix[0][0]);
}

void shader_set_uniform_mat_3f(shader* shader, const char* name, const glm::mat3& matrix) {
    glUniformMatrix3fv(glGetUniformLocation(shader->program_id, name), 1, GL_FALSE, &matrix[0][0]);
}

void shader_set_uniform_mat_4f(shader* shader, const char* name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(shader->program_id, name), 1, GL_FALSE, &matrix[0][0]);
}

// TODO: this might not belong here but if it does it will need to be refactored
std::pair<std::string, std::string> shader_read_file(std::string filePath) {
    std::ifstream file(filePath);
    std::stringstream vertexShader, fragmentShader;
    std::string line;

    bool isVertexShader = false;
    bool isFragmentShader = false;

    if (!file.is_open()) std::cerr << "Error opening shader file: " << filePath << std::endl;

    while (std::getline(file, line)) {
        if (line == "#Vertex Shader") {
            isVertexShader = true;
            isFragmentShader = false;
            continue;
        } else if (line == "#Fragment Shader") {
            isVertexShader = false;
            isFragmentShader = true;
            continue;
        }

        if (isVertexShader) {
            vertexShader << line << "\n";
        } else if (isFragmentShader) {
            fragmentShader << line << "\n";
        }
    }

    file.close();
    return std::make_pair(vertexShader.str(), fragmentShader.str());
}
