#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/bio.h>

DECLARE_OPENSSL_HANDLE(bio_method, const BIO_METHOD, nullptr, nullptr, nullptr);
