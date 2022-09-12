#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/x509.h>

DECLARE_OPENSSL_HANDLE(x509_algorithm, X509_ALGOR, X509_ALGOR_new, nullptr, X509_ALGOR_free);
