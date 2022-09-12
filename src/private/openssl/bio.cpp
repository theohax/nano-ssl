#include "private/openssl/bio.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/buffer.hpp"

#include <openssl/bio.h>

#include <cstddef>

namespace nanossl::prv
{

bio::bio()
: m_method_handle{bio_method_handle_view::make(BIO_s_mem())},
  m_handle{bio_handle::make(*m_method_handle)}
{

}

const bio_handle& bio::operator*() const
{
    return m_handle;
}

std::string bio::read_content() const
{
    auto buffer = buffer_handle_view::make();

    const auto size = BIO_get_mem_data(*m_handle, buffer.get_address());
    OPENSSL_EXPECT_OR_THROW(size >= 0);

    if (!size)
    {
        return std::string{};
    }

    return std::string{reinterpret_cast<const char*>(*buffer), static_cast<std::size_t>(size)};
}

}
