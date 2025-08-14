#include "Material.h"

#include "ResourceManager.h"
#include "ResourceHandle.h"
#include "Shader.h"
#include "Texture.h"

void material_init(material* mat, resource_handle shader, resource_handle texture) {
    mat->shader_handle = shader;
    mat->texture_handle = texture;
}

void material_bind(material* mat, glm::mat4 vpMatrix, glm::mat4 modelMatrix) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader* shader = ResourceManager::GetResourceManager()->GetShader(mat->shader_handle);
    texture* texture = ResourceManager::GetResourceManager()->GetTexture(mat->texture_handle);

    assert(shader);
    assert(texture);

    texture_bind(texture, 0);
    shader_bind(shader);
    shader_set_uniform_mat_4f(shader, "u_ViewProjection", vpMatrix);
    shader_set_uniform_mat_4f(shader, "u_Transform", modelMatrix);
    shader_set_uniform_1i(shader, "u_Texture", 0);
}

void material_unbind(material* mat) {
    shader* shader = ResourceManager::GetResourceManager()->GetShader(mat->shader_handle);
    shader_unbind(shader);
}
