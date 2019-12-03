#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

// --- Day 1: The Tyranny of the Rocket Equation ---

/**
 * --- Part 1 ---
 *
 * Santa has become stranded at the edge of the Solar System while delivering presents to other planets! To
 * accurately calculate his position in space, safely align his warp drive, and return to Earth in time to
 * save Christmas, he needs you to bring him measurements from fifty stars.
 *
 * Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar;
 * the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
 *
 * The Elves quickly load you into a spacecraft and prepare to launch.
 *
 * At the first Go / No Go poll, every Elf is Go until the Fuel Counter-Upper. They haven't determined the
 * amount of fuel required yet.
 *
 * Fuel required to launch a given module is based on its mass. Specifically, to find the fuel required for a
 * module, take its mass, divide by three, round down, and subtract 2.
 *
 * The Fuel Counter-Upper needs to know the total fuel requirement. To find it, individually calculate the
 * fuel needed for the mass of each module (your puzzle input), then add together all the fuel values.
 *
 * What is the sum of the fuel requirements for all of the modules on your spacecraft?
 */

int calculate_fuel(const int mass) noexcept { return std::floor(mass / 3 - 2); }

int total_fuel_needed(const std::vector<int>& mass_list) noexcept {
  int temporary = 0;
  for (const auto& mass : mass_list)
    temporary += calculate_fuel(mass);

  return temporary;
}

/**
 * --- Part Two ---
 *
 * During the second Go / No Go poll, the Elf in charge of the Rocket Equation Double-Checker stops the launch
 * sequence. Apparently, you forgot to include additional fuel for the fuel you just added.
 *
 * Fuel itself requires fuel just like a module - take its mass, divide by three, round down, and subtract 2.
 * However, that fuel also requires fuel, and that fuel requires fuel, and so on. Any mass that would require
 * negative fuel should instead be treated as if it requires zero fuel; the remaining mass, if any, is instead
 * handled by wishing really hard, which has no mass and is outside the scope of this calculation.
 *
 * So, for each module mass, calculate its fuel and add it to the total. Then, treat the fuel amount you just
 * calculated as the input mass and repeat the process, continuing until a fuel requirement is zero or
 * negative.
 *
 * What is the sum of the fuel requirements for all of the modules on your spacecraft when also taking into
 * account the mass of the added fuel? (Calculate the fuel requirements for each module separately, then add
 * them all up at the end.)
 */

int true_fuel_needed(const int mass) noexcept {
  int temporary = calculate_fuel(mass);
  int result = temporary;
  while (calculate_fuel(temporary) > 0) {
    temporary = calculate_fuel(temporary);
    result += temporary;
  }
  return result;
}

int total_true_fuel_needed(const std::vector<int>& mass_list) noexcept {
  int temporary = 0;

  for (const auto& mass : mass_list)
    temporary += true_fuel_needed(mass);
  return temporary;
}

/**
 * Entry point of day 1 challenge.
 */
int main(int argc, char** argv) {
  // Stream is being closed automatically when fstream destructor is called.
  std::fstream day1_input(std::filesystem::current_path().string().append(argv[1]));
  std::istream_iterator<int> start(day1_input), end;
  std::vector<int> mass_list(start, end);

  std::cout << "total fuel needed: " << total_fuel_needed(mass_list) << std::endl;
  std::cout << "total true fuel needed: " << total_true_fuel_needed(mass_list) << std::endl << std::endl;

  return EXIT_SUCCESS;
}