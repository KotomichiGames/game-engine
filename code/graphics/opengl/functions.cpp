#include "functions.hpp"

namespace engine::gl
{
    void Functions::load()
    {
        if (gladLoadGL() == 0)
        {
            std::exit(EXIT_FAILURE);
        }
    }
}