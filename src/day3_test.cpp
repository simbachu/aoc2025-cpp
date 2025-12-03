#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "aoc2025.hpp"
#include "day3.hpp"

static std::string run_part(const aoc2025::Day& day, int part, const std::string& input) {
    std::ostringstream oss;
    if (part == 1) {
        day.part1(oss, input);
    } else if (part == 2 && day.part2.has_value()) {
        day.part2.value()(oss, input);
    }
    return oss.str();
}

namespace test_day3 {
    const std::string kSampleInput = "987654321111111\n123456789\n999888777";
    // Line 1: "987654321111111" -> max pair is 98
    // Line 2: "123456789" -> max pair is 89 (max in [0, len-1) is 8 at pos 7, max in [8, len) is 9)
    // Line 3: "999888777" -> max pair is 99
    // Total: 98 + 89 + 99 = 286
    const std::string kSampleOutput1 = "286";
}

namespace day3_tests {

TEST_CASE("Day 3: Bank - Create from Valid Digits", "[day3][component][bank]") {
    // Arrange & Act
    Day3::Bank bank("12345");
    
    // Assert
    REQUIRE(bank.size() == 5);
    REQUIRE(bank.get_digits()[0] == 1);
    REQUIRE(bank.get_digits()[1] == 2);
    REQUIRE(bank.get_digits()[2] == 3);
    REQUIRE(bank.get_digits()[3] == 4);
    REQUIRE(bank.get_digits()[4] == 5);
}

TEST_CASE("Day 3: Bank - Create from Long String", "[day3][component][bank]") {
    // Arrange & Act
    Day3::Bank bank("987654321111111");
    
    // Assert
    REQUIRE(bank.size() == 15);
    REQUIRE(bank.get_digits()[0] == 9);
    REQUIRE(bank.get_digits()[1] == 8);
}

TEST_CASE("Day 3: Bank - Create from String View", "[day3][component][bank]") {
    // Arrange
    std::string input = "12345";
    
    // Act
    Day3::Bank bank(std::string_view(input));
    
    // Assert
    REQUIRE(bank.size() == 5);
}

TEST_CASE("Day 3: Bank - Create from C String", "[day3][component][bank]") {
    // Arrange & Act
    Day3::Bank bank("12345");
    
    // Assert
    REQUIRE(bank.size() == 5);
}

TEST_CASE("Day 3: Bank - Empty String", "[day3][component][bank]") {
    // Arrange & Act
    Day3::Bank bank("");
    
    // Assert
    REQUIRE(bank.empty());
    REQUIRE(bank.size() == 0);
}

TEST_CASE("Day 3: Bank - Invalid Non-Digit Characters", "[day3][component][bank]") {
    // Assert
    REQUIRE_THROWS_AS(Day3::Bank("123abc"), std::invalid_argument);
    REQUIRE_THROWS_AS(Day3::Bank("abc123"), std::invalid_argument);
    REQUIRE_THROWS_AS(Day3::Bank("12-34"), std::invalid_argument);
}

TEST_CASE("Day 3: Bank - MaxPair - Simple Case", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("1234");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 3) is 3 at pos 2, max in [3, 4) is 4 at pos 3
    REQUIRE(result == 34);
}

TEST_CASE("Day 3: Bank - MaxPair - Example from Comments", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("987654321111111");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 14) is 9 at pos 0, max in [1, 15) is 8 at pos 1
    REQUIRE(result == 98);
}

TEST_CASE("Day 3: Bank - MaxPair - All Same Digits", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("1111");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 3) is 1 at pos 0, max in [1, 4) is 1 at pos 1
    REQUIRE(result == 11);
}

TEST_CASE("Day 3: Bank - MaxPair - Increasing Sequence", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("123456789");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 8) is 8 at pos 7, max in [8, 9) is 9 at pos 8
    REQUIRE(result == 89);
}

TEST_CASE("Day 3: Bank - MaxPair - Decreasing Sequence", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("987654321");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 8) is 9 at pos 0, max in [1, 9) is 8 at pos 1
    REQUIRE(result == 98);
}

TEST_CASE("Day 3: Bank - MaxPair - Too Short", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("1");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    REQUIRE(result == 0);
}

TEST_CASE("Day 3: Bank - MaxPair - Exactly Two Digits", "[day3][component][maxpair]") {
    // Arrange
    Day3::Bank bank("42");
    
    // Act
    std::int64_t result = bank.max_pair();
    
    // Assert
    // Max in [0, 1) is 4 at pos 0, max in [1, 2) is 2 at pos 1
    REQUIRE(result == 42);
}

TEST_CASE("Day 3: Bank - Max_N - Single Digit", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("12345");
    
    // Act
    std::int64_t result = bank.max_n(1);
    
    // Assert
    REQUIRE(result == 5);
}

TEST_CASE("Day 3: Bank - Max_N - Two Digits", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("12345");
    
    // Act
    std::int64_t result = bank.max_n(2);
    
    // Assert
    // Should be same as max_pair for n=2
    REQUIRE(result == 45);
}

TEST_CASE("Day 3: Bank - Max_N - All Digits", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("12345");
    
    // Act
    std::int64_t result = bank.max_n(5);
    
    // Assert
    REQUIRE(result == 12345);
}

TEST_CASE("Day 3: Bank - Max_N - Twelve Digits Example", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("98765432101234567890");
    
    // Act
    std::int64_t result = bank.max_n(12);
    
    // Assert
    // Should find the 12 largest digits in order
    REQUIRE(result > 0);
}

TEST_CASE("Day 3: Bank - Max_N - Zero N", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("12345");
    
    // Act
    std::int64_t result = bank.max_n(0);
    
    // Assert
    REQUIRE(result == 0);
}

TEST_CASE("Day 3: Bank - Max_N - N Too Large", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("12345");
    
    // Act
    std::int64_t result = bank.max_n(10);
    
    // Assert
    REQUIRE(result == 0);
}

TEST_CASE("Day 3: Bank - Max_N - Complex Case", "[day3][component][maxn]") {
    // Arrange
    Day3::Bank bank("987654321111111");
    
    // Act
    std::int64_t result = bank.max_n(3);
    
    // Assert
    // Should find 3 largest digits: 9, 8, 7
    REQUIRE(result == 987);
}

TEST_CASE("Day 3: Part 1 - Single Line", "[day3][integration][part1]") {
    // Arrange
    const std::string input = "987654321111111";
    
    // Act
    std::string result = run_part(Day3::Day3, 1, input);
    
    // Assert
    REQUIRE(result == "98");
}

TEST_CASE("Day 3: Part 1 - Multiple Lines", "[day3][integration][part1]") {
    // Arrange
    const std::string input = "1234\n5678";
    
    // Act
    std::string result = run_part(Day3::Day3, 1, input);
    
    // Assert
    // Line 1: max_pair = 34, Line 2: max_pair = 78, Total = 112
    REQUIRE(result == "112");
}

TEST_CASE("Day 3: Part 1 - Sample Input", "[day3][integration][part1]") {
    // Arrange
    const std::string sample_input = test_day3::kSampleInput;
    
    // Act
    std::string result = run_part(Day3::Day3, 1, sample_input);
    
    // Assert
    REQUIRE(result == test_day3::kSampleOutput1);
}

TEST_CASE("Day 3: Part 1 - Empty Lines Skipped", "[day3][integration][part1]") {
    // Arrange
    const std::string input = "1234\n\n5678";
    
    // Act
    std::string result = run_part(Day3::Day3, 1, input);
    
    // Assert
    REQUIRE(result == "112");
}

TEST_CASE("Day 3: Part 1 - Invalid Lines Skipped", "[day3][integration][part1]") {
    // Arrange
    const std::string input = "1234\nabc\n5678";
    
    // Act
    std::string result = run_part(Day3::Day3, 1, input);
    
    // Assert
    // Only valid lines processed: 34 + 78 = 112
    REQUIRE(result == "112");
}

TEST_CASE("Day 3: Part 2 - Single Line", "[day3][integration][part2]") {
    // Arrange
    const std::string input = "12345678901234567890";
    
    // Act
    std::string result = run_part(Day3::Day3, 2, input);
    
    // Assert
    // Should find max 12-digit number
    REQUIRE(result != "0");
}

TEST_CASE("Day 3: Part 2 - Multiple Lines", "[day3][integration][part2]") {
    // Arrange
    const std::string input = "12345678901234567890\n98765432109876543210";
    
    // Act
    std::string result = run_part(Day3::Day3, 2, input);
    
    // Assert
    // Should sum max_n(12) for each line
    REQUIRE(result != "0");
}

TEST_CASE("Day 3: Part 2 - Line Too Short", "[day3][integration][part2]") {
    // Arrange
    const std::string input = "12345";
    
    // Act
    std::string result = run_part(Day3::Day3, 2, input);
    
    // Assert
    // Line too short for 12 digits, should return 0
    REQUIRE(result == "0");
}

} // namespace day3_tests
