#ifndef FITS_HEADER_BLOCK_H
#define FITS_HEADER_BLOCK_H

#include "errors.h"
#include <complex>
#include <cstddef>
#include <variant>
#include <vector>

namespace fits
{
  namespace detail
  {
    inline void validate_header_key(const std::string& /*key*/)
    {
      throw fits::invalid_key {{""}, "thrown exception"};
    }
  }  // namespace detail
  namespace details
  {
    bool is_valid_header_key(const std::string& key);
  }

  class keyword_record
  {
  public:
    explicit keyword_record(const std::string& key): m_key {key} {}
    keyword_record(const std::string& key, const std::string& comment):
      m_key {key},
      m_comment {comment}
    {
    }
    keyword_record(const std::string& key,
                   const std::string& comment,
                   const int val):
      m_key {key},
      m_comment {comment},
      m_value {val}
    {
    }

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
    // template <typename T>
    // keyword_record(const std::string& key,
    //               const T& val,
    //               const std::string& comment = ""):
    //  m_key {key},
    //  m_comment {comment},
    //  m_value {val}
    //{
    //  // clang-format off
    //  static_assert(std::is_same_v<T, int>
    //      || std::is_same_v<T, float>
    //      || std::is_same_v<T, std::complex<float>>
    //      || std::is_same_v<T, std::string>
    //      || std::is_same_v<T, bool>);
    //  // clang-format on
    //  // FITS_EXPECTS(
    //  //  !key.empty(), fits::invalid_key, "Header key may not be empty.");
    //  // FITS_EXPECTS(key.size() <= 8,
    //  //             fits::invalid_key,
    //  //             "Header key may not exceed 8 characters.");
    //  // FITS_EXPECTS(details::is_valid_header_key(key),
    //  //             fits::invalid_key,
    //  //             "Header key may not contain invalid ASCII characters.");
    //}

    // void swap(keyword_record& other) noexcept;

    /**
     * \brief Get the datum's key.
     * \return The key.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string key() const;

    // bool has_a_value() const noexcept;

    // template <typename T>
    // void set_value(const T& new_value)
    //{
    //}

    //    template <typename T>
    //    fits::keyword_record& operator=(const T& new_value)
    //    {
    //      // GCC 8.3 appears to have a bug, in which -Weffc++ warns that this
    //      // operator should return a reference to *this, even though it is.
    //#if __GNUC__ == 8
    //#  pragma GCC diagnostic push
    //#  pragma GCC diagnostic ignored "-Weffc++"
    //      return *this;
    //#  pragma GCC diagnostic pop
    //#endif
    //    }

    /**
     * \brief Get the datum's value.
     * \tparam T The data type of the returned value. See
     * fits::keyword_record::keyword_record() for type restrictions.
     * \return The datum's value.
     * \throws Unknown Anything thrown by invalid access of a `std::variant` is
     * allowed to propagate.
     */
    // template <typename T>
    // T value() const
    //{
    //  // clang-format off
    //  static_assert(std::is_same_v<T, int>
    //      || std::is_same_v<T, float>
    //      || std::is_same_v<T, std::complex<float>>
    //      || std::is_same_v<T, std::string>
    //      || std::is_same_v<T, bool>);
    //  // clang-format on
    //  return std::get<T>(m_value);
    //}

    // bool has_a_comment() const noexcept;
    // void set_comment(const std::string& new_comment);

    /**
     * \brief Get the datum's comment.
     * \return The comment.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string comment() const;

  private:
    std::string m_key;
    std::string m_comment {""};
    std::variant<int, float, std::complex<float>, std::string, bool> m_value {
      0};
  };

  // bool operator==(const fits::keyword_record& a,
  //                const fits::keyword_record& b) noexcept
  // bool operator!=(const fits::keyword_record& a,
  //                const fits::keyword_record& b) noexcept;
  // bool operator<(const fits::keyword_record& a,
  //               const fits::keyword_record& b) noexcept;
  // bool operator<=(const fits::keyword_record& a,
  //                const fits::keyword_record& b) noexcept;
  // bool operator>(const fits::keyword_record& a,
  //               const fits::keyword_record& b) noexcept;
  // bool operator>=(const fits::keyword_record& a,
  //                const fits::keyword_record& b) noexcept;

  // void swap(fits::keyword_record& a, fits::keyword_record& b) noexcept;
}  // namespace fits

#endif
