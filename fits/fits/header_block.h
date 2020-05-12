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
    // clang-format off
    template <typename T> struct is_value: public std::false_type {};
    template <> struct is_value<int>: public std::true_type {};
    template <> struct is_value<float>: public std::true_type {};
    template <> struct is_value<std::complex<float>>: public std::true_type {};
    template <> struct is_value<std::string>: public std::true_type {};
    template <> struct is_value<bool>: public std::true_type {};
    // clang-format on

    inline void validate_header_key(const std::string& /*key*/)
    {
      throw fits::invalid_key {{""}, "thrown exception"};
    }

    bool is_valid_header_key(const std::string& key);
  }  // namespace detail

  class keyword_record
  {
  public:
    /**
     * \brief Construct a new keyword record object.
     * \param[in] key The key for the new record. The key must be between one
     * and eight characters. The characters may only be digits, upper case
     * characters, dashes, and underscores.
     * \param[in] comment The comment for the new record. Comments are optional.
     * An entire header keyword record cannot exceed 80 bytes, including space
     * padding inserted by the library. Comments which would cause the record to
     * exceed 80 bytes are truncated.
     * \throws fits::invalid_key If \a key is not valid.
     */
    explicit keyword_record(const std::string& key,
                            const std::string& comment = ""):
      m_key {key}, m_comment {comment}
    {
      FITS_EXPECTS(
        !m_key.empty(), fits::invalid_key, "Header key may not be empty.");
      FITS_EXPECTS(m_key.size() <= 8,
                   fits::invalid_key,
                   "Header key may not exceed 8 characters.");
      FITS_EXPECTS(details::is_valid_header_key(m_key),
                   fits::invalid_key,
                   "Header key may not contain invalid ASCII characters.");
    }

    /**
     * \brief Construct a new keyword record object.
     * \tparam Value The type of the record's value. This is restricted to
     * `int`, `float`, `std::complex<float>`, `std::string`, and `bool` by the
     * FITS specification. Failure to adhere to these restrictions will result
     * in a compile-time error.
     * \param[in] key The key for the new record. The key must be between one
     * and eight characters. The characters may only be digits, upper case
     * characters, dashes, and underscores.
     * \param[in] comment The comment for the new record. Comments are optional.
     * An entire header keyword record cannot exceed 80 bytes, including space
     * padding inserted by the library. Comments which would cause the record to
     * exceed 80 bytes are truncated.
     * \param[in] val The initial value of the record.
     * \throws fits::invalid_key If \a key is not valid.
     */
    template <typename Value>
    keyword_record(const std::string& key,
                   const std::string& comment,
                   const std::remove_cv_t<Value> val):
      m_key {key}, m_comment {comment}, m_value {val}
    {
      static_assert(fits::detail::is_value<std::remove_cv_t<Value>>::value);
    }

    /**
     * \brief Swap this keyword record with another.
     * \param[in] other The other record to swap with this.
     */
    void swap(keyword_record& other) noexcept;

    /**
     * \brief Get the record's key.
     * \return The key.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string key() const;

    /**
     * \brief Query if the record has a value.
     * \retval true The record has a value.
     * \retval false The record does not have a value.
     */
    bool has_a_value() const noexcept;

    /**
     * \brief Set the record's value.
     * \tparam Value The type of the new value. See keyword_record() for the
     * restrictions on the Value type.
     * \param[in] new_value The new value for the record.
     */
    template <typename Value>
    void set_value(const Value& new_value)
    {
      static_assert(fits::detail::is_value<Value>::value);
    }

    /**
     * \brief Set the record's value.
     * \tparam Value The type of the new value. See keyword_record() for the
     * restrictions on the Value type.
     * \param[in] new_value The new value for the record.
     */
    template <typename Value>
    fits::keyword_record& operator=(const Value& new_value)
    {
      this->set_value(new_value);
      // GCC 8.3 appears to have a bug, in which -Weffc++ warns that this
      // operator should return a reference to *this, even though it is.
#if __GNUC__ == 8
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Weffc++"
#endif
      return *this;
#if __GNUC__ == 8
#  pragma GCC diagnostic pop
#endif
    }

    /**
     * \brief Get the record's value.
     * \tparam Value The data type of the returned value. See
     * fits::keyword_record::keyword_record() for type restrictions.
     * \return The record's value.
     * \throws std::bad_variant_access This is thrown if \a Value does not match
     * the type of the current value.
     * \throws Unknown Anything thrown by invalid access of a `std::variant` is
     * allowed to propagate.
     */
    template <typename Value>
    Value value() const
    {
      static_assert(fits::detail::is_value<Value>::value);
      return std::get<Value>(m_value);
    }

    /**
     * \brief Query if the record has a comment.
     * \retval true The record has a comment.
     * \retval false The record does not have a comment.
     */
    bool has_a_comment() const noexcept;

    /**
     * \brief Set the record's comment.
     * \param[in] new_comment The new comment.
     */
    void set_comment(const std::string& new_comment);

    /**
     * \brief Get the record's comment.
     * \return The comment.
     * \throws Unknown Anything thrown by copying a `std::string` is allowed to
     * propagate.
     */
    std::string comment() const;

  private:
    std::string m_key;
    std::variant<int, float, std::complex<float>, std::string, bool> m_value {
      0};
    std::string m_comment {""};
  };

  /**
   * \brief Compare two keyword records for equality.
   * \param[in] a,b The two records to compare.
   * \retval true Both records of identical keys, comments, and values. If one
   * record does not have a comment or value, the other record also does not
   * have a comment or value.
   * \retval false The two records do not have identical keys, comments, or
   * values.
   */
  bool operator==(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept;

  /**
   * \brief Compare two keyword records for inequality.
   * \param[in] a,b The two records to compare.
   * \retval true The two records do not have identical keys, comments, or
   * values.
   * \retval false Both records of identical keys, comments, and values. If one
   * record does not have a comment or value, the other record also does not
   * have a comment or value.
   */
  bool operator!=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept;

  /**
   * \brief Query if one keyword record is less than another.
   * \param[in] a,b The two records to compare.
   * \retval true \a
   * \details Record data is compared in the following order:
   * - key
   * - value
   * - comment
   *
   */
  bool operator<(const fits::keyword_record& a,
                 const fits::keyword_record& b) noexcept;
  bool operator<=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept;
  bool operator>(const fits::keyword_record& a,
                 const fits::keyword_record& b) noexcept;
  bool operator>=(const fits::keyword_record& a,
                  const fits::keyword_record& b) noexcept;

  void swap(fits::keyword_record& a, fits::keyword_record& b) noexcept;
}  // namespace fits

#endif
