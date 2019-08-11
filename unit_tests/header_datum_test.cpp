#include "fits/header_block.h"
#include <catch2/catch.hpp>

fits::header_datum make_header(const std::string& key)
{
  return fits::header_datum {key, 0};
}

SCENARIO("A header datum can be constructed.")
{
  WHEN("The key is empty")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_AS(make_header(""), fits::invalid_key);
    }
  }
  AND_WHEN("The key exceeds 8 characters")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_AS(make_header("012345678"), fits::invalid_key);
    }
  }
  AND_WHEN("The key contains invalid characters")
  {
    THEN("The constructor throws.")
    {
      CHECK_THROWS_AS(make_header("FOOBAr"), fits::invalid_key);
    }
  }
}

SCENARIO("A header datum can be copied.")
{
  GIVEN("A header datum")
  {
    const fits::header_datum a {"KEY", 10, "a comment"};
    WHEN("A new datum is constructed from the original.")
    {
      const auto b {a};  // NOLINT(performance-unnecessary-copy-initialization)
      THEN("The keys are the same") { CHECK(a.key() == b.key()); }
      AND_THEN("The values are the same")
      {
        CHECK(a.value<int>() == b.value<int>());
      }
      AND_THEN("The comments are the same")
      {
        CHECK(a.comment() == b.comment());
      }
    }
    AND_WHEN("The original datum is assigned to another datum")
    {
      fits::header_datum b {"YEK", 0};
      b = a;
      THEN("The keys are the same") { CHECK(a.key() == b.key()); }
      AND_THEN("The values are the same")
      {
        CHECK(a.value<int>() == b.value<int>());
      }
      AND_THEN("The comments are the same")
      {
        CHECK(a.comment() == b.comment());
      }
    }
  }
}

SCENARIO("A header datum can be moved.")
{
  GIVEN("A header datum")
  {
    WHEN("A new datum is constructed from the original.")
    {
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      fits::header_datum a {"KEY", 10, "a comment"};
      const auto b {std::move(a)};
      THEN("The new key is the same as the original")
      {
        CHECK(b.key() == "KEY");
      }
      AND_THEN("The new value is the same as the original")
      {
        CHECK(b.value<int>() == 10);
      }
      AND_THEN("The new comment is the same as the original")
      {
        CHECK(b.comment() == "a comment");
      }
    }
    AND_WHEN("The original datum is assigned to another datum")
    {
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      fits::header_datum a {"KEY", 10, "a comment"};
      fits::header_datum b {"YEK", 0};
      b = std::move(a);
      THEN("The new key is the same as the original")
      {
        CHECK(b.key() == "KEY");
      }
      AND_THEN("The new value is the same as the original")
      {
        CHECK(b.value<int>() == 10);
      }
      AND_THEN("The new comment is the same as the original")
      {
        CHECK(b.comment() == "a comment");
      }
    }
  }
}

SCENARIO("Header data can be parse from a list of bytes.")
{
  GIVEN("An empty list of bytes.")
  {
    const fits::raw_block empty;
    WHEN("The list is parsed.")
    {
      THEN("An exception is thrown.")
      {
        CHECK_THROWS_AS(fits::parse_header_block(empty),
                        fits::invalid_header_block);
      }
    }
  }
}
