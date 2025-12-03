#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "aoc2025.hpp"
#include "day2.hpp"

static std::string run_part(const aoc2025::Day& day, int part, const std::string& input) {
    std::ostringstream oss;
    if (part == 1) {
        day.part1(oss, input);
    } else if (part == 2 && day.part2.has_value()) {
        day.part2.value()(oss, input);
    }
    return oss.str();
}

namespace test_day2 {
    const std::string kSampleInput = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";
    const std::string kSampleOutput = "1227775554";
}

namespace day2_tests {

TEST_CASE("Day 2: Range - Parse Simple Range", "[day2][component][range]") {
    // Arrange & Act
    Day2::Range range("11-22");
    
    // Assert
    REQUIRE(range.start == 11);
    REQUIRE(range.end == 22);
}

TEST_CASE("Day 2: Range - Parse Large Range", "[day2][component][range]") {
    // Arrange & Act
    Day2::Range range("998-1012");
    
    // Assert
    REQUIRE(range.start == 998);
    REQUIRE(range.end == 1012);
}

TEST_CASE("Day 2: Range - Parse Very Large Range", "[day2][component][range]") {
    // Arrange & Act
    Day2::Range range("1188511880-1188511890");
    
    // Assert
    REQUIRE(range.start == 1188511880);
    REQUIRE(range.end == 1188511890);
}

TEST_CASE("Day 2: Range - Invalid Format Missing Dash", "[day2][component][range]") {
    // Assert
    REQUIRE_THROWS_AS(Day2::Range("1122"), std::invalid_argument);
}

TEST_CASE("Day 2: Range - Invalid Format No Start", "[day2][component][range]") {
    // Assert
    REQUIRE_THROWS_AS(Day2::Range("-22"), std::invalid_argument);
}

TEST_CASE("Day 2: Range - Invalid Format No End", "[day2][component][range]") {
    // Assert
    REQUIRE_THROWS_AS(Day2::Range("11-"), std::invalid_argument);
}

TEST_CASE("Day 2: Range - Invalid Numbers", "[day2][component][range]") {
    // Assert
    REQUIRE_THROWS_AS(Day2::Range("abc-def"), std::invalid_argument);
}

TEST_CASE("Day 2: Range - Start Greater Than End", "[day2][component][range]") {
    // Assert
    REQUIRE_THROWS_AS(Day2::Range("22-11"), std::invalid_argument);
}

TEST_CASE("Day 2: Part1IdOfConcern - Valid Two Digit Number", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(11);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 11);
}

TEST_CASE("Day 2: Part1IdOfConcern - Valid Four Digit Number", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(1111);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 1111);
}

TEST_CASE("Day 2: Part1IdOfConcern - Valid Six Digit Number", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(111111);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 111111);
}

TEST_CASE("Day 2: Part1IdOfConcern - Valid Eight Digit Number", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(12341234);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 12341234);
}

TEST_CASE("Day 2: Part1IdOfConcern - Invalid Odd Digits", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(123);
    
    // Assert
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Day 2: Part1IdOfConcern - Invalid Non-Matching Halves", "[day2][component][part1]") {
    // Arrange & Act
    auto result = Day2::Part1IdOfConcern(1234);
    
    // Assert
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Two Digit Number", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(11);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 11);
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Three Digit Number", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(111);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 111);
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Four Digit Number", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(1111);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 1111);
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Repeating Pattern", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(123123123);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 123123123);
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Eight Digit Number", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(12341234);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 12341234);
}

TEST_CASE("Day 2: Part2IdOfConcern - Valid Six Digit Number", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(111111);
    
    // Assert
    REQUIRE(result.has_value());
    REQUIRE(*result == 111111);
}

TEST_CASE("Day 2: Part2IdOfConcern - Invalid Non-Repeating", "[day2][component][part2]") {
    // Arrange & Act
    auto result = Day2::Part2IdOfConcern(1234);
    
    // Assert
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Day 2: Ranges - Parse Single Range", "[day2][component][ranges]") {
    // Arrange & Act
    Day2::Ranges ranges("11-22");
    
    // Assert
    REQUIRE(ranges.get().size() == 1);
    REQUIRE(ranges.get()[0].start == 11);
    REQUIRE(ranges.get()[0].end == 22);
}

TEST_CASE("Day 2: Ranges - Parse Multiple Ranges", "[day2][component][ranges]") {
    // Arrange & Act
    Day2::Ranges ranges("11-22,95-115,998-1012");
    
    // Assert
    REQUIRE(ranges.get().size() == 3);
    REQUIRE(ranges.get()[0].start == 11);
    REQUIRE(ranges.get()[0].end == 22);
    REQUIRE(ranges.get()[1].start == 95);
    REQUIRE(ranges.get()[1].end == 115);
    REQUIRE(ranges.get()[2].start == 998);
    REQUIRE(ranges.get()[2].end == 1012);
}

TEST_CASE("Day 2: Ranges - Range-Based For Loop", "[day2][component][ranges]") {
    // Arrange
    Day2::Ranges ranges("11-22,95-115");
    int count = 0;
    
    // Act
    for ([[maybe_unused]] const auto& range : ranges) {
        ++count;
    }
    
    // Assert
    REQUIRE(count == 2);
}

TEST_CASE("Day 2: Part 1 - Single Valid Number", "[day2][integration][part1]") {
    // Arrange
    const std::string input = "11-11";
    
    // Act
    std::string result = run_part(Day2::Day2, 1, input);
    
    // Assert
    REQUIRE(result == "11");
}

TEST_CASE("Day 2: Part 1 - Range With Multiple Valid Numbers", "[day2][integration][part1]") {
    // Arrange
    const std::string input = "11-22"; // 11 and 22 should sum to 33
    
    // Act
    std::string result = run_part(Day2::Day2, 1, input);
    
    // Assert
    REQUIRE(result == "33");
}

TEST_CASE("Day 2: Part 1 - Sample Input", "[day2][integration][part1]") {
    // Arrange
    const std::string sample_input = test_day2::kSampleInput;
    
    // Act
    std::string result = run_part(Day2::Day2, 1, sample_input);
    
    // Assert
    REQUIRE(result == test_day2::kSampleOutput);
}

TEST_CASE("Day 2: Part 2 - Single Valid Number", "[day2][integration][part2]") {
    // Arrange
    const std::string input = "11-11";
    
    // Act
    std::string result = run_part(Day2::Day2, 2, input);
    
    // Assert
    REQUIRE(result == "11");
}

TEST_CASE("Day 2: Part 2 - Range With Repeating Pattern", "[day2][integration][part2]") {
    // Arrange
    const std::string input = "111-111";
    
    // Act
    std::string result = run_part(Day2::Day2, 2, input);
    
    // Assert
    REQUIRE(result == "111");
}

TEST_CASE("Day 2: Part 2 - Range With Multiple Valid Numbers", "[day2][integration][part2]") {
    // Arrange
    const std::string input = "11-22";
    
    // Act
    std::string result = run_part(Day2::Day2, 2, input);
    
    // Assert
    REQUIRE(result == "33");
}

TEST_CASE("Day 2: Part 2 - Range With Repeating Pattern Numbers", "[day2][integration][part2]") {
    // Arrange
    const std::string input = "111-222";
    
    // Act
    std::string result = run_part(Day2::Day2, 2, input);
    
    // Assert
    REQUIRE(result == "333");
}

} // namespace day2_tests

