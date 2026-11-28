// Helper function implementations for SentimentReader.

#include "utils.hpp"
#include <cstdlib>
#include <cctype>


std::string lowerAndStrip(const std::string& str) {
    // Skip beginning and end punctuation
    size_t begin = 0, end = str.size();
    while (begin < end && ispunct(str[begin])) {
        ++begin;
    } // while
    while (end > begin && ispunct(str[end - 1])) {
        --end;
    } // while

    // Add lowercase version of chars to modifiedStr
    std::string modifiedStr = "";
    modifiedStr.reserve(end - begin);
    for (size_t i = begin; i < end; ++i) {
        modifiedStr.push_back(static_cast<char>(std::tolower(str[i])));
    } // for i

    return modifiedStr;
} // lowerAndStrip()


[[noreturn]] void printError(Error e) {
    if (e == Error::InvalidCallFile) {
        std::cerr << "Could not open call file" << std::endl;
    } else if (e == Error::InvalidCallFileList) {
        std::cerr << "Could not open list of call files" << std::endl;
    } else if (e == Error::NoCallFileList) {
        std::cerr << "Provide list of call files" << std::endl;
    } else if (e == Error::EmptyCallFileList) {
        std::cerr << "Select training data before predicting" << std::endl;
    } else if (e == Error::NoPredictFile) {
        std::cerr << "Provide file to predict" << std::endl;
    } else if (e == Error::InvalidLabel) {
        std::cerr << "File must be labeled Positive or Negative" << std::endl;
    } else if (e == Error::UnknownCLIOption) {
        std::cerr << "Unknown option" << std::endl;
    } // if-else

    exit(1);
} // printError()


[[noreturn]] void printHelp() {
    std::cout << "This program reads a txt file that contains one or more\n"
              << "paths to cleaned earnings call txt files ('read files')\n"
              << "and a separate cleaned earnings call txt file ('predict file').\n"
              << "It will train itself on the read files to predict the stock\n"
              << "price movement following the earnings call described in the\n"
              << "predict file. It will output the probability of a positive or\n"
              << "negative movement and recommend 'Buy' or 'Sell'.\n"
              << "Usage: \'./earnings\n\t[--read | -r] <List of Read Files>\n"
              <<                     "\t[--predict | -p] <Predict File>\n"
              <<                     "\t[--help | -h]\'\n" << std::endl;
    exit(0);
} // printHelp()