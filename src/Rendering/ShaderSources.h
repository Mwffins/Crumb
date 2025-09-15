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
            flat out int TexIndex;

            uniform mat4 uProjection;

            void main() {
                TexCoords = aTexCoords;
                TexIndex = int(aTexIndex);
                gl_Position = uProjection * vec4(aPosition, 0.0, 1.0);
            }
            )";

        constexpr const char *SpriteFragmentShader = R"(
            #version 330 core
            out vec4 FragColor;

            in vec2 TexCoords;
            flat in int TexIndex;

            uniform sampler2D uTextures[32];

            void main() {
                if (TexIndex == 0) FragColor = texture(uTextures[0], TexCoords);
                else if (TexIndex == 1) FragColor = texture(uTextures[1], TexCoords);
                else if (TexIndex == 2) FragColor = texture(uTextures[2], TexCoords);
                else if (TexIndex == 3) FragColor = texture(uTextures[3], TexCoords);
                else if (TexIndex == 4) FragColor = texture(uTextures[4], TexCoords);
                else if (TexIndex == 5) FragColor = texture(uTextures[5], TexCoords);
                else if (TexIndex == 6) FragColor = texture(uTextures[6], TexCoords);
                else if (TexIndex == 7) FragColor = texture(uTextures[7], TexCoords);
                else if (TexIndex == 8) FragColor = texture(uTextures[8], TexCoords);
                else if (TexIndex == 9) FragColor = texture(uTextures[9], TexCoords);
                else if (TexIndex == 10) FragColor = texture(uTextures[10], TexCoords);
                else if (TexIndex == 11) FragColor = texture(uTextures[11], TexCoords);
                else if (TexIndex == 12) FragColor = texture(uTextures[12], TexCoords);
                else if (TexIndex == 13) FragColor = texture(uTextures[13], TexCoords);
                else if (TexIndex == 14) FragColor = texture(uTextures[14], TexCoords);
                else if (TexIndex == 15) FragColor = texture(uTextures[15], TexCoords);
                else if (TexIndex == 16) FragColor = texture(uTextures[16], TexCoords);
                else if (TexIndex == 17) FragColor = texture(uTextures[17], TexCoords);
                else if (TexIndex == 18) FragColor = texture(uTextures[18], TexCoords);
                else if (TexIndex == 19) FragColor = texture(uTextures[19], TexCoords);
                else if (TexIndex == 20) FragColor = texture(uTextures[20], TexCoords);
                else if (TexIndex == 21) FragColor = texture(uTextures[21], TexCoords);
                else if (TexIndex == 22) FragColor = texture(uTextures[22], TexCoords);
                else if (TexIndex == 23) FragColor = texture(uTextures[23], TexCoords);
                else if (TexIndex == 24) FragColor = texture(uTextures[24], TexCoords);
                else if (TexIndex == 25) FragColor = texture(uTextures[25], TexCoords);
                else if (TexIndex == 26) FragColor = texture(uTextures[26], TexCoords);
                else if (TexIndex == 27) FragColor = texture(uTextures[27], TexCoords);
                else if (TexIndex == 28) FragColor = texture(uTextures[28], TexCoords);
                else if (TexIndex == 29) FragColor = texture(uTextures[29], TexCoords);
                else if (TexIndex == 30) FragColor = texture(uTextures[30], TexCoords);
                else if (TexIndex == 31) FragColor = texture(uTextures[31], TexCoords);
                else FragColor = texture(uTextures[0], TexCoords);
            }
            )";

    }
}