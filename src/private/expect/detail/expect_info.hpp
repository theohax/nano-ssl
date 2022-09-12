#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <string>
#include <string_view>

namespace nanossl::prv
{

struct expect_info
{
    std::string_view expression;
    std::string_view file_path;
    std::size_t line_number;
    std::optional<std::function<std::string()>> message;
};

}
