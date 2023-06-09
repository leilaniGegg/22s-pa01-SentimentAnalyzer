#include "FileManager.h"
#include "TrainingData.h"
#include "TestingData.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

int main(int argc, char* const argv[]) {
    if(argc == 1){
        return Catch::Session().run();
    }
    else {
        FileManager IO;
        TrainingData training;
        //From the training file, store the tweets and their sentiments in a map
        training.retrieveTS(IO.readFile(argv[1]));
        //Calculate the frequency of each word in the tweets, and store the word in a map (as map<DSString, Word>)
        training.calculateWF();
        TestingData testing;
        //From the testing file, store the tweets and their ID's in a map
        testing.retrieveTI(IO.readFile(argv[2]));
        //Calculate the predicted sentiment of the tweet
        testing.calculateTS(training.getWF());
        //Compare predicted sentiment to actual sentiment
        testing.compareSentiments(IO.readFile(argv[3]));
        testing.calculateAccuracy();
        IO.writeToFile(argv[4], testing);
    }

    return 0;
}