#pragma once

#include "base/factory.hpp"

namespace engine::glfw
{
    class Factory final : public base::Factory
    {
    public:
        std::unique_ptr<base::Window>   create_window()   override;
        std::unique_ptr<base::Platform> create_platform() override;
        std::unique_ptr<base::Context>  create_context()  override;
    };
}