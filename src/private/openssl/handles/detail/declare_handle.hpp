#pragma once

#include "private/openssl/handles/detail/handle.hpp"
#include "private/openssl/handles/detail/handle_view.hpp"

#define DECLARE_OPENSSL_HANDLE(                                                  \
    name,                                                                        \
    data_type,                                                                   \
    create_function,                                                             \
    increase_references_function,                                                \
    decrease_references_function)                                                \
        namespace nanossl::prv                                                   \
        {                                                                        \
	    using name##_handle = nanossl::prv::openssl_handle<                      \
            data_type,                                                           \
            create_function,                                                     \
            increase_references_function,                                        \
            decrease_references_function>;                                       \
	    using name##_handle_view = nanossl::prv::openssl_handle_view<data_type>; \
        }
