#include "private/impl/certificate_impl.hpp"
#include "public/certificate.hpp"

namespace nanossl
{

certificate::certificate()
: base{}
{

}

std::string certificate::retrieve_subject() const
{
    return base::get_impl()->retrieve_subject();
}

std::string certificate::retrieve_issuer() const
{
    return base::get_impl()->retrieve_issuer();
}

time_interval certificate::retrieve_validity_interval() const
{
    return base::get_impl()->retrieve_validity_interval();
}

key_pair certificate::retrieve_public_key() const
{
    return key_pair::_detail_make_facade_from_impl<key_pair>(base::get_impl()->retrieve_public_key());
}

}
