#pragma once

#include "private/openssl/handles/detail/handle_base.hpp"

namespace nanossl::prv
{

template <class data_t>
class openssl_handle_view : public openssl_handle_base<data_t>
{
public:
	static auto make();

	static auto make(data_t* data);

private:
	using self = openssl_handle_view<data_t>;
	using base = openssl_handle_base<data_t>;

	using base::base;
};

template <class data_t>
auto openssl_handle_view<data_t>::make()
{
	return self{};
}

template <class data_t>
auto openssl_handle_view<data_t>::make(data_t* data)
{
	return self{data};
}

}
