#include "fits/errors.h"

namespace fits
{
  invalid_key::invalid_key(fits::detail::invalid_string bad_string,
                           const std::string& what_message):
    std::invalid_argument {what_message},
    m_bad_string {std::move(bad_string)}
  {
    if (m_bad_string.m_string.length() <= m_bad_string.m_bad_character_index)
    {
      m_bad_string.m_bad_character_index = std::string::npos;
    }
  }

  std::string invalid_key::key() const { return m_bad_string.m_string; }

  std::string::value_type invalid_key::bad_character() const noexcept
  {
    if (m_bad_string.m_bad_character_index < m_bad_string.m_string.length())
    {
      return m_bad_string.m_string[m_bad_string.m_bad_character_index];
    }
    return '\0';
  }

  std::string::size_type invalid_key::bad_character_index() const noexcept
  {
    return m_bad_string.m_bad_character_index;
  }

  invalid_comment::invalid_comment(fits::detail::invalid_string bad_string,
                                   const std::string& what_message):
    std::invalid_argument {what_message},
    m_bad_string {std::move(bad_string)}
  {
    if (m_bad_string.m_string.length() <= m_bad_string.m_bad_character_index)
    {
      m_bad_string.m_bad_character_index = std::string::npos;
    }
  }

  std::string invalid_comment::comment() const { return m_bad_string.m_string; }

  std::string::value_type invalid_comment::bad_character() const noexcept
  {
    if (m_bad_string.m_bad_character_index < m_bad_string.m_string.length())
    {
      return m_bad_string.m_string[m_bad_string.m_bad_character_index];
    }
    return '\0';
  }

  std::string::size_type invalid_comment::bad_character_index() const noexcept
  {
    return m_bad_string.m_bad_character_index;
  }
}  // namespace fits
