#include "private/impl/certificate_builder_impl.hpp"
#include "certificate_builder.hpp"
#include "key_pair.hpp"

namespace nanossl
{

certificate_builder::certificate_builder()
: base{}
{

}

certificate_builder& certificate_builder::with_subject(const std::string_view& subject)
{
    base::get_impl()->with_subject(subject);
    return *this;
}

certificate_builder& certificate_builder::with_issuer(const std::string_view& subject)
{
    base::get_impl()->with_issuer(subject);
    return *this;
}

certificate_builder& certificate_builder::with_validity_interval(const time_interval& interval)
{
    base::get_impl()->with_validity_interval(interval);
    return *this;
}

certificate_builder& certificate_builder::with_public_key(const key_pair& key_pair)
{
    base::get_impl()->with_public_key(*key_pair.get_impl());
    return *this;
}

certificate certificate_builder::build()
{
    return certificate::_detail_make_facade_from_impl<certificate>(base::get_impl()->build());
}

}
