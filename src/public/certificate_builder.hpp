#pragma once

#include "certificate.hpp"
#include "public/detail/declare_facade.hpp"
#include "public/detail/shared_facade.hpp"

#include <string_view>

namespace nanossl
{

class key_pair;
class time_interval;

DECLARE_SHARED_FACADE_CLASS(certificate_builder);

public:
    certificate_builder& with_subject(const std::string_view& subject);

    certificate_builder& with_issuer(const std::string_view& issuer);

    certificate_builder& with_validity_interval(const time_interval& interval);

    certificate_builder& with_public_key(const key_pair& key_pair);

    certificate build();
};

}
