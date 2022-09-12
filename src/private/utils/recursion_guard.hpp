#pragma once

namespace nanossl::prv
{

class recursion_guard
{
public:
	explicit recursion_guard(bool& entered);

	~recursion_guard();

private:
	bool& m_entered;
};

}
