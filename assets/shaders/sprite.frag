#version 330 core

in vec2 v_texCoords;
in float v_textureSlot;

uniform sampler2D u_textures[32];

out vec4 color;

void main() {
    int index = int(v_textureSlot);
    color = texture(u_textures[index], v_texCoords);
}