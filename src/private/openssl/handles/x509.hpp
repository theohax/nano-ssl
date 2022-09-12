#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/x509.h>

DECLARE_OPENSSL_HANDLE(x509, X509, X509_new, X509_up_ref, X509_free);
