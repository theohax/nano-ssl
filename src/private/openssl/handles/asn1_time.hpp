#pragma once

#include "private/openssl/handles/detail/declare_handle.hpp"

#include <openssl/asn1.h>

DECLARE_OPENSSL_HANDLE(asn1_time, ASN1_TIME, ASN1_TIME_new, nullptr, ASN1_TIME_free);
