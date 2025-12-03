#pragma once
#include <fstream>
#include <ostream>
#include <functional>
#include <algorithm>

#include "aoc2025.hpp"

namespace Day1 {
    const char* kInputFile("inputs/day1.txt");

    // Forward declarations
    std::ostream& part_1(std::ostream& os);
    std::ostream& part_2(std::ostream& os);

    const aoc2025::Day Day1 {
        1,
        "Secret Entrance",
        {
            &part_1,
            &part_2
        }
    };

    enum class Direction {
        kLeft = -1,
        kRight = 1
    };

    struct DialRotation {
        Direction direction;
        std::uint8_t steps;

        explicit DialRotation(const std::string& token)
            : direction(token.empty() ? throw std::invalid_argument("Empty token") : (token[0] == 'L' ? Direction::kLeft : Direction::kRight)),
              steps(static_cast<std::uint8_t>(std::stoi(token.substr(1)))) {
            if (steps == 0) {
                throw std::invalid_argument("Steps must be greater than zero");
            }
        }
    };

    enum class CountMode {
        kCountPass,
        kCountEnd
    };

    struct Dial {
        std::uint8_t min = 0;
        std::uint8_t max = 99;
        std::uint8_t position = 50;

        std::function<void()> on_end_at_min;
        std::function<void()> on_pass_min;

        void rotate(const DialRotation& rotation) {
            const int new_position = static_cast<int>(position) + static_cast<int>(rotation.direction) * rotation.steps;
            
            if (on_pass_min) {
                switch (rotation.direction) {
                    case Direction::kLeft:
                        for (int pos = position - 1; pos >= new_position && pos >= min; --pos) {
                            if (pos == min) {
                                on_pass_min();
                            }
                        }
                        break;
                    case Direction::kRight:
                        for (int pos = position + 1; pos <= new_position && pos <= max; ++pos) {
                            if (pos == min) {
                                on_pass_min();
                            }
                        }
                        break;
                }
            }
            
            position = static_cast<std::uint8_t>(std::clamp(new_position, static_cast<int>(min), static_cast<int>(max)));
            
            if (on_end_at_min && position == min) {
                on_end_at_min();
            }
        }

        void rotate(const std::vector<DialRotation>& rotations) {
            for (const auto& rotation : rotations) {
                rotate(rotation);
            }
        }
    };

    class DialRotations {
        std::vector<DialRotation> rotations;

    public:
        explicit DialRotations(const char* filename) {
            std::ifstream input_file(filename);
            std::string line;
            while (std::getline(input_file, line)) {
                if (!line.empty()) {
                    rotations.emplace_back(line);
                }
            }
        }

        auto begin() const { return rotations.begin(); }
        auto end() const { return rotations.end(); }
        const std::vector<DialRotation>& get() const { return rotations; }
    };

    class DialCounter {
        Dial& dial;
        int count = 0;
        CountMode mode;

    public:
        DialCounter(Dial& d, CountMode m) : dial(d), mode(m) {
            switch (mode) {
                case CountMode::kCountPass:
                    dial.on_pass_min = [this]() { ++count; };
                    break;
                case CountMode::kCountEnd:
                    dial.on_end_at_min = [this]() { ++count; };
                    break;
            }
        }

        ~DialCounter() {
            switch (mode) {
                case CountMode::kCountPass:
                    dial.on_pass_min = nullptr;
                    break;
                case CountMode::kCountEnd:
                    dial.on_end_at_min = nullptr;
                    break;
            }
        }

        DialCounter(const DialCounter&) = delete;
        DialCounter& operator=(const DialCounter&) = delete;
        DialCounter(DialCounter&&) = delete;
        DialCounter& operator=(DialCounter&&) = delete;

        int get_count() const { return count; }
    };

    std::ostream& part_1(std::ostream& os) {
        DialRotations rotations(kInputFile);
        Dial dial;
        DialCounter counter(dial, CountMode::kCountEnd);
        
        dial.rotate(rotations.get());
        
        os << counter.get_count();
        return os;
    }

    std::ostream& part_2(std::ostream& os) {
        DialRotations rotations(kInputFile);
        Dial dial;
        DialCounter counter(dial, CountMode::kCountPass);
        
        dial.rotate(rotations.get());
        
        os << counter.get_count();
        return os;
    }
};