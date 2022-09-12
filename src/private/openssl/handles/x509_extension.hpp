#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/x509.h>

DECLARE_OPENSSL_HANDLE(x509_extension, X509_EXTENSION, X509_EXTENSION_new, nullptr, X509_EXTENSION_free);
