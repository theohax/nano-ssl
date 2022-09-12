#include "private/openssl/bio.hpp"
#include "private/openssl/error.hpp"
#include "private/utils/recursion_guard.hpp"

#include <openssl/err.h>

namespace
{
    constexpr std::string_view no_error_string = "no error";
    constexpr std::string_view recursive_call_error_string = "recursive call within openssl_error::retrieve_last";
}

namespace nanossl::prv
{

openssl_error& openssl_error::get_instance()
{
    static openssl_error instance{};
    return instance;
}

std::string openssl_error::retrieve_last() const
{
    std::unique_lock lock{m_mutex};

    try
    {
        recursion_guard guard{m_is_retrieving};

        bio bio{};
        ERR_print_errors(**bio);

        auto result = bio.read_content();
        if (result.empty())
        {
            return no_error_string.data();
        }

        return result;
    }
    catch (...)
    {
        return recursive_call_error_string.data();
    }
}

openssl_error::openssl_error()
: m_is_retrieving{false},
  m_mutex{}
{

}

}
