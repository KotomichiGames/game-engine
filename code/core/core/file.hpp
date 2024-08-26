#pragma once

namespace engine::core
{
    class File
    {
    public:
        static std::vector<char> read(const std::string& file);

        File() = delete;
    };
}