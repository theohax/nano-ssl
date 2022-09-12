#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/ssl.h>

DECLARE_OPENSSL_HANDLE(ssl, SSL, SSL_new, SSL_up_ref, SSL_free);
