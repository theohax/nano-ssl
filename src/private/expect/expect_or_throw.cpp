#include "private/expect/expect_or_throw.hpp"

#include <stdexcept>

namespace nanossl::prv
{

DECLARE_EXPECTATION_FAILED_FUNCTION(throw_after_expectation_failed)
{
    throw std::runtime_error{construct_failure_message(info)};
}

}
