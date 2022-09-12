#pragma once

#include "private/expect/detail/expect_impl.hpp"
#include "private/openssl/error.hpp"

#define OPENSSL_EXPECT_IMPL(function, expression) DECLARE_EXPECT_WITH_MESSAGE_MACRO(                    \
    function,                                                                                           \
    expression,                                                                                         \
    []()                                                                                                \
    {                                                                                                   \
        return "OpenSSL error: `" + nanossl::prv::openssl_error::get_instance().retrieve_last() + "`."; \
    })
