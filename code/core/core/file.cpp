#include "file.hpp"

namespace engine::core
{
    std::vector<char> File::read(const std::string& file)
    {
        std::ifstream stream(file, std::ios::ate);
        assert(stream.is_open());

        const auto size = stream.tellg();
        assert(size > 0);

        std::vector<char> content(size);

        stream.seekg(0, std::ios::beg);
        stream.read(content.data(), size);

        return content;
    }
}