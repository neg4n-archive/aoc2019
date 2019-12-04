#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

// --- Day 2: 1202 Program Alarm ---

/**
 * --- Part 1 ---
 * 
 * On the way to your gravity assist around the Moon, your ship computer beeps angrily about a "1202 program
 * alarm". On the radio, an Elf is already explaining how to handle the situation: "Don't worry, that's
 * perfectly norma--" The ship computer bursts into flames.
 *
 * You notify the Elves that the computer's magic smoke seems to have escaped. "That computer ran Intcode
 * programs like the gravity assist program it was working on; surely there are enough spare parts up there to
 * build a new Intcode computer!"
 *
 * An Intcode program is a list of integers separated by commas (like 1,0,0,3,99). To run one, start by
 * looking at the first integer (called position 0). Here, you will find an opcode - either 1, 2, or 99. The
 * opcode indicates what to do; for example, 99 means that the program is finished and should immediately
 * halt. Encountering an unknown opcode means something went wrong.
 *
 * Opcode 1 adds together numbers read from two positions and stores the result in a third position. The three
 * integers immediately after the opcode tell you these three positions - the first two indicate the positions
 * from which you should read the input values, and the third indicates the position at which the output
 * should be stored.
 *
 * For example, if your Intcode computer encounters 1,10,20,30, it should read the values at positions 10 and
 * 20, add those values, and then overwrite the value at position 30 with their sum.
 *
 * Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them. Again,
 * the three integers after the opcode indicate where the inputs and outputs are, not their values.
 *
 * Once you're done processing an opcode, move to the next one by stepping forward 4 positions.
 *
 * Once you have a working computer, the first step is to restore the gravity assist program (your puzzle
 * input) to the "1202 program alarm" state it had just before the last computer caught fire. To do this,
 * before running the program, replace position 1 with the value 12 and replace position 2 with the value 2.
 * What value is left at position 0 after the program halts?
 */

enum Instructions { ADD = 1, MULTIPLY = 2, HALT = 99 };

std::vector<int> split(std::string_view string, char delimiter = ' ') noexcept {
  std::vector<int> temporary_vector;
  std::stringstream temporary_stringstream(string.data());
  std::string token;

  while (std::getline(temporary_stringstream, token, delimiter))
    temporary_vector.push_back(std::atoi(token.c_str()));

  temporary_stringstream.clear();

  return temporary_vector;
}

int process_instructions(const int first_code, const int second_code, std::vector<int>& codes) noexcept {
  int code = 0;
  codes[ 1 ] = first_code;
  codes[ 2 ] = second_code;
  for (const auto& _ : codes) {
    bool should_halt = false;
    switch (codes[ code ]) {
    case Instructions::ADD:
      codes[ codes[ code + 3 ] ] = codes[ codes[ code + 1 ] ] + codes[ codes[ code + 2 ] ];
      break;
    case Instructions::MULTIPLY:
      codes[ codes[ code + 3 ] ] = codes[ codes[ code + 1 ] ] * codes[ codes[ code + 2 ] ];
      break;
    case Instructions::HALT:
      should_halt = true;
      break;
    default:
      continue;
    }
    code += 4;
  }
  return codes[ 0 ];
}

/**
 * Entry point of day 2 challenge.
 */
int main(int argc, char** argv) {
  std::fstream day2_input(std::filesystem::current_path().string().append(argv[ 1 ]));
  std::stringstream temporary_stringstream;

  if (temporary_stringstream) {
    temporary_stringstream << day2_input.rdbuf();
    day2_input.close();
  }

  std::vector<int> codes = split(temporary_stringstream.str(), ',');
  temporary_stringstream.clear();

  std::cout << "value at 0 at gravity program halt: " << process_instructions(12, 2, codes) << std::endl << std::endl;

  return EXIT_SUCCESS;
}