#include "private/expect/expect_or_throw.hpp"
#include "private/impl/key_pair_impl.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/evp_pkey_ctx.hpp"

#include <cstddef>

namespace
{

constexpr std::size_t ED25519_PRIVATE_KEY_SIZE = 32;
constexpr std::size_t ED25519_PUBLIC_KEY_SIZE = 32;

template <auto retrieve_function>
nanossl::buffer retrieve_key_part(const nanossl::prv::evp_pkey_handle& handle, const std::size_t expected_size)
{
    std::size_t size{};
    OPENSSL_EXPECT_OR_THROW(retrieve_function(*handle, nullptr, &size));
    EXPECT_OR_THROW(expected_size == size);

    nanossl::buffer result(size);
    OPENSSL_EXPECT_OR_THROW(retrieve_function(*handle, result.data(), &size));
    EXPECT_OR_THROW(expected_size == size);

    return result;
}

}

namespace nanossl::prv
{

key_pair_impl::key_pair_impl()
: base{}
{

}

DECLARE_IMPL_CONSTRUCTOR(key_pair_impl, evp_pkey_handle),
 m_private{},
 m_public{}
{
    extract_private();
    extract_public();
}

void key_pair_impl::generate()
{
    const auto evp_pkey_ctx = evp_pkey_ctx_handle::make(EVP_PKEY_CTX_new_id(NID_ED25519, nullptr));
    OPENSSL_EXPECT_OR_THROW(EVP_PKEY_keygen_init(*evp_pkey_ctx));

    base::make_handle();
    OPENSSL_EXPECT_OR_THROW(EVP_PKEY_keygen(*evp_pkey_ctx, base::get_handle().get_address()));

    extract_private();
    extract_public();
}

bool key_pair_impl::has_private() const
{
    return m_private.has_value();
}

const buffer& key_pair_impl::get_private() const
{
    EXPECT_OR_THROW(has_private());
    return *m_private;
}

std::string key_pair_impl::get_private_as_hex() const
{
    EXPECT_OR_THROW(has_private());
    return {};
}

bool key_pair_impl::has_public() const
{
    return m_public.has_value();
}

const buffer& key_pair_impl::get_public() const
{
    EXPECT_OR_THROW(has_public());
    return *m_public;
}

std::string key_pair_impl::get_public_as_hex() const
{
    EXPECT_OR_THROW(has_public());
    return {};
}

void key_pair_impl::extract_private()
{
    m_private = retrieve_key_part<EVP_PKEY_get_raw_private_key>(base::get_handle(), ED25519_PRIVATE_KEY_SIZE);
}

void key_pair_impl::extract_public()
{
    m_public = retrieve_key_part<EVP_PKEY_get_raw_public_key>(base::get_handle(), ED25519_PUBLIC_KEY_SIZE);
}

}
