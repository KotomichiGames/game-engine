#pragma once

namespace engine::core
{
    using time_clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::high_resolution_clock::time_point;

    class Time
    {
    public:
        void init();
        void update();

        static float total_time();
        static float delta_time();

    private:
        static float calculate_duration(const time_point& start, const time_point& end);

        inline static float _delta_time { };
        inline static float _total_time { };

        time_point _previous_time { };
        time_point    _start_time { };
    };
}