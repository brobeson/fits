#include "fits/header.h"
#include <algorithm>

namespace fits
{
  namespace details
  {
    bool is_valid_header_key(const std::string& key)
    {
      return std::all_of(key.begin(), key.end(), [](const char c) {
        return ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || (c == '_')
               || (c == '-');
      });
    }
  }  // namespace details

  std::string header_entry::key() const { return m_key; }

  std::string header_entry::comment() const { return m_comment; }
}  // namespace fits
