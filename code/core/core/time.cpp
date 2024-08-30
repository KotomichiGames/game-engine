#include "time.hpp"

namespace engine::core
{
    void Time::init()
    {
        _previous_time = _start_time = time_clock::now();
    }

    void Time::update()
    {
         const auto current_time = time_clock::now();

        _total_time    = calculate_duration(_start_time,        current_time);
        _delta_time    = calculate_duration(_previous_time, current_time);
        _previous_time = current_time;
    }

    float Time::total_time()
    {
        return _total_time;
    }

    float Time::delta_time()
    {
        return _delta_time;
    }

    float Time::calculate_duration(const time_point& start, const time_point& end)
    {
        return std::chrono::duration<float>(end - start).count();
    }
}