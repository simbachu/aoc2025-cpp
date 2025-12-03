#pragma once

#include <vector>
#include <string>
#include <ostream>

namespace aoc2025 {
    struct Day {
        int day_number;
        std::string title;
        // array of function pointers for parts of the day's challenge
        using PartFunction = std::ostream&(*)(std::ostream&); // function type should be a printable function that has << std::ostream& as parameter
        std::vector<PartFunction> parts;
    };
    std::vector<Day> days;
}