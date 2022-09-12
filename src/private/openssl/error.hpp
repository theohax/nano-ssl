#pragma once

#include <mutex>
#include <string>

namespace nanossl::prv
{

class openssl_error
{
public:
    static openssl_error& get_instance();

    std::string retrieve_last() const;

private:
    mutable bool m_is_retrieving;
    mutable std::recursive_mutex m_mutex;

    openssl_error();
};

}
