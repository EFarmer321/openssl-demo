#include "utils.h"
#include <iostream>

std::string Utils::read_string() {
  std::string input;

  std::getline(std::cin >> std::ws, input);

  return input;
}