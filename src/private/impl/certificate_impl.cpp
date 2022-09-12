#include "private/expect/expect_or_throw.hpp"
#include "private/impl/certificate_impl.hpp"
#include "private/openssl/bio.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/asn1_time.hpp"
#include "private/openssl/handles/x509_name.hpp"

#include <openssl/asn1.h>
#include <openssl/x509.h>

#include <chrono>
#include <ctime>

namespace
{

template <auto retrieve_function>
std::string retrieve_name(const nanossl::prv::x509_handle& handle)
{
    nanossl::prv::bio bio{};

    const auto subject = nanossl::prv::x509_name_handle_view::make(retrieve_function(*handle));
    OPENSSL_EXPECT_OR_THROW(X509_NAME_print_ex(**bio, *subject, 0, 0));

    return bio.read_content();
}

template <auto retrieve_function>
nanossl::time_interval::point retrieve_validity_time_point(const nanossl::prv::x509_handle& handle)
{
    auto point = nanossl::prv::asn1_time_handle_view::make(retrieve_function(*handle));
    OPENSSL_EXPECT_OR_THROW(ASN1_TIME_normalize(*point));

    tm point_tm{};
    OPENSSL_EXPECT_OR_THROW(ASN1_TIME_to_tm(*point, &point_tm));

    time_t point_time_t = mktime(&point_tm);
    EXPECT_OR_THROW(-1 != point_time_t);

    return std::chrono::system_clock::from_time_t(point_time_t);
}

}

namespace nanossl::prv
{

certificate_impl::certificate_impl()
: base{}
{

}

DECLARE_IMPL_CONSTRUCTOR(certificate_impl, x509_handle)
{

}

std::string certificate_impl::retrieve_subject() const
{
    return retrieve_name<X509_get_subject_name>(base::get_handle());
}

std::string certificate_impl::retrieve_issuer() const
{
    return retrieve_name<X509_get_issuer_name>(base::get_handle());
}

time_interval certificate_impl::retrieve_validity_interval() const
{
    auto from = retrieve_validity_time_point<X509_get_notBefore>(base::get_handle());
    auto to = retrieve_validity_time_point<X509_get_notAfter>(base::get_handle());

    return time_interval{std::move(from), std::move(to)};
}

key_pair_impl certificate_impl::retrieve_public_key() const
{
    return key_pair_impl{evp_pkey_handle::make(X509_get_pubkey(*base::get_handle()))};
}

}
