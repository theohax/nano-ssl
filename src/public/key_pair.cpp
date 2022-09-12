#include "private/impl/key_pair_impl.hpp"
#include "key_pair.hpp"

namespace nanossl
{

key_pair::key_pair()
: base{}
{

}

void key_pair::generate()
{
    base::get_impl()->generate();
}

bool key_pair::has_private() const
{
    return base::get_impl()->has_private();
}

const buffer& key_pair::get_private() const
{
    return base::get_impl()->get_private();
}

std::string key_pair::get_private_as_hex() const
{
    return base::get_impl()->get_private_as_hex();
}

bool key_pair::has_public() const
{
    return base::get_impl()->has_public();
}

const buffer& key_pair::get_public() const
{
    return base::get_impl()->get_public();
}

std::string key_pair::get_public_as_hex() const
{
    return base::get_impl()->get_public_as_hex();
}

bool key_pair::operator==(const key_pair& rhs) const
{
    const auto& lhs_public_key = get_public();
    const auto& rhs_public_key = rhs.get_public();

    return lhs_public_key == rhs_public_key;
}

}
