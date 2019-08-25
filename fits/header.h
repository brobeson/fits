#ifndef FITS_HEADER_BLOCK_H
#define FITS_HEADER_BLOCK_H

#include "errors.h"
#include <complex>
#include <cstddef>
#include <variant>
#include <vector>

namespace fits
{
  /// A list of bytes, representing a FITS block.
  using raw_block = std::vector<std::byte>;

  namespace details
  {
    bool is_valid_header_key(const std::string& key);
  }

  class header_entry
  {
  public:
    /**
     * \brief Construct a header datum.
     * \tparam T The type of the value. This is restricted to `int`, `float`,
     * `std::complex<float>`, `std::string`, and `bool` by the FITS
     * specification. Failure to adhere to these restrictions will result in a
     * compile-time error.
     * \param[in] key The key for the datum. Keys must be between 1 and 8
     * characters, and are restricted to digits, upper case characters, dash,
     * and underscore.
     * \param[in] value The value for the datum.
     * \param[in] comment A comment to record with the datum. Comments are
     * optional. An entire header datum cannot exceed 80 bytes, including space
     * padding inserted by the library. Comments which would cause the datum to
     * exceed 80 bytes are truncated.
     * \throws fits::invalid_key This is thrown if \a key violates any of the
     * restrictions noted above.
     */
    template <typename T>
    header_entry(const std::string& key,
                 const T& val,
                 const std::string& comment = ""):
      m_key {key},
      m_comment {comment},
      m_value {val}
    {
      // clang-format off
      static_assert(std::is_same_v<T, int>
          || std::is_same_v<T, float>
          || std::is_same_v<T, std::complex<float>>
          || std::is_same_v<T, std::string>
          || std::is_same_v<T, bool>);
      // clang-format on
      FITS_EXPECTS(
        !key.empty(), fits::invalid_key, "Header key may not be empty.");
      FITS_EXPECTS(key.size() <= 8,
                   fits::invalid_key,
                   "Header key may not exceed 8 characters.");
      FITS_EXPECTS(details::is_valid_header_key(key),
                   fits::invalid_key,
                   "Header key may not contain invalid ASCII characters.");
    }

    /**
     * \brief Get the datum's key.
     * \return The key.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string key() const;

    /**
     * \brief Get the datum's comment.
     * \return The comment.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string comment() const;

    /**
     * \brief Get the datum's value.
     * \tparam T The data type of the returned value. See
     * fits::header_entry::header_entry() for type restrictions.
     * \return The datum's value.
     * \throws Unknown Anything thrown by invalid access of a `std::variant` is
     * allowed to propagate.
     */
    template <typename T>
    T value() const
    {
      // clang-format off
      static_assert(std::is_same_v<T, int>
          || std::is_same_v<T, float>
          || std::is_same_v<T, std::complex<float>>
          || std::is_same_v<T, std::string>
          || std::is_same_v<T, bool>);
      // clang-format on
      return std::get<T>(m_value);
    }

  private:
    std::string m_key;
    std::string m_comment;
    std::variant<int, float, std::complex<float>, std::string, bool> m_value {
      0};
  };

  /**
   * \brief Extract header information from a FITS block.
   * \param[in] block A list of bytes, representing a FITS block. The block must
   * be exactly 2880 bytes.
   * \return A list of header datum objects, extracted from the \a block. Note
   * that superfluous data is thrown away. This includes all bytes after the END
   * keyword, extraneous spaces, etc.
   * \throws fits::invalid_header_block This is thrown if the block is not
   * exactly 2880 bytes.
   */
  std::vector<header_entry> parse_header_block(const fits::raw_block& block);

  class header_block
  {
  };
}  // namespace fits

#endif
