#include "commands.hpp"
#include "functions.hpp"

namespace engine::gl
{
    void Commands::clear(const float red, const float green, const float blue, const float alpha)
    {
        glClearColor(red, green, blue, alpha);
    }

    void Commands::clear(const uint32_t flags)
    {
        glClear(flags);
    }
}