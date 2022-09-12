#pragma once

#include <utility>

namespace nanossl::prv
{

template <class handle_t>
class impl_base
{
public:
    impl_base();

    explicit impl_base(handle_t handle);

    void make_handle();

    handle_t& get_handle();

    const handle_t& get_handle() const;

protected:
    using base = impl_base<handle_t>;

private:
    handle_t m_handle;
};

template <class handle_t>
impl_base<handle_t>::impl_base()
: m_handle{}
{

}

template <class handle_t>
impl_base<handle_t>::impl_base(handle_t handle)
: m_handle{std::move(handle)}
{

}

template <class handle_t>
void impl_base<handle_t>::make_handle()
{
    m_handle = handle_t::make();
}

template <class handle_t>
handle_t& impl_base<handle_t>::get_handle()
{
    return m_handle;
}

template <class handle_t>
const handle_t& impl_base<handle_t>::get_handle() const
{
    return const_cast<base*>(this)->get_handle();
}

}
