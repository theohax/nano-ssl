#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/evp.h>

DECLARE_OPENSSL_HANDLE(evp_pkey, EVP_PKEY, EVP_PKEY_new, EVP_PKEY_up_ref, EVP_PKEY_free);
