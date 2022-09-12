#pragma once

#include "private/expect/detail/expect_info.hpp"

#include <string>
#include <type_traits>

namespace nanossl::prv
{

std::string construct_failure_message(const expect_info& info);

template <typename result_t>
bool is_expectation_met(result_t result)
{
    if constexpr (std::is_pointer_v<result_t>)
    {
        return result;
    }
    else
    {
        return 1 == result;
    }
}

#define DECLARE_EXPECTATION_FAILED_FUNCTION(name) \
    void name (const expect_info& info)

}

#define DECLARE_EXPECT_MACRO_IMPL(function, expression, message) \
    if (!nanossl::prv::is_expectation_met(expression))           \
        {                                                        \
            nanossl::prv::function(                              \
                nanossl::prv::expect_info{                       \
                    #expression,                                 \
                    __FILE__,                                    \
                    __LINE__,                                    \
                    message});                                   \
        }

#define DECLARE_EXPECT_MACRO(function, expression) \
    DECLARE_EXPECT_MACRO_IMPL(function, expression, std::nullopt);

#define DECLARE_EXPECT_WITH_MESSAGE_MACRO(function, expression, message) \
    DECLARE_EXPECT_MACRO_IMPL(function, expression, message);
