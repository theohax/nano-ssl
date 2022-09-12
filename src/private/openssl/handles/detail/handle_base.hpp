#pragma once

#include "private/openssl/expect_or_throw.hpp"

#include <type_traits>

namespace nanossl::prv
{

template <class data_t>
class openssl_handle_base
{
public:
	using self = openssl_handle_base<data_t>;

	openssl_handle_base(const self& rhs);

	openssl_handle_base(self&& rhs) noexcept;

	auto& operator=(const self& rhs);

	auto& operator=(self&& rhs) noexcept;

	data_t* get() const;

	data_t* operator*() const;

    data_t** get_address();

	operator bool() const;

	void reset();

protected:
	openssl_handle_base();

	explicit openssl_handle_base(data_t* data);

private:
	data_t* m_data;
};

template <class data_t>
openssl_handle_base<data_t>::openssl_handle_base(const openssl_handle_base& rhs)
: m_data{rhs.m_data}
{

}

template <class data_t>
openssl_handle_base<data_t>::openssl_handle_base(openssl_handle_base&& rhs) noexcept
: m_data{rhs.m_data}
{
	rhs.reset();
}

template <class data_t>
auto& openssl_handle_base<data_t>::operator=(const self& rhs)
{
	if (this != &rhs)
	{
		reset();
		m_data = rhs.m_data;
	}

	return *this;
}

template <class data_t>
auto& openssl_handle_base<data_t>::operator=(self&& rhs) noexcept
{
	if (this != &rhs)
	{
		operator=(rhs);
		rhs.reset();
	}

	return *this;
}

template <class data_t>
data_t* openssl_handle_base<data_t>::get() const
{
	return m_data;
}

template <class data_t>
data_t* openssl_handle_base<data_t>::operator*() const
{
	return get();
}

template <class data_t>
data_t** openssl_handle_base<data_t>::get_address()
{
    return &m_data;
}

template <class data_t>
openssl_handle_base<data_t>::operator bool() const
{
	return get();
}

template <class data_t>
void openssl_handle_base<data_t>::reset()
{
	m_data = nullptr;
}

template <class data_t>
openssl_handle_base<data_t>::openssl_handle_base()
: m_data{}
{
    static_assert(
            std::is_same_v<decltype(self::operator=(std::declval<const self&>())), self&>,
            "operator= inferred type must be self&");
}

template <class data_t>
openssl_handle_base<data_t>::openssl_handle_base(data_t* data)
: m_data{data}
{
	OPENSSL_EXPECT_OR_THROW(m_data);
}

}
