#pragma once

#include "private/impl/detail/impl_base.hpp"

#define DECLARE_IMPL_CLASS(name, handle_type)  \
    class name : public impl_base<handle_type> \
    {                                          \
    public:                                    \
        name();                                \
                                               \
        name(handle_type handle)

#define DECLARE_IMPL_CONSTRUCTOR(name, handle_type) \
    name::name(handle_type handle)                  \
    : base{std::move(handle)}
