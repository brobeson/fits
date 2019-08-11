#ifndef FITS_ERRORS_H
#define FITS_ERRORS_H

#include <stdexcept>

namespace fits
{
  struct invalid_key: public std::logic_error
  {
    explicit invalid_key(const char* const message): std::logic_error {message}
    {
    }
  };

  struct invalid_header_block: public std::logic_error
  {
    explicit invalid_header_block(const char* const message):
      std::logic_error {message}
    {
    }
  };

  struct parse_error: public std::logic_error
  {
    explicit parse_error(const char* const message): std::logic_error {message}
    {
    }
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
