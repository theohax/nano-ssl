#include "private/openssl/handles/buffer.hpp"

#include <openssl/crypto.h>

namespace nanossl::prv
{

void delete_openssl_buffer (std::uint8_t* data)
{
	OPENSSL_free(data);
}

}
