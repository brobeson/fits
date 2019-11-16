#ifndef FITS_TESTING_H
#define FITS_TESTING_H

#include "fits/errors.h"
#include <catch2/catch.hpp>
#include <string>

namespace fits_testing
{
  bool operator==(const fits::invalid_key& a,
                  const fits::invalid_key& b) noexcept;

  std::string to_string(const fits::invalid_key& exception);

  bool operator==(const fits::invalid_comment& a,
                  const fits::invalid_comment& b) noexcept;

  std::string to_string(const fits::invalid_comment& exception);

  template <typename Exception>
  class exception_matcher: public Catch::MatcherBase<Exception>
  {
  public:
    explicit exception_matcher(Exception expected_exception):
      m_expected_exception {std::move(expected_exception)}
    {
    }

    bool match(const Exception& actual_exception) const override
    {
      m_actual_exception = actual_exception;
      return actual_exception == m_expected_exception;
    }

    [[nodiscard]] std::string describe() const override
    {
      using namespace std::literals::string_literals;
      return "\n  "s.append(fits_testing::to_string(m_actual_exception))
        .append("\n  ")
        .append(fits_testing::to_string(m_expected_exception));
    }

  private:
    const Exception m_expected_exception;

    // store the actual exception so details can be reported
    mutable Exception m_actual_exception {{""}, ""};
  };

  template <typename Exception>
  auto match_exception(Exception expected_exception)
  {
    return fits_testing::exception_matcher<Exception> {
      std::move(expected_exception)};
  }
}  // namespace fits_testing

#endif
