#pragma once

#include "private/impl/certificate_impl.hpp"
#include "private/impl/detail/declare_impl.hpp"
#include "private/openssl/handles/x509.hpp"

#include <string_view>

namespace nanossl
{

class time_interval;

}

namespace nanossl::prv
{

class key_pair_impl;

DECLARE_IMPL_CLASS(certificate_builder_impl, x509_handle);

public:
    void with_subject(const std::string_view& subject);

    void with_issuer(const std::string_view& issuer);

    void with_validity_interval(const time_interval& interval);

    void with_public_key(const key_pair_impl& key_pair);

    certificate_impl build();

private:
    bool m_built;

    void make_handle_if_not_made();
};

}
