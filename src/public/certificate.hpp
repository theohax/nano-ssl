#pragma once

#include "public/key_pair.hpp"
#include "public/time_interval.hpp"
#include "public/detail/declare_facade.hpp"
#include "public/detail/shared_facade.hpp"

namespace nanossl
{

DECLARE_SHARED_FACADE_CLASS(certificate);

public:
    std::string retrieve_subject() const;

    std::string retrieve_issuer() const;

    time_interval retrieve_validity_interval() const;

    key_pair retrieve_public_key() const;
};

}
