#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include "aoc2025.hpp"

// Forward declarations for day registrations
namespace Day1 {
    extern const aoc2025::Day Day1;
}
namespace Day2 {
    extern const aoc2025::Day Day2;
}
namespace Day3 {
    extern const aoc2025::Day Day3;
}

int main(int argc, char* argv[]) {
    // Register all days
    aoc2025::register_day(Day1::Day1);
    aoc2025::register_day(Day2::Day2);
    aoc2025::register_day(Day3::Day3);
    
    // Determine which days to run
    std::vector<int> days_to_run;
    
    if (argc > 1) {
        // Run specific day from command line argument
        int day_number = std::atoi(argv[1]);
        if (day_number > 0) {
            days_to_run.push_back(day_number);
        } else {
            std::cerr << "Invalid day number: " << argv[1] << '\n';
            return 1;
        }
    } else {
        // Run all registered days
        for (const auto& [day_num, _] : aoc2025::days) {
            days_to_run.push_back(day_num);
        }
    }
    
    // Run each day
    for (int day_number : days_to_run) {
        auto it = aoc2025::days.find(day_number);
        if (it == aoc2025::days.end()) {
            std::cerr << "Day " << day_number << " not implemented yet\n";
            continue;
        }
        
        const auto& day = it->second;
        
        // Check if input file exists
        if (!day.has_input()) {
            std::cerr << "Error reading file " << day.get_input_file() << ": file not found\n";
            continue;
        }
        
        // Read input
        std::string input = day.read_input();
        
        // Run parts
        std::cout << "Day " << day_number << ":\n";
        
        // Part 1
        std::ostringstream part1_oss;
        day.part1(part1_oss, input);
        std::cout << "  Part 1: " << part1_oss.str() << '\n';
        
        // Part 2 (if unlocked)
        if (day.part2.has_value()) {
            std::ostringstream part2_oss;
            day.part2.value()(part2_oss, input);
            std::cout << "  Part 2: " << part2_oss.str() << '\n';
        } else {
            std::cout << "  Part 2: Not yet unlocked\n";
        }
        std::cout << '\n';
    }
    
    return 0;
}