#include "private/expect/expect_or_throw.hpp"
#include "private/impl/certificate_builder_impl.hpp"
#include "private/impl/key_pair_impl.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/x509_name.hpp"
#include "public/time_interval.hpp"

#include <openssl/asn1.h>
#include <openssl/obj_mac.h>
#include <openssl/x509.h>

#include <utility>

namespace
{

template <auto retrieve_function>
void set_name(const nanossl::prv::x509_handle& handle, const std::string_view& name)
{
    const auto x509_name = nanossl::prv::x509_name_handle_view::make(retrieve_function(*handle));
    OPENSSL_EXPECT_OR_THROW(X509_NAME_add_entry_by_NID(
            *x509_name,
            NID_commonName,
            MBSTRING_ASC,
            reinterpret_cast<const std::uint8_t*>(name.data()),
            -1,
            -1,
            0));
}

}

namespace nanossl::prv
{

certificate_builder_impl::certificate_builder_impl()
: base{},
  m_built{false}
{

}

certificate_builder_impl::certificate_builder_impl(x509_handle handle)
: base{std::move(handle)},
  m_built{false}
{

}

void certificate_builder_impl::with_subject(const std::string_view& subject)
{
    make_handle_if_not_made();
    set_name<X509_get_subject_name>(base::get_handle(), subject);
}

void certificate_builder_impl::with_issuer(const std::string_view& issuer)
{
    make_handle_if_not_made();
    set_name<X509_get_issuer_name>(base::get_handle(), issuer);
}

void certificate_builder_impl::with_validity_interval(const time_interval& interval)
{
    make_handle_if_not_made();
    static_cast<void>(interval);
}

    void certificate_builder_impl::with_public_key(const key_pair_impl& key_pair)
{
    make_handle_if_not_made();
    OPENSSL_EXPECT_OR_THROW(X509_set_pubkey(*base::get_handle(), *key_pair.get_handle()));
}

certificate_impl certificate_builder_impl::build()
{
    EXPECT_OR_THROW(!m_built);

    auto& handle = base::get_handle();
    EXPECT_OR_THROW(handle);

    m_built = true;

    return certificate_impl{std::move(handle)};
}

void certificate_builder_impl::make_handle_if_not_made()
{
    EXPECT_OR_THROW(!m_built);

    if (!base::get_handle())
    {
        base::make_handle();
    }
}

}
