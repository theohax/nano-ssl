#pragma once

#include <chrono>

namespace nanossl
{

class time_interval
{
public:
    using point = std::chrono::time_point<std::chrono::system_clock>;

    time_interval(point from, point to);

    void set_from(point from);

    const point& get_from() const;

    void set_to(point to);

    const point& get_to() const;

private:
    point m_from;
    point m_to;
};

}
