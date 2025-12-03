#pragma once
#include <ostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

#include "aoc2025.hpp"

namespace Day1 {

    std::ostream& solve_part1(std::ostream& os, const std::string& input);
    std::ostream& solve_part2(std::ostream& os, const std::string& input);

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
            int new_position = static_cast<int>(position) + static_cast<int>(rotation.direction) * rotation.steps;
            
            // Wrap around: 0-99 range
            const int range_size = max - min + 1;
            while (new_position < min) {
                new_position += range_size;
            }
            while (new_position > max) {
                new_position -= range_size;
            }
            
            // Count passes through min (0) during rotation
            if (on_pass_min) {
                const int start_value = static_cast<int>(position);
                for (int i = 1; i <= rotation.steps; ++i) {
                    int pos;
                    if (rotation.direction == Direction::kLeft) {
                        pos = (start_value - i) % range_size;
                        if (pos < 0) {
                            pos += range_size;
                        }
                    } else {
                        pos = (start_value + i) % range_size;
                    }
                    if (pos == min) {
                        on_pass_min();
                    }
                }
            }
            
            position = static_cast<std::uint8_t>(new_position);
            
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
        explicit DialRotations(const std::string& input_string) {
            std::istringstream input_stream(input_string);
            std::string line;
            while (std::getline(input_stream, line)) {
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

    namespace detail {
        inline std::int64_t solve_common(const std::string& input, CountMode mode) {
            DialRotations rotations(input);
            Dial dial;
            DialCounter counter(dial, mode);
            
            dial.rotate(rotations.get());
            
            return counter.get_count();
        }
    }

    inline std::ostream& solve_part1(std::ostream& os, const std::string& input) {        
        return os << detail::solve_common(input, CountMode::kCountEnd);
    }
    
    inline std::ostream& solve_part2(std::ostream& os, const std::string& input) {
        return os << detail::solve_common(input, CountMode::kCountPass);
    }

    extern const aoc2025::Day Day1;

}; // namespace Day1