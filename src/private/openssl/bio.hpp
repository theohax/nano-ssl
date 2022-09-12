#pragma once

#include "private/openssl/handles/bio.hpp"
#include "private/openssl/handles/bio_method.hpp"

#include <string>

namespace nanossl::prv
{

class bio
{
public:
    bio();

    const bio_handle& operator*() const;

    std::string read_content() const;

private:
    bio_method_handle_view m_method_handle;
    bio_handle m_handle;
};

}
