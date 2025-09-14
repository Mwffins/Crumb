#pragma once
#include <string>
#include <unordered_map>

namespace Crumb
{

    class AssetManager
    {
    public:
        static AssetManager &get();

        unsigned int loadTexture(const std::string &name, const std::string &path);
        unsigned int getTexture(const std::string &name) const;

    private:
        AssetManager() = default;
        std::unordered_map<std::string, unsigned int> m_textures;
    };
}