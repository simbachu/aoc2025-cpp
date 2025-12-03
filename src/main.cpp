#include <vector>
#include <iostream>
#include "aoc2025.hpp"


int main (){
    for (const auto& day : aoc2025::days) {
        std::cout << "Day " << day.day_number << ": " << day.title << '\n';
        for (size_t i = 0; i < day.parts.size(); ++i) {
            std::cout << "  Part " << (i + 1) << ": ";
            day.parts[i](std::cout); // Call the part function
            std::cout << '\n';
        }
    }
    return 0;
}