// Implementation of SentimentReader class.

#include "SentimentReader.hpp"
#include <getopt.h>
#include <cmath>


void SentimentReader::getOptions(int argc, char** argv) {
    int optionIndex = 0, option = 0;

    // Don't display getopt error messages about options
    opterr = false;

    // Use getopt to find command line options
    struct option longOpts[] = {{ "read", required_argument, nullptr, 'r' },
                                { "predict", required_argument, nullptr, 'p' },
                                { "help", no_argument, nullptr, 'h' },
                                { nullptr, 0, nullptr, '\0' }};
    
    while ((option = getopt_long(argc, argv, "r:p:h", longOpts, &optionIndex)) != -1) {
        switch (option) {
            case 'r':
                readFile = optarg;
                break;

            case 'p':
                predictFile = optarg;
                break;

            case 'h':
                printHelp();

            default:
                printError('u');
        } // switch
    } // while

    if (readFile.empty()) printError('r');
    if (predictFile.empty()) printError('p'); 
} // getOptions()


void SentimentReader::readCalls() {
    std::ifstream is(readFile);
    if (is.fail()) printError('l');
    
    std::string callFile;
    while (is >> callFile) {
        readCall(callFile);
    } // while
    if (totalCalls == 0) printError('c');

    const int ALPHA = 1; // For Laplace smoothing
    const double NUM_FEATURES = static_cast<double>(vocab.size()); // For Laplace smoothing
    const double LOG_POS_PROD_DENOM = std::log(static_cast<double>(totalPosWords) + ALPHA * NUM_FEATURES);
    const double LOG_NEG_PROD_DENOM = std::log(static_cast<double>(totalNegWords) + ALPHA * NUM_FEATURES);
    for (auto& [word, wordData] : vocab) {
        wordData.negOdds = std::log(static_cast<double>(wordData.neg + ALPHA)) 
                        - std::log(static_cast<double>(wordData.pos + ALPHA)) 
                        + LOG_POS_PROD_DENOM - LOG_NEG_PROD_DENOM;
    } // for [word, wordData]
} // readCalls()


void SentimentReader::predict() const {
    std::ifstream is(predictFile);
    if (is.fail()) printError('f');

    double negLogOdds = std::log(static_cast<double>(totalCalls - totalPosCalls) / static_cast<double>(totalPosCalls));

    std::string word;
    while (is >> word) {
        auto it = vocab.find(lowerAndStrip(word));
        if (it != vocab.end()) negLogOdds += it->second.negOdds;
    } // for word

    double posProb = 1.0 / (1.0 + std::exp(negLogOdds));
    std::cout << "Log-odds: " << -1 * negLogOdds << '\n'
              << "Probability of positive movement: " << posProb << '\n'
              << "Probability of negative movement: " << 1 - posProb << '\n'
              << "Recommendation: ";
    posProb > 0.5 ? std::cout << "Buy\n" : std::cout << "Sell\n";
} // predict()
