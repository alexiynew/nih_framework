/// @file
/// @brief The realisation details of the logging system.
/// @author Fedorov Alexey
/// @date 03.03.2018

#include <log/log.hpp>
#include <log/log_details.hpp>

namespace {

constexpr size_t log_buffer_size = 64;

} // namespace

namespace framework {

namespace log {

namespace log_details {

#pragma region log_buffer

log_buffer::log_buffer(::framework::log::severity_level level, const std::string& tag)
    : m_level(level), m_tag(tag), m_buffer(log_buffer_size)
{
    reset_pointers();
}

log_buffer::~log_buffer()
{
    sync();
}

int log_buffer::overflow(int character)
{
    if (character == traits_type::eof()) {
        return traits_type::eof();
    }

    const size_t size = m_buffer.size();
    m_buffer.resize(size * 2);
    reset_pointers();
    pbump(static_cast<int>(size));

    return sputc(static_cast<char>(character));
}

int log_buffer::sync()
{
    if (pptr() == pbase()) {
        return 0;
    }

    const size_t size = static_cast<size_t>(pptr() - pbase());

    ::framework::log::logger()->add_message(m_level, m_tag, std::string(m_buffer.data(), size));

    reset_pointers();

    return 0;
}

void log_buffer::reset_pointers()
{
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
}

#pragma endregion

log_ostream::log_ostream(std::unique_ptr<std::streambuf> buffer)
    : std::ostream(buffer.get()), m_buffer(std::move(buffer))
{}

log_ostream::~log_ostream() = default;

log_ostream::log_ostream(log_ostream&& other) : m_buffer(std::move(other.m_buffer))
{
    rdbuf(m_buffer.get());
}

log_ostream& log_ostream::operator=(log_ostream&& other)
{
    std::ostream::operator=(std::move(other));

    m_buffer = std::move(other.m_buffer);

    return *this;
}

} // namespace log_details

} // namespace log

} // namespace framework