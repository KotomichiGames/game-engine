#include "commands.hpp"
#include "functions.hpp"
#include "macros.hpp"

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

    void Commands::draw_arrays(const uint32_t primitive, const int32_t count)
    {
        glDrawArrays(primitive, 0, count);
    }

    void Commands::draw_elements(const uint32_t primitive, const int32_t count)
    {
        glDrawElements(primitive, count, unsigned_int, nullptr);
    }
}