#include "private/expect/detail/expect_info.hpp"

#include <string>
#include <vector>

namespace nanossl::test
{
    std::vector<std::string> construct_expected_failure_message_parts(const nanossl::prv::expect_info& expect_info);
}
