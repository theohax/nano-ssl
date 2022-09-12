#pragma once

#include "private/expect/expect_or_throw.hpp"
#include "private/openssl/detail/openssl_expect_impl.hpp"

#define OPENSSL_EXPECT_OR_THROW(expression) OPENSSL_EXPECT_IMPL(throw_after_expectation_failed, expression);
