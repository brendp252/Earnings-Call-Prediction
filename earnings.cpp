// Driver for the program.

#include "SentimentReader.hpp"


int main(int argc, char** argv) {
    SentimentReader s;
    s.getOptions(argc, argv);
    s.readCalls();
    s.predict();

    return 0;
} // main()
