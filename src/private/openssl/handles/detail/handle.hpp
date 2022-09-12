#pragma once

#include "private/expect/expect_or_throw.hpp"
#include "private/openssl/expect_or_throw.hpp"
#include "private/openssl/handles/detail/handle_base.hpp"
#include "private/openssl/handles/detail/handle_view.hpp"

#include <type_traits>
#include <utility>

namespace nanossl::prv
{

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
class openssl_handle : public openssl_handle_base<data_t>
{
public:
	using base = openssl_handle_base<data_t>;
	using self = openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>;

	static auto make();

	static auto make(data_t* data);

	template <class... ArgsT>
	static auto make(ArgsT... args);

	openssl_handle();

	openssl_handle(const self& rhs);

	openssl_handle(self&& rhs) noexcept;

	~openssl_handle();

	auto& operator=(const self& rhs);

	auto& operator=(self&& rhs) noexcept;

	data_t* release();

	operator openssl_handle_view<data_t>() const;

private:
	explicit openssl_handle(data_t* data);

	void increase_references();

	void decrease_references();

	template <class self_t>
	auto& assign(self_t&& rhs);
};

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	openssl_handle(const self& rhs)
	: base{rhs}
{
	increase_references();
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
openssl_handle(self&& rhs) noexcept
	: base{std::move(rhs)}
{

}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	~openssl_handle()
{
	base::reset();
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
auto& openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	operator=(const self& rhs)
{
	return assign(rhs);
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
auto& openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	operator=(self&& rhs) noexcept
{
	return assign(std::move(rhs));
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
auto openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::make()
{
	return self{create_function()};
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
auto openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
    make(data_t* data)
{
	return self{data};
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
template <class... ArgsT>
auto openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
    make(ArgsT... args)
{
	return self{create_function(std::forward<ArgsT...>(args...))};
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
openssl_handle()
	: base{}
{

}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
data_t* openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	release()
{
	const auto* result = base::get();

	base::reset();

	return result;
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	operator openssl_handle_view<data_t>() const
{
	return openssl_handle_view<data_t>::make(base::get());
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	openssl_handle(data_t* data)
	: base{data}
{
    EXPECT_OR_THROW(data);
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
void openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	increase_references()
{
	auto* data = base::get();

	EXPECT_OR_THROW(data);
	OPENSSL_EXPECT_OR_THROW(increase_references_function(data));
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
void openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	decrease_references()
{
	auto* data = base::get();
    if (data)
    {
        if constexpr (std::is_same_v<std::invoke_result_t<decltype(decrease_references_function), data_t* >, void>)
        {
            decrease_references_function(data);
        }
        else
        {
            OPENSSL_EXPECT_OR_THROW(decrease_references_function(data));
        }

        base::reset();
    }
}

template <class data_t, auto create_function, auto increase_references_function, auto decrease_references_function>
template <class self_t>
auto& openssl_handle<data_t, create_function, increase_references_function, decrease_references_function>::
	assign(self_t&& rhs)
{
	if (this != &rhs)
	{
		decrease_references();
		static_cast<void>(base::operator=(std::forward<self_t>(rhs)));
		increase_references();
	}

	return *this;
}

}
