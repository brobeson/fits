#include "fits_testing.h"

using namespace std::literals::string_literals;

namespace fits_testing
{
  bool operator==(const fits::invalid_key& a,
                  const fits::invalid_key& b) noexcept
  {
    return a.key() == b.key() && a.bad_character() == b.bad_character()
           && a.bad_character_index() == b.bad_character_index()
           && a.what() == b.what();
  }

  std::string to_string(const fits::invalid_key& exception)
  {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
    return "key: '"s.append(exception.key())
      .append("' bad index: '")
      .append(std::to_string(exception.bad_character_index()))
      .append("' what message: '")
      .append(exception.what())
      .append(1, '\'');
  }
}  // namespace fits_testing
