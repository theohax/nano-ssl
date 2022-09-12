#include "time_interval.hpp"

#include <utility>

namespace nanossl
{

time_interval::time_interval(point from, point to)
: m_from{std::move(from)},
  m_to{std::move(to)}
{

}

void time_interval::set_from(point from)
{
    m_from = std::move(from);
}

const time_interval::point& time_interval::get_from() const
{
    return m_from;
}

void time_interval::set_to(point to)
{
    m_to = std::move(to);
}

const time_interval::point& time_interval::get_to() const
{
    return m_to;
}

}
