#pragma once

#include "private/expect/expect_or_log.hpp"
#include "private/openssl/detail/openssl_expect_impl.hpp"

#define OPENSSL_EXPECT_OR_LOG(expression) OPENSSL_EXPECT_IMPL(log_after_expectation_failed, expression);
