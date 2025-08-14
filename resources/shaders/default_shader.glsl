// This is an example shader to plan the making/loading process

#Vertex Shader
#version 430 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;
out vec2 v_TexCoord;

void main() {
    v_Position = a_Position;
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;

    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#Fragment Shader
#version 430 core

layout(location = 0) out vec4 FragColor;

uniform sampler2D u_Texture;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}
