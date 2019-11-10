#include "fits/errors.h"
#include <catch2/catch.hpp>

SCENARIO("An invalid_key exception can be constructed.")
{
  GIVEN("An empty key string and no bad character index")
  {
    WHEN("An invalid_key exception is constructed")
    {
      fits::invalid_key i {{""}, "the key cannot be empty"};
      THEN("The key is empty.") { CHECK(i.key().empty()); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the key cannot be empty");
      }
    }
  }

  GIVEN("An empty key string and a bad character index")
  {
    WHEN("An invalid_key exception is constructed")
    {
      fits::invalid_key i {{"", 1}, "the key cannot be empty"};
      THEN("The key is empty.") { CHECK(i.key().empty()); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the key cannot be empty");
      }
    }
  }

  GIVEN("An key string and a bad character index")
  {
    WHEN("An invalid_key exception is constructed")
    {
      fits::invalid_key i {{"Key", 1},
                           "the key cannot contain lower case characters"};
      THEN("The key is correct.") { CHECK(i.key() == "key"); }
      AND_THEN("The bad character is the character pointed to by the index.")
      {
        CHECK(i.bad_character() == 'e');
      }
      AND_THEN("The bad character index is correct.")
      {
        CHECK(i.bad_character_index() == 1);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the key cannot contain lower case characters");
      }
    }
  }

  GIVEN("An key string and a bad character index that is out of bounds")
  {
    WHEN("An invalid_key exception is constructed")
    {
      fits::invalid_key i {{"Key", 4},
                           "the key cannot contain lower case characters"};
      THEN("The key is correct.") { CHECK(i.key() == "key"); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the key cannot contain lower case characters");
      }
    }
  }
}

SCENARIO("An invalid_comment exception can be constructed.")
{
  GIVEN("An empty comment string and no bad character index")
  {
    WHEN("An invalid_comment exception is constructed")
    {
      fits::invalid_comment i {{""}, "the comment cannot be empty"};
      THEN("The comment is empty.") { CHECK(i.comment().empty()); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the comment cannot be empty");
      }
    }
  }

  GIVEN("An empty comment string and a bad character index")
  {
    WHEN("An invalid_comment exception is constructed")
    {
      fits::invalid_comment i {{"", 1}, "the comment cannot be empty"};
      THEN("The comment is empty.") { CHECK(i.comment().empty()); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the comment cannot be empty");
      }
    }
  }

  GIVEN("An comment string and a bad character index")
  {
    WHEN("An invalid_comment exception is constructed")
    {
      fits::invalid_comment i {
        {"Key", 1}, "the comment cannot contain lower case characters"};
      THEN("The comment is correct.") { CHECK(i.comment() == "comment"); }
      AND_THEN("The bad character is the character pointed to by the index.")
      {
        CHECK(i.bad_character() == 'e');
      }
      AND_THEN("The bad character index is correct.")
      {
        CHECK(i.bad_character_index() == 1);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the comment cannot contain lower case characters");
      }
    }
  }

  GIVEN("An comment string and a bad character index that is out of bounds")
  {
    WHEN("An invalid_comment exception is constructed")
    {
      fits::invalid_comment i {
        {"Key", 4}, "the comment cannot contain lower case characters"};
      THEN("The comment is correct.") { CHECK(i.comment() == "comment"); }
      AND_THEN("The bad character is the null terminator.")
      {
        CHECK(i.bad_character() == '\0');
      }
      AND_THEN("The bad character index is std::string::npos.")
      {
        CHECK(i.bad_character_index() == std::string::npos);
      }
      AND_THEN("The what message is the one sent to the constructor.")
      {
        CHECK(i.what() == "the comment cannot contain lower case characters");
      }
    }
  }
}
