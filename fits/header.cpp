#include "fits/header.h"
#include <algorithm>

namespace fits::details
{
  bool is_valid_header_key(const std::string& key)
  {
    return std::all_of(key.begin(), key.end(), [](const char c) {
      return ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || (c == '_')
             || (c == '-');
    });
  }
}  // namespace fits::details

namespace fits
{
  std::string keyword_record::key() const { return m_key; }

  std::string keyword_record::comment() const { return m_comment; }

  bool operator==(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept
  {
    /// \todo How do I handle records with different value types.
    return a.key() == b.key() && a.comment() == b.comment();
  }

  bool operator!=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept
  {
    return !(a == b);
  }

  bool operator<(const fits::keyword_record& a,
                 const fits::keyword_record& b) noexcept
  {
    return a.key() < b.key();
  }

  bool operator<=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept
  {
    return a.key() <= b.key();
  }

  bool operator>(const fits::keyword_record& a,
                 const fits::keyword_record& b) noexcept
  {
    return !(a <= b);
  }

  bool operator>=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept
  {
    return !(a < b);
  }

  void swap(fits::keyword_record& /*a*/, fits::keyword_record& /*b*/) noexcept
  {
  }
}  // namespace fits
