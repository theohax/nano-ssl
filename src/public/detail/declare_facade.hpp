#pragma once

#include <spimpl/spimpl.h>

#include <utility>

#define DECLARE_FACADE_TEMPLATE(name, type, make_impl_function)                 \
    template <class impl_t>                                                     \
    class name                                                                  \
    {                                                                           \
    public:                                                                     \
        template <class facade_t>                                               \
        static auto _detail_make_facade_from_impl(impl_t impl);                 \
                                                                                \
        template <typename... args_t>                                           \
        explicit name(args_t&&... args);                                        \
                                                                                \
        spimpl::type<impl_t>& get_impl();                                       \
                                                                                \
        const spimpl::type<impl_t>& get_impl() const;                           \
                                                                                \
    protected:                                                                  \
        using base = name<impl_t>;                                              \
                                                                                \
        explicit name(impl_t impl);                                             \
                                                                                \
    private:                                                                    \
        spimpl::type<impl_t> m_impl;                                            \
    };                                                                          \
                                                                                \
    template <class impl_t>                                                     \
    template <class facade_t>                                                   \
    auto name<impl_t>::_detail_make_facade_from_impl(impl_t impl)               \
    {                                                                           \
        return facade_t{std::move(impl)};                                       \
    }                                                                           \
                                                                                \
    template <class impl_t>                                                     \
    template <typename... args_t>                                               \
    name<impl_t>::name(args_t&&... args)                                        \
    : m_impl{spimpl::make_impl_function<impl_t>(std::forward<args_t>(args)...)} \
    {                                                                           \
                                                                                \
    }                                                                           \
                                                                                \
    template <class impl_t>                                                     \
    spimpl::type<impl_t>& name<impl_t>::get_impl()                              \
    {                                                                           \
        return m_impl;                                                          \
    }                                                                           \
                                                                                \
    template <class impl_t>                                                     \
    const spimpl::type<impl_t>& name<impl_t>::get_impl() const                  \
    {                                                                           \
        return const_cast<base*>(this)->get_impl();                             \
    }                                                                           \
                                                                                \
    template <class impl_t>                                                     \
    name<impl_t>::name(impl_t impl)                                             \
    : m_impl{spimpl::make_impl_function<impl_t>(std::move(impl))}               \
    {                                                                           \
                                                                                \
    }

#define DECLARE_FACADE_CLASS(name, type)               \
                                                       \
    namespace prv                                      \
    {                                                  \
                                                       \
    class name##_impl;                                 \
                                                       \
    }                                                  \
                                                       \
    class name : public detail::type<prv::name##_impl> \
    {                                                  \
    public:                                            \
        name();                                        \
                                                       \
    private:                                           \
        using base::base

#define DECLARE_UNIQUE_FACADE_TEMPLATE(name) DECLARE_FACADE_TEMPLATE(name, unique_impl_ptr, make_unique_impl);

#define DECLARE_SHARED_FACADE_TEMPLATE(name) DECLARE_FACADE_TEMPLATE(name, impl_ptr, make_impl);

#define DECLARE_UNIQUE_FACADE_CLASS(name) DECLARE_FACADE_CLASS(name, unique_facade)

#define DECLARE_SHARED_FACADE_CLASS(name) DECLARE_FACADE_CLASS(name, shared_facade)
