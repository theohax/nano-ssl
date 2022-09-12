#include "private/expect/expect_or_log.hpp"
#include "private/expect/expect_or_throw.hpp"
#include "private/expect/detail/expect_info.hpp"
#include "test/utils/expected_failure_message.hpp"
#include "test/utils/std_output_redirect.hpp"

#include <gtest/gtest.h>

#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>

namespace
{
    nanossl::prv::expect_info construct_expect_info(const std::size_t line_number)
    {
        return nanossl::prv::expect_info{
                "1 == 2",
                "nano-ssl/test/unit/expect_tests.cpp",
                line_number,
                std::nullopt
        };
    }
}

TEST(expect_tests, expect_or_log)
{
    nanossl::test::std_output_redirect redirect{std::cout};

    EXPECT_OR_LOG(true);
    EXPECT_FALSE(redirect.has_any_content());

    EXPECT_OR_LOG(1 == 2);

    const auto output = redirect.get_stream_content();
    const auto parts = nanossl::test::construct_expected_failure_message_parts(construct_expect_info(34));
    for (const auto& part : parts)
    {
        EXPECT_NE(std::string::npos, output.find(part));
    }
}

TEST(expect_tests, expect_or_throw)
{
    nanossl::test::std_output_redirect redirect{std::cout};

    EXPECT_NO_THROW(EXPECT_OR_THROW(true));
    EXPECT_FALSE(redirect.has_any_content());

    EXPECT_THROW(EXPECT_OR_THROW(false), std::runtime_error);
    EXPECT_FALSE(redirect.has_any_content());

    try
    {
        EXPECT_OR_THROW(1 == 2);
        FAIL();
    }
    catch (const std::exception& ex)
    {
        const std::string output{ex.what()};
        const auto parts = nanossl::test::construct_expected_failure_message_parts(construct_expect_info(56));
        for (const auto& part : parts)
        {
            EXPECT_NE(std::string::npos, output.find(part));
        }
    }

    EXPECT_FALSE(redirect.has_any_content());
}
