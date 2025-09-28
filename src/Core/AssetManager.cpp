#include "AssetManager.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace Crumb
{

    AssetManager &AssetManager::get()
    {
        static AssetManager instance;
        return instance;
    }

    unsigned int AssetManager::loadTexture(const std::string &name, const std::string &path)
    {
        if (m_textures.contains(name))
        {
            return m_textures[name];
        }

        int width, height, channels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data)
        {
            std::cerr << "Failed to load texture: " << path << std::endl;
            return 0;
        }

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                     channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);

        m_textures[name] = textureID;
        return textureID;
    }

    unsigned int AssetManager::getTexture(const std::string &name) const
    {
        auto it = m_textures.find(name);
        if (it != m_textures.end())
        {
            return it->second;
        }
        return 0;
    }

}