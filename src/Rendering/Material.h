#pragma once

#include "ResourceHandle.h"

struct material {
    resource_handle shader_handle;
    resource_handle texture_handle;
};

void material_init(material* mat, resource_handle shader, resource_handle texture);
void material_bind(material* mat, glm::mat4 vpMatrix, glm::mat4 modelMatrix);
void material_unbind(material* mat);
