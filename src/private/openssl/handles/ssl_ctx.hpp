#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/ssl.h>

DECLARE_OPENSSL_HANDLE(ssl_ctx, SSL_CTX, SSL_CTX_new, SSL_CTX_up_ref, SSL_CTX_free);
