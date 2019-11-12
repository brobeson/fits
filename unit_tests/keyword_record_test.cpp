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

// SCENARIO("Invalid data can be used to try to construct a keyword record.")
//{
/*
GIVEN("An empty key")
{
  WHEN("A keyword record is constructed with just the key")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits::keyword_record {""},
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{""s, std::string::npos}, "FITS header keys may not be empty."s}));
    }
  }
  AND_WHEN("A keyword record is constructed with the key and a comment")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits_testing::make_record(""s, "a comment"s),
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{""s, std::string::npos}, "FITS header keys may not be empty."s}));
    }
  }
  AND_WHEN(
    "A keyword record is constructed with the key, a value, and a comment")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits_testing::make_record(""s, "a comment"s, 0),
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{""s, std::string::npos}, "FITS header keys may not be empty."s}));
    }
  }
}

GIVEN("A key that is too long")
{
  const std::string key {"THIS_KEY_IS_TOO_LONG"};
  WHEN("A keyword record is constructed with just the key")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits::keyword_record {key},
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{key, 8}, "FITS header keys may not exceed eight characters."s}));
    }
  }
  AND_WHEN("A keyword record is constructed with the key and a comment")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits_testing::make_record(key, "a comment"s),
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{key, 8}, "FITS header keys may not exceed eight characters."s}));
    }
  }
  AND_WHEN(
    "A keyword record is constructed with the key, a value, and a comment")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_MATCHES(
        fits_testing::make_record(key, "a comment"s, 0),
        fits::invalid_key,
        fits_testing::match_exception<fits::invalid_key>(
          {{key, 8}, "FITS header keys may not exceed eight characters."s}));
    }
  }
}
*/

/*
  GIVEN("A key with lower case characters")
  {
    // The GENERATE() macro (from Catch2) must have 'using namespace ...'. I
    // can't do anything about that, so tell clang-tidy to ignore it.
    // NOLINTNEXTLINE(google-build-using-namespace)
    const auto key {GENERATE("Key"s, "K y"s, "K.y"s)};
    WHEN("A keyword record is constructed with just the key")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits::keyword_record {key},
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(
            {{key, 1}, "FITS header key has an invalid character."s}));
      }
    }
    AND_WHEN("A keyword record is constructed with the key and a comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record(key, "a comment"s),
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(
            {{key, 1}, "FITS header key has an invalid character."s}));
      }
    }
    AND_WHEN(
      "A keyword record is constructed with the key, a value, and a comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record(key, "a comment"s, 0),
          fits::invalid_key,
          fits_testing::match_exception<fits::invalid_key>(
            {{key, 1}, "FITS header key has an invalid character."s}));
      }
    }
  }
  */
//}

// SCENARIO("A keyword record can be copied.")
//{
//  GIVEN("A keyword record")
//  {
//    const fits::keyword_record a {"KEY", 10, "a comment"};
//    WHEN("A new entry is constructed from the original.")
//    {
//      const auto b {a};  //
//      NOLINT(performance-unnecessary-copy-initialization) THEN("The keys are
//      the same") { CHECK(a.key() == b.key()); } AND_THEN("The values are the
//      same")
//      {
//        CHECK(a.value<int>() == b.value<int>());
//      }
//      AND_THEN("The comments are the same")
//      {
//        CHECK(a.comment() == b.comment());
//      }
//    }
//    AND_WHEN("The original entry is assigned to another entry")
//    {
//      fits::keyword_record b {"YEK", 0};
//      b = a;
//      THEN("The keys are the same") { CHECK(a.key() == b.key()); }
//      AND_THEN("The values are the same")
//      {
//        CHECK(a.value<int>() == b.value<int>());
//      }
//      AND_THEN("The comments are the same")
//      {
//        CHECK(a.comment() == b.comment());
//      }
//    }
//  }
//}

// SCENARIO("A keyword record can be moved.")
//{
//  GIVEN("A keyword record")
//  {
//    WHEN("A new entry is constructed from the original.")
//    {
//      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
//      fits::keyword_record a {"KEY", 10, "a comment"};
//      const auto b {std::move(a)};
//      THEN("The new key is the same as the original")
//      {
//        CHECK(b.key() == "KEY");
//      }
//      AND_THEN("The new value is the same as the original")
//      {
//        CHECK(b.value<int>() == 10);
//      }
//      AND_THEN("The new comment is the same as the original")
//      {
//        CHECK(b.comment() == "a comment");
//      }
//    }
//    AND_WHEN("The original entry is assigned to another entry")
//    {
//      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
//      fits::keyword_record a {"KEY", 10, "a comment"};
//      fits::keyword_record b {"YEK", 0};
//      b = std::move(a);
//      THEN("The new key is the same as the original")
//      {
//        CHECK(b.key() == "KEY");
//      }
//      AND_THEN("The new value is the same as the original")
//      {
//        CHECK(b.value<int>() == 10);
//      }
//      AND_THEN("The new comment is the same as the original")
//      {
//        CHECK(b.comment() == "a comment");
//      }
//    }
//  }
//}
