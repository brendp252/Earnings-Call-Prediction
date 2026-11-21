// Declaration of SentimentReader class, which holds earnings call data.

#ifndef SENTIMENTREADER_HPP
#define SENTIMENTREADER_HPP

#include "utils.hpp"
#include <fstream>
#include <unordered_map>


// WordCounts struct for tracking positive/negative counts of a word.
// Also tracks negOdds of word being positive/negative given training data.
// Value type in "vocab" map within SentimentReader class.
struct WordCounts {
    size_t pos = 0;
    size_t neg = 0;
    double negOdds = 0.0;
}; // WordCounts


// SentimentReader class for training/predicting based on earnings call data.
class SentimentReader {
public:    
    void getOptions(int argc, char** argv);


    void readCalls();
    

    void predict() const;
private:
    void readCall(const std::string& callFile) {
        std::ifstream is(callFile);
        if (is.fail()) printError('f');
        ++totalCalls;

        std::string word;
        is >> word;
        if (word != "Positive" && word != "Negative") printError('t');

        if (word == "Positive") {
            ++totalPosCalls;
            while (is >> word) {
                std::string modifiedWord = lowerAndStrip(word);
                if (!modifiedWord.empty()) {
                    ++totalPosWords;
                    vocab[modifiedWord].pos++;
                } // if
            } // while
        } else {
            while (is >> word) {
                std::string modifiedWord = lowerAndStrip(word);
                if (!modifiedWord.empty()) {
                    ++totalNegWords;
                    vocab[modifiedWord].neg++;
                } // if
            } // while
        } // if-else
    } // readCall()


    std::unordered_map<std::string, WordCounts> vocab;
    std::string readFile = "";
    std::string predictFile = "";
    size_t totalCalls = 0;
    size_t totalPosCalls = 0;
    size_t totalPosWords = 0;
    size_t totalNegWords = 0;
}; // SentimentReader

#endif // SENTIMENTREADER_HPP