#include <hello_lib.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("test buzz") {
    int givenNumber = 5;

    std::string actual = fizzBuzz(givenNumber);

    REQUIRE(actual == "Buzz");
}
