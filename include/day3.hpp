#pragma once
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <algorithm>
#include <cctype>

#include "aoc2025.hpp"

namespace Day3 {

    // Bank represents one line of input as an array of digits
    class Bank {
        std::vector<std::uint8_t> digits_;

    public:
        // Create a Bank from a string of digits
        // Rejects non-digit characters
        explicit Bank(std::string_view input_string) {
            if (!std::all_of(input_string.begin(), input_string.end(), 
                           [](char ch) { return std::isdigit(static_cast<unsigned char>(ch)); })) {
                throw std::invalid_argument("Input contains non-digit characters");
            }

            digits_.reserve(input_string.length());
            std::transform(input_string.begin(), input_string.end(), 
                         std::back_inserter(digits_),
                         [](char ch) { return static_cast<std::uint8_t>(ch - '0'); });
        }

        explicit Bank(const std::string& input_string) : Bank(std::string_view(input_string)) {}
        explicit Bank(const char* input_string) : Bank(std::string_view(input_string)) {}

        // Get the underlying digits
        const std::vector<std::uint8_t>& get_digits() const { return digits_; }
        std::size_t size() const { return digits_.size(); }
        bool empty() const { return digits_.empty(); }

        // Find the largest 2-digit number made from a pair of digits in order
        // Example: "987654321111111" -> 98
        std::int64_t max_pair() const {
            if (digits_.size() < 2) {
                return 0;
            }

            // Find the index of the max element in range [0, len-1)
            const auto first_range_end = digits_.end() - 1;
            const auto max_it = std::max_element(digits_.begin(), first_range_end);
            const std::size_t max_idx = static_cast<std::size_t>(std::distance(digits_.begin(), max_it));

            // Find the max element in range [maxIdx+1, len)
            const auto second_range_begin = digits_.begin() + static_cast<std::ptrdiff_t>(max_idx + 1);
            const auto max_second_it = std::max_element(second_range_begin, digits_.end());
            const std::size_t max_second_idx = static_cast<std::size_t>(std::distance(digits_.begin(), max_second_it));

            return static_cast<std::int64_t>(digits_[max_idx]) * 10 + 
                   static_cast<std::int64_t>(digits_[max_second_idx]);
        }

        // Returns the n largest digits in order of appearance, as a number
        // Uses recursive approach: for each possible first digit position in range [0, len-n],
        // find the max digit, then recursively solve for remaining (n-1) digits after it
        std::int64_t max_n(std::size_t n) const {
            if (n == 0 || n > digits_.size()) {
                return 0;
            }
            return max_n_helper(n, 0);
        }

    private:
        static constexpr std::int64_t power_of_10(std::size_t power) {
            std::int64_t result = 1;
            for (std::size_t i = 0; i < power; ++i) {
                result *= 10;
            }
            return result;
        }

        std::int64_t max_n_helper(std::size_t n, std::size_t start_idx) const {
            if (n == 0 || start_idx >= digits_.size()) {
                return 0;
            }

            // Need n digits, so first digit can be at most at position len - n
            const std::size_t end_search_pos = digits_.size() - n;
            if (end_search_pos < start_idx) {
                return 0;
            }

            // Find the maximum digit in the valid range using std::max_element
            const auto range_begin = digits_.begin() + static_cast<std::ptrdiff_t>(start_idx);
            const auto range_end = digits_.begin() + static_cast<std::ptrdiff_t>(end_search_pos + 1);
            const auto max_it = std::max_element(range_begin, range_end);
            const std::size_t max_pos = static_cast<std::size_t>(std::distance(digits_.begin(), max_it));
            const std::uint8_t max_digit = *max_it;

            // Use this digit and recursively find the best (n-1) digits after it
            if (n == 1) {
                return static_cast<std::int64_t>(max_digit);
            }

            const std::int64_t remaining = max_n_helper(n - 1, max_pos + 1);
            // Compute 10^(n-1) as integer
            const std::int64_t multiplier = power_of_10(n - 1);

            return static_cast<std::int64_t>(max_digit) * multiplier + remaining;
        }
    };

    namespace detail {
        // Helper function to trim whitespace from a string view
        inline std::string_view trim_whitespace(std::string_view str) {
            const auto first = str.find_first_not_of(" \t\r\n");
            if (first == std::string_view::npos) {
                return {};
            }
            const auto last = str.find_last_not_of(" \t\r\n");
            return str.substr(first, last - first + 1);
        }

        inline std::int64_t solve_part1(const std::string& input) {
            std::int64_t result = 0;
            std::istringstream input_stream(input);
            std::string line;

            while (std::getline(input_stream, line)) {
                const std::string_view trimmed = trim_whitespace(line);
                if (trimmed.empty()) {
                    continue;
                }

                try {
                    Bank bank(trimmed);
                    result += bank.max_pair();
                } catch (const std::exception&) {
                    // Skip invalid lines
                    continue;
                }
            }

            return result;
        }

        inline std::int64_t solve_part2(const std::string& input) {
            std::int64_t result = 0;
            std::istringstream input_stream(input);
            std::string line;

            while (std::getline(input_stream, line)) {
                const std::string_view trimmed = trim_whitespace(line);
                if (trimmed.empty()) {
                    continue;
                }

                try {
                    Bank bank(trimmed);
                    result += bank.max_n(12);
                } catch (const std::exception&) {
                    // Skip invalid lines
                    continue;
                }
            }

            return result;
        }
    }

    inline std::ostream& solve_part1(std::ostream& os, const std::string& input) {
        os << detail::solve_part1(input);
        return os;
    }

    inline std::ostream& solve_part2(std::ostream& os, const std::string& input) {
        os << detail::solve_part2(input);
        return os;
    }

    extern const aoc2025::Day Day3;

} // namespace Day3
