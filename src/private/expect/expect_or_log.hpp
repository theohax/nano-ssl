#pragma once

#include "private/expect/detail/expect_impl.hpp"

namespace nanossl::prv
{

DECLARE_EXPECTATION_FAILED_FUNCTION(log_after_expectation_failed);

}

#define EXPECT_OR_LOG(expression) DECLARE_EXPECT_MACRO(log_after_expectation_failed, expression);
