#pragma once

#include "private/expect/detail/expect_impl.hpp"

namespace nanossl::prv
{

DECLARE_EXPECTATION_FAILED_FUNCTION(throw_after_expectation_failed);

}

#define EXPECT_OR_THROW(expression) \
    DECLARE_EXPECT_MACRO(throw_after_expectation_failed, expression);
