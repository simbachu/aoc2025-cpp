#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "aoc2025.hpp"
#include "day1.hpp"

static std::string run_part(const aoc2025::Day& day, int part, const std::string& input) {
    std::ostringstream oss;
    if (part == 1) {
        day.part1(oss, input);
    } else if (part == 2 && day.part2.has_value()) {
        day.part2.value()(oss, input);
    }
    return oss.str();
}

namespace test_day1 {
    const std::string kSampleInput = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82";
    const std::string kSampleOutput1 = "3";
    const std::string kSampleOutput2 = "6";
}

namespace day1_tests {

TEST_CASE("Day 1: DialRotation - Parse Left", "[day1][component][dialrotation]") {
    // Arrange
    Day1::DialRotation rotation("L10");
    
    // Assert
    REQUIRE(rotation.direction == Day1::Direction::kLeft);
    REQUIRE(rotation.steps == 10);
}

TEST_CASE("Day 1: DialRotation - Parse Right", "[day1][component][dialrotation]") {
    // Arrange
    Day1::DialRotation rotation("R5");
    
    // Assert
    REQUIRE(rotation.direction == Day1::Direction::kRight);
    REQUIRE(rotation.steps == 5);
}

TEST_CASE("Day 1: DialRotation - Parse Large Steps", "[day1][component][dialrotation]") {
    // Arrange
    Day1::DialRotation rotation("L99");
    
    // Assert
    REQUIRE(rotation.direction == Day1::Direction::kLeft);
    REQUIRE(rotation.steps == 99);
}

TEST_CASE("Day 1: DialRotation - Invalid Empty Token", "[day1][component][dialrotation]") {
    // Assert
    REQUIRE_THROWS_AS(Day1::DialRotation(""), std::invalid_argument);
}

TEST_CASE("Day 1: DialRotation - Invalid Zero Steps", "[day1][component][dialrotation]") {
    // Assert
    REQUIRE_THROWS_AS(Day1::DialRotation("L0"), std::invalid_argument);
}

TEST_CASE("Day 1: Dial - Rotate Right", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    
    // Act
    Day1::DialRotation rotation("R10");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 60);
}

TEST_CASE("Day 1: Dial - Rotate Left", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    
    // Act
    Day1::DialRotation rotation("L20");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 30);
}

TEST_CASE("Day 1: Dial - Wrap at Max", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 95;
    
    // Act
    Day1::DialRotation rotation("R10");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 5);
}

TEST_CASE("Day 1: Dial - Wrap at Min", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 5;
    
    // Act
    Day1::DialRotation rotation("L10");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 95);
}

TEST_CASE("Day 1: Dial - Rotate Multiple", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    std::vector<Day1::DialRotation> rotations = {
        Day1::DialRotation("R10"),
        Day1::DialRotation("L5"),
        Day1::DialRotation("R3")
    };
    
    // Act
    dial.rotate(rotations);
    
    // Assert
    REQUIRE(dial.position == 58);
}

TEST_CASE("Day 1: Dial - Wrap from 0 Left", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 0;
    
    // Act
    Day1::DialRotation rotation("L1");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 99);
}

TEST_CASE("Day 1: Dial - Wrap from 99 Right", "[day1][component][dial]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 99;
    
    // Act
    Day1::DialRotation rotation("R1");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(dial.position == 0);
}

TEST_CASE("Day 1: DialCounter - Count End at Min", "[day1][component][dialcounter]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 5;
    Day1::DialCounter counter(dial, Day1::CountMode::kCountEnd);
    
    // Act
    Day1::DialRotation rotation("L5");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(counter.get_count() == 1);
}

TEST_CASE("Day 1: DialCounter - Count End Not Triggered", "[day1][component][dialcounter]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 50;
    Day1::DialCounter counter(dial, Day1::CountMode::kCountEnd);
    
    // Act
    Day1::DialRotation rotation("R10");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(counter.get_count() == 0);
}

TEST_CASE("Day 1: DialCounter - Count Pass Mode", "[day1][component][dialcounter]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 50;
    Day1::DialCounter counter(dial, Day1::CountMode::kCountPass);
    
    // Act
    Day1::DialRotation rotation("L50");
    dial.rotate(rotation);
    
    // Assert
    REQUIRE(counter.get_count() == 1);
}

TEST_CASE("Day 1: DialCounter - Multiple Rotations Count End", "[day1][component][dialcounter]") {
    // Arrange
    Day1::Dial dial;
    dial.position = 50;
    Day1::DialCounter counter(dial, Day1::CountMode::kCountEnd);
    std::vector<Day1::DialRotation> rotations = {
        Day1::DialRotation("L50"),
        Day1::DialRotation("R10"),
        Day1::DialRotation("L10")
    };
    
    // Act
    dial.rotate(rotations);
    
    // Assert
    REQUIRE(counter.get_count() == 2);
}

TEST_CASE("Day 1: Part 1 - Sample Input", "[day1][integration][part1]") {
    // Arrange
    const std::string sample_input = test_day1::kSampleInput;
    
    // Act
    std::string result = run_part(Day1::Day1, 1, sample_input);
    
    // Assert
    REQUIRE(result == test_day1::kSampleOutput1);
}

TEST_CASE("Day 1: Part 2 - Sample Input", "[day1][integration][part2]") {
    // Arrange
    const std::string sample_input = test_day1::kSampleInput;
    
    // Act
    std::string result = run_part(Day1::Day1, 2, sample_input);
    
    // Assert
    REQUIRE(result == test_day1::kSampleOutput2);
}

} // namespace day1_tests
