#pragma once

#include <iosfwd>
#include <sstream>

namespace nanossl::test
{

class std_output_redirect
{
public:
    explicit std_output_redirect(std::ostream& output_stream);

    ~std_output_redirect();

    const std::stringstream& get_stream() const;

    std::string get_stream_content() const;

    bool has_any_content() const;

private:
    std::ostream& m_output_stream;
    std::stringstream m_redirect_stream;
    std::streambuf* m_old_buffer;
};

}
