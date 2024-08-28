#pragma once

namespace engine::core
{
    class File
    {
    public:
        static std::vector<char> read(const std::string& file, int32_t read_mode = 0);

        File() = delete;
    };
}