#pragma once

#include "buffer.hpp"
#include "public/detail/declare_facade.hpp"
#include "public/detail/shared_facade.hpp"

namespace nanossl
{

DECLARE_SHARED_FACADE_CLASS(key_pair);

public:
    void generate();

    bool has_private() const;

    const buffer& get_private() const;

    std::string get_private_as_hex() const;

    bool has_public() const;

    const buffer& get_public() const;

    std::string get_public_as_hex() const;

    bool operator==(const key_pair& rhs) const;
};

}
