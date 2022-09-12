#include "test/utils/std_output_redirect.hpp"

namespace nanossl::test
{

std_output_redirect::std_output_redirect(std::ostream& output_stream)
: m_output_stream{output_stream},
  m_redirect_stream{},
  m_old_buffer{m_output_stream.rdbuf(m_redirect_stream.rdbuf())}
{

}

std_output_redirect::~std_output_redirect()
{
    m_output_stream.rdbuf(m_old_buffer);
}

const std::stringstream& std_output_redirect::get_stream() const
{
    return m_redirect_stream;
}

std::string std_output_redirect::get_stream_content() const
{
    return get_stream().str();
}

bool std_output_redirect::has_any_content() const
{
    return !get_stream_content().empty();
}

}
