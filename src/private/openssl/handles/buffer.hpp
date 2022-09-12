#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <cstdint>

namespace nanossl::prv
{

void delete_openssl_buffer (std::uint8_t* data);

}

DECLARE_OPENSSL_HANDLE(buffer, std::uint8_t, nullptr, nullptr, nanossl::prv::delete_openssl_buffer);
