#pragma once

namespace engine::base
{
    template <typename T> class Singleton
    {
    public:
        Singleton& operator=(const Singleton&) = delete;
        Singleton           (const Singleton&) = delete;

        static T& instance()
        {
            static T instance;
            return   instance;
        }

    protected:
        virtual ~Singleton() = default;
                 Singleton() = default;
    };
}