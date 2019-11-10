#include "fits/header.h"
#include <catch2/catch.hpp>

fits::header_entry make_header(const std::string& key)
{
  return fits::header_entry {key, 0};
}

SCENARIO("A header entry can be constructed.")
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

SCENARIO("A header entry can be copied.")
{
  GIVEN("A header entry")
  {
    const fits::header_entry a {"KEY", 10, "a comment"};
    WHEN("A new entry is constructed from the original.")
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
    AND_WHEN("The original entry is assigned to another entry")
    {
      fits::header_entry b {"YEK", 0};
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

SCENARIO("A header entry can be moved.")
{
  GIVEN("A header entry")
  {
    WHEN("A new entry is constructed from the original.")
    {
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      fits::header_entry a {"KEY", 10, "a comment"};
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
    AND_WHEN("The original entry is assigned to another entry")
    {
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      fits::header_entry a {"KEY", 10, "a comment"};
      fits::header_entry b {"YEK", 0};
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
