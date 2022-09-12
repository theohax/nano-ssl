#include "test/utils/expected_failure_message.hpp"

#include <functional>
#include <string_view>

namespace nanossl::test
{

std::vector<std::string> construct_expected_failure_message_parts(const nanossl::prv::expect_info& expect_info)
{
    std::vector<std::string> result{
        std::string{"Expectation failed: `"} +
        expect_info.expression.data() +
        "` at `",
        std::string{expect_info.file_path.data()} +
        ":" +
        std::to_string(expect_info.line_number) +
        "`."
    };

    if (expect_info.message.has_value())
    {
        result.push_back(expect_info.message->operator()());
    }

    return result;
}

}
