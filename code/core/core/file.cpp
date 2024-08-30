#include "file.hpp"

namespace engine::core
{
    std::vector<char> File::read(const std::string& file, const int32_t read_mode)
    {
        std::ifstream stream(file, std::ios::ate | read_mode);
        assert(stream.is_open());

        const auto size = stream.tellg();
        assert(size > 0);

        std::vector<char> content(size);

        stream.seekg(0, std::ios::beg);
        stream.read(content.data(), size);

        return content;
    }
}