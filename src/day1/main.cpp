#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  // Stream is being closed automatically when fstream destructor is called.
  std::fstream day1_input(std::filesystem::current_path().string().append("/input/day1.input"));
  std::istream_iterator<int> start(day1_input), end;

  std::vector<int> mass_list(start, end);
  int total_fuel_needed = 0;

  for (const auto& mass : mass_list)
    total_fuel_needed += std::floor(mass / 3) - 2;

  std::cout << total_fuel_needed << std::endl;

  return EXIT_SUCCESS;
}