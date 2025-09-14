#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in float a_textureSlot;

uniform mat4 u_projection;

out vec2 v_texCoords;
out float v_textureSlot;

void main() {
    v_texCoords = a_texCoords;
    v_textureSlot = a_textureSlot;
    gl_Position = u_projection * vec4(a_position, 0.0, 1.0);
}