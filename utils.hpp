// Helper function declarations for SentimentReader.

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>


// Error enum class for labeling error types.
enum class Error : char {
    InvalidCallFile,
    InvalidCallFileList,
    NoCallFileList,
    EmptyCallFileList,
    NoPredictFile,
    InvalidLabel,
    UnknownCLIOption
}; // Error


// Returns str converted to lowercase & stripped of punctuation.
std::string lowerAndStrip(const std::string& str);


// Print error based on error type.
[[noreturn]] void printError(Error e);


// Print help message to user.
[[noreturn]] void printHelp();

#endif // UTILS_HPP