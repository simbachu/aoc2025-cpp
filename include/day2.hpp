#pragma once
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <optional>
#include <functional>
#include <algorithm>

#include "aoc2025.hpp"

namespace Day2 {

    struct Range {
        std::int64_t start;
        std::int64_t end;

        explicit Range(const std::string& range_string) 
            : Range(std::string_view(range_string)) {}
        
        explicit Range(const char* range_string) 
            : Range(std::string_view(range_string)) {}

    private:
        explicit Range(std::string_view range_string) {
            const size_t dash_pos = range_string.find('-');
            if (dash_pos == std::string_view::npos || dash_pos == 0 || dash_pos == range_string.length() - 1) {
                throw std::invalid_argument("Invalid range format: " + std::string(range_string));
            }
            
            const std::string_view start_str = range_string.substr(0, dash_pos);
            const std::string_view end_str = range_string.substr(dash_pos + 1);
            
            try {
                start = std::stoll(std::string(start_str));
                end = std::stoll(std::string(end_str));
            } catch (const std::exception&) {
                throw std::invalid_argument("Invalid range numbers: " + std::string(range_string));
            }
            
            if (start > end) {
                throw std::invalid_argument("Range start greater than end: " + std::string(range_string));
            }
        }
    };

    // Take number and return number if it consists of two groups of equal digits,
    // otherwise return empty optional
    inline std::optional<std::int64_t> Part1IdOfConcern(std::int64_t number) {
        const std::string digits = std::to_string(number);
        if (digits.length() % 2 != 0) {
            return std::nullopt;
        }
        
        const size_t mid = digits.length() / 2;
        if (digits.substr(0, mid) == digits.substr(mid)) {
            return number;
        }
        return std::nullopt;
    }

    // Return number if it contains only repeating parts, otherwise return empty optional
    // Checks if the number is composed of a repeating pattern
    inline std::optional<std::int64_t> Part2IdOfConcern(std::int64_t number) {
        const std::string digits = std::to_string(number);
        const size_t length = digits.length();
        
        // Try all possible segment lengths that divide evenly into the total length
        for (size_t segment_len = 1; segment_len <= length / 2; ++segment_len) {
            if (length % segment_len != 0) {
                continue;
            }
            const std::string_view segment = std::string_view(digits).substr(0, segment_len);
            const size_t repetitions = length / segment_len;
            
            bool matches = true;
            for (size_t rep = 1; rep < repetitions && matches; ++rep) {
                const size_t offset = rep * segment_len;
                const std::string_view current_segment = std::string_view(digits).substr(offset, segment_len);
                if (segment != current_segment) {
                    matches = false;
                }
            }
            
            if (matches) {
                return number;
            }
        }
        return std::nullopt;
    }

    class Ranges {
        std::vector<Range> ranges_;

    public:
        explicit Ranges(const std::string& input_string) {
            ranges_.reserve(std::count(input_string.begin(), input_string.end(), ',') + 1);
            
            std::istringstream input_stream(input_string);
            std::string token;
            
            while (std::getline(input_stream, token, ',')) {
                if (!token.empty()) {
                    ranges_.emplace_back(token);
                }
            }
        }

        auto begin() const { return ranges_.begin(); }
        auto end() const { return ranges_.end(); }
        const std::vector<Range>& get() const { return ranges_; }
    };

    namespace detail {
        inline std::int64_t solve_common(
            const std::string& input,
            std::function<std::optional<std::int64_t>(std::int64_t)> id_checker) {
            Ranges ranges(input);
            std::int64_t result = 0;
            
            for (const auto& range : ranges.get()) {
                for (std::int64_t i = range.start; i <= range.end; ++i) {
                    if (auto id = id_checker(i)) {
                        result += *id;
                    }
                }
            }
            
            return result;
        }
    }

    inline std::ostream& solve_part1(std::ostream& os, const std::string& input) {
        os << detail::solve_common(input, Part1IdOfConcern);
        return os;
    }

    inline std::ostream& solve_part2(std::ostream& os, const std::string& input) {
        os << detail::solve_common(input, Part2IdOfConcern);
        return os;
    }

    extern const aoc2025::Day Day2;

} // namespace Day2

