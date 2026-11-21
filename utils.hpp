// Helper function declarations for SentimentReader.

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>


// Returns str converted to lowercase & stripped of punctuation.
std::string lowerAndStrip(const std::string& str);


// Print error based on error type.
[[noreturn]] void printError(char type);


// Print help message to user.
[[noreturn]] void printHelp();

#endif // UTILS_HPP