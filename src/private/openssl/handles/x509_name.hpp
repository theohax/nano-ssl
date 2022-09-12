#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/x509.h>

DECLARE_OPENSSL_HANDLE(x509_name, X509_NAME, X509_NAME_new, nullptr, X509_NAME_free);
