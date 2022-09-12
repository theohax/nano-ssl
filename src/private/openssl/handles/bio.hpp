#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/bio.h>

DECLARE_OPENSSL_HANDLE(bio, BIO, BIO_new, BIO_up_ref, BIO_free);
