#include "fits/header.h"
#include "fits_testing.h"
#include <catch2/catch.hpp>

using namespace std::literals::string_literals;

namespace fits_testing
{
  namespace
  {
    template <typename... Ts>
    fits::keyword_record make_record(Ts... arguments)
    {
      return fits::keyword_record(arguments...);
    }
  }  // namespace
}  // namespace fits_testing

SCENARIO("Invalid data can be used to try to construct a keyword record.")
{
  struct test_case
  {
    std::string given_label;
    std::string key;
    std::string comment;
    int value;
    fits::invalid_key exception;
  };

  // clang-format off
  // NOLINTNEXTLINE(google-build-using-namespace)
  const auto c{GENERATE(values({
    test_case{"An empty key"s, ""s, "a comment"s, 0, {{"", std::string::npos}, "FITS header keys may not be empty."s}},
    test_case{"A key that is too long"s, "THIS_KEY_IS_TOO_LONG"s, "a comment"s, 0, {{"THIS_KEY_IS_TOO_LONG", 8}, "FITS header keys may not exceed eight characters."s}},
    test_case{"A key with a lower case character"s, "Key"s, "a comment"s, 0, {{"Key"s, 1}, "FITS header key has an invalid character."s}},
    test_case{"A key with a space"s, "KEY "s, "a comment"s, 0, {{"KEY "s, 3}, "FITS header key has an invalid character."s}},
    test_case{"A key with a period"s, "Key."s, "a comment"s, 0, {{"KEY."s, 3}, "FITS header key has an invalid character."s}}}))};
  // clang-format on

  GIVEN(c.given_label)
  {
    WHEN("A keyword record is constructed with just the key")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits::keyword_record {c.key},
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(c.exception));
      }
    }
    AND_WHEN("A keyword record is constructed with the key and a comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record(c.key, c.comment),
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(c.exception));
      }
    }
    AND_WHEN(
      "A keyword record is constructed with the key, a value, and a comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record(c.key, c.comment, c.value),
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(c.exception));
      }
    }
  }
}

SCENARIO("A keyword record can be copied.")
{
  GIVEN("A keyword record")
  {
    const fits::keyword_record ground_truth {"KEY", "a comment", 10};
    WHEN("A new keyword record is constructed from the original.")
    {
      // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
      const auto copied {ground_truth};
      THEN("The records are the same") { CHECK(ground_truth == copied); }
    }
    AND_WHEN("The original entry is assigned to another entry")
    {
      fits::keyword_record copied {"YEK", "not a comment", 0};
      copied = ground_truth;
      THEN("The records are the same") { CHECK(ground_truth == copied); }
    }
  }
}

SCENARIO("A keyword record can be moved.")
{
  GIVEN("A keyword record")
  {
    const fits::keyword_record ground_truth {"KEY", "a comment", 10};
    auto movable_copy {ground_truth};
    WHEN("A new keyword record is constructed from the original.")
    {
      const auto moved {std::move(movable_copy)};
      THEN("The records are the same") { CHECK(ground_truth == moved); }
    }
    AND_WHEN("The original entry is assigned to another entry")
    {
      movable_copy = ground_truth;
      fits::keyword_record moved {"YEK", "not a comment", 0};
      moved = std::move(movable_copy);
      THEN("The records are the same") { CHECK(ground_truth == moved); }
    }
  }
}
