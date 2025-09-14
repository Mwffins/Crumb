#pragma once

namespace Crumb
{
    namespace ShaderSources
    {

        constexpr const char *SpriteVertexShader = R"(
            #version 330 core
            layout (location = 0) in vec2 aPosition;
            layout (location = 1) in vec2 aTexCoords;
            layout (location = 2) in float aTexIndex;

            out vec2 TexCoords;
            out float TexIndex;

            uniform mat4 uProjection;

            void main() {
                TexCoords = aTexCoords;
                TexIndex = aTexIndex;
                gl_Position = uProjection * vec4(aPosition, 0.0, 1.0);
            }
            )";

        constexpr const char *SpriteFragmentShader = R"(
            #version 330 core
            out vec4 FragColor;

            in vec2 TexCoords;
            in float TexIndex;

            uniform sampler2D uTextures[32];

            void main() {
                int index = int(TexIndex);
                FragColor = texture(uTextures[index], TexCoords);
            }
            )";

    }
}