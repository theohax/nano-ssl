#include "private/expect/detail/expect_info.hpp"
#include "private/openssl/expect_or_log.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/ssl.hpp"
#include "private/openssl/handles/ssl_ctx.hpp"
#include "test/utils/expected_failure_message.hpp"
#include "test/utils/std_output_redirect.hpp"

#include <gtest/gtest.h>
#include <openssl/ssl.h>

#include <stdexcept>
#include <string>
#include <string_view>

namespace
{
    const nanossl::prv::ssl_ctx_handle ssl_ctx{nanossl::prv::ssl_ctx_handle::make(TLS_method())};
    const nanossl::prv::ssl_handle ssl{nanossl::prv::ssl_handle::make(*ssl_ctx)};

    nanossl::prv::expect_info construct_expect_info(const std::size_t line_number)
    {
        return nanossl::prv::expect_info{
                "SSL_do_handshake(*ssl)",
                "nano-ssl/test/unit/openssl_expect_tests.cpp",
                line_number,
                []()
                {
                    return "SSL_do_handshake:connection type not set:ssl/ssl_lib.c";
                }
        };
    }
}

TEST(openssl_expect_tests, expect_or_log)
{
    nanossl::test::std_output_redirect redirect{std::cout};

    OPENSSL_EXPECT_OR_LOG(true);
    EXPECT_FALSE(redirect.has_any_content());

    OPENSSL_EXPECT_OR_LOG(SSL_do_handshake(*ssl));

    const auto output = redirect.get_stream_content();
    const auto parts = nanossl::test::construct_expected_failure_message_parts(construct_expect_info(42));
    for (const auto& part : parts)
    {
        EXPECT_NE(std::string::npos, output.find(part));
    }
}

TEST(openssl_expect_tests, expect_or_throw)
{
    nanossl::test::std_output_redirect redirect{std::cout};

    EXPECT_NO_THROW(OPENSSL_EXPECT_OR_THROW(true));
    EXPECT_FALSE(redirect.has_any_content());

    EXPECT_THROW(OPENSSL_EXPECT_OR_THROW(SSL_do_handshake(*ssl)), std::runtime_error);
    EXPECT_FALSE(redirect.has_any_content());

    try
    {
        OPENSSL_EXPECT_OR_THROW(SSL_do_handshake(*ssl));
        FAIL();
    }
    catch (const std::exception& ex)
    {
        const std::string output{ex.what()};
        const auto parts = nanossl::test::construct_expected_failure_message_parts(construct_expect_info(64));
        for (const auto& part : parts)
        {
            EXPECT_NE(std::string::npos, output.find(part));
        }
    }

    EXPECT_FALSE(redirect.has_any_content());
}
