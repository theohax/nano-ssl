#pragma once

#include "private/impl/key_pair_impl.hpp"
#include "private/impl/detail/declare_impl.hpp"
#include "private/openssl/handles/x509.hpp"
#include "public/time_interval.hpp"

#include <string>

namespace nanossl::prv
{

DECLARE_IMPL_CLASS(certificate_impl, x509_handle);

public:
    std::string retrieve_subject() const;

    std::string retrieve_issuer() const;

    time_interval retrieve_validity_interval() const;

    key_pair_impl retrieve_public_key() const;
};

}
