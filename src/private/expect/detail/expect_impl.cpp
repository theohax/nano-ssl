#include "private/expect/detail/expect_impl.hpp"

namespace nanossl::prv
{

std::string construct_failure_message (const expect_info& info)
{
	auto result = std::string{"Expectation failed: "} +
            "`" +
            info.expression.data() +
            "` at `" +
            info.file_path.data() +
            ":" +
            std::to_string(info.line_number) +
            "`.";

    if (info.message.has_value())
    {
        result += " " + info.message->operator()();
    }

    return result;
}

}
