#pragma once

#include "private/impl/detail/declare_impl.hpp"
#include "private/openssl/handles/evp_pkey.hpp"
#include "public/buffer.hpp"

#include <optional>
#include <string>

namespace nanossl::prv
{

DECLARE_IMPL_CLASS(key_pair_impl, evp_pkey_handle);

public:
    void generate();

    bool has_private() const;

    const buffer& get_private() const;

    std::string get_private_as_hex() const;

    bool has_public() const;

    const buffer& get_public() const;

    std::string get_public_as_hex() const;

private:
    std::optional<buffer> m_private;
    std::optional<buffer> m_public;

    void extract_private();

    void extract_public();
};

}
