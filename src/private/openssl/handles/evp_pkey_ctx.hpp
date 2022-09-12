#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/evp.h>

DECLARE_OPENSSL_HANDLE(evp_pkey_ctx, EVP_PKEY_CTX, EVP_PKEY_CTX_new, nullptr, EVP_PKEY_CTX_free);
