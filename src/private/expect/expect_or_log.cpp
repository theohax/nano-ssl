#include "private/expect/expect_or_log.hpp"
#include "private/log/log.hpp"

namespace nanossl::prv
{

DECLARE_EXPECTATION_FAILED_FUNCTION(log_after_expectation_failed)
{
    log(construct_failure_message(info));
}

}
