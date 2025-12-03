#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <map>
#include <optional>

namespace aoc2025 {
    struct Day {
        int day_number;
        std::string title;
        
        using PartFunction = std::ostream&(*)(std::ostream&, const std::string&);
        PartFunction part1;
        std::optional<PartFunction> part2; // Optional for unlocked parts
        
        // Get input file path for this day
        std::string get_input_file() const {
            return "day" + std::to_string(day_number) + "/data.txt";
        }
        
        // Check if input file exists
        bool has_input() const {
            return std::filesystem::exists(get_input_file());
        }
        
        // Read input file content
        std::string read_input() const {
            std::ifstream file(get_input_file());
            if (!file.is_open()) {
                return "";
            }
            std::ostringstream oss;
            oss << file.rdbuf();
            return oss.str();
        }
    };
    
    extern std::map<int, Day> days;
    
    // Register a day
    inline void register_day(const Day& day) {
        days[day.day_number] = day;
    }
}