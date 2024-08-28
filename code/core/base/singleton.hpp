#pragma once

namespace engine::base
{
    template <typename T> class Singleton
    {
    public:
        static T& instance()
        {
            static T instance;
            return   instance;
        }

        Singleton& operator=(const Singleton&) = delete;
        Singleton           (const Singleton&) = delete;

    protected:
        virtual ~Singleton() = default;
                 Singleton() = default;
    };
}