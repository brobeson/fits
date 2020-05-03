#define CATCH_CONFIG_MAIN
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

SCENARIO("Invalid keys can be used to try to construct a keyword record.")
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
    AND_WHEN("A keyword record is constructed with the key, a value, "
             "and a comment")
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

SCENARIO("Invalid comments can be used to try to construct a keyword record.")
{
  struct test_case
  {
    std::string given_label;
    std::string comment;
    fits::invalid_comment exception;
  };

  // clang-format off
  // NOLINTNEXTLINE(google-build-using-namespace)
  const auto c{GENERATE(values({
    test_case{"ASCII character 0"s,   std::string{1, 0},   {{std::string{1, 0},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 1"s,   std::string{1, 1},   {{std::string{1, 1},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 2"s,   std::string{1, 2},   {{std::string{1, 2},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 3"s,   std::string{1, 3},   {{std::string{1, 3},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 4"s,   std::string{1, 4},   {{std::string{1, 4},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 5"s,   std::string{1, 5},   {{std::string{1, 5},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 6"s,   std::string{1, 6},   {{std::string{1, 6},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 7"s,   std::string{1, 7},   {{std::string{1, 7},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 8"s,   std::string{1, 8},   {{std::string{1, 8},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 9"s,   std::string{1, 9},   {{std::string{1, 9},   0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 10"s,  std::string{1, 10},  {{std::string{1, 10},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 11"s,  std::string{1, 11},  {{std::string{1, 11},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 12"s,  std::string{1, 12},  {{std::string{1, 12},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 13"s,  std::string{1, 13},  {{std::string{1, 13},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 14"s,  std::string{1, 14},  {{std::string{1, 14},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 15"s,  std::string{1, 15},  {{std::string{1, 15},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 16"s,  std::string{1, 16},  {{std::string{1, 16},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 17"s,  std::string{1, 17},  {{std::string{1, 17},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 18"s,  std::string{1, 18},  {{std::string{1, 18},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 19"s,  std::string{1, 19},  {{std::string{1, 19},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 20"s,  std::string{1, 20},  {{std::string{1, 20},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 21"s,  std::string{1, 21},  {{std::string{1, 21},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 22"s,  std::string{1, 22},  {{std::string{1, 22},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 23"s,  std::string{1, 23},  {{std::string{1, 23},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 24"s,  std::string{1, 24},  {{std::string{1, 24},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 25"s,  std::string{1, 25},  {{std::string{1, 25},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 26"s,  std::string{1, 26},  {{std::string{1, 26},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 27"s,  std::string{1, 27},  {{std::string{1, 27},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 28"s,  std::string{1, 28},  {{std::string{1, 28},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 29"s,  std::string{1, 29},  {{std::string{1, 29},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 30"s,  std::string{1, 30},  {{std::string{1, 30},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 31"s,  std::string{1, 31},  {{std::string{1, 31},  0}, "FITS keyword record comment has an invalid character."s}},
    test_case{"ASCII character 127"s, std::string{1, 127}, {{std::string{1, 127}, 0}, "FITS keyword record comment has an invalid character."s}}}))};
  // clang-format on

  GIVEN(c.given_label)
  {
    WHEN("A keyword record is constructed with a key and the comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record("KEY", c.comment),
          fits::invalid_comment,
          fits_testing::match_exception<fits::invalid_comment>(c.exception));
      }
    }
    AND_WHEN("A keyword record is constructed with a key, a value, and "
             "the comment")
    {
      THEN("The constructor throws.")
      {
        CHECK_THROWS_MATCHES(
          fits_testing::make_record("KEY", c.comment, 0),
          fits::invalid_comment,
          fits_testing::match_exception<fits::invalid_comment>(c.exception));
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
