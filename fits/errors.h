#ifndef FITS_ERRORS_H
#define FITS_ERRORS_H

#include <stdexcept>

namespace fits
{
  namespace detail
  {
    struct invalid_string
    {
      std::string m_string;
      std::string::size_type m_bad_character_index {std::string::npos};
    };
  }  // namespace detail

  class invalid_key: public std::invalid_argument
  {
  public:
    invalid_key(fits::detail::invalid_string bad_string,
                const std::string& what_message);
    std::string key() const;
    std::string::value_type bad_character() const noexcept;
    std::string::size_type bad_character_index() const noexcept;

  private:
    fits::detail::invalid_string m_bad_string {"", std::string::npos};
  };

  class invalid_comment: public std::invalid_argument
  {
  public:
    invalid_comment(fits::detail::invalid_string bad_string,
                    const std::string& what_message);
    std::string comment() const;
    std::string::value_type bad_character() const noexcept;
    std::string::size_type bad_character_index() const noexcept;

  private:
    fits::detail::invalid_string m_bad_string {"", std::string::npos};
  };
}  // namespace fits

// Copied from GSL assert, and modified to allow specification of the exception
// and the exception message at the macro call site.
#if defined(__clang__) || defined(__GNUC__)
#  define FITS_LIKELY(x) __builtin_expect(!!(x), 1)
#else
#  define FITS_LIKELY(x) (!!(x))
#endif
#define FITS_STRINGIFY_DETAIL(x) #x
#define FITS_STRINGIFY(x) FITS_STRINGIFY_DETAIL(x)

#define FITS_CONTRACT_CHECK(type, condition, exc, msg)                      \
  (FITS_LIKELY(condition) ? static_cast<void>(0)                            \
                          : throw exc("fits: " type " failure at " __FILE__ \
                                      ":" FITS_STRINGIFY(__LINE__) "\n" msg))

#define FITS_EXPECTS(condition, exc, msg) \
  FITS_CONTRACT_CHECK("Precondition", condition, exc, msg)
#define FITS_ENSURES(condition, exc, msg) \
  FITS_CONTRACT_CHECK("Postcondition", condition, exc, msg)

#endif
