#include "private/expect/expect_or_throw.hpp"
#include "private/utils/recursion_guard.hpp"

namespace nanossl::prv
{

recursion_guard::recursion_guard(bool& entered)
: m_entered{entered}
{
	EXPECT_OR_THROW(!m_entered);

	m_entered = true;
}

recursion_guard::~recursion_guard ()
{
	m_entered = false;
}

}
