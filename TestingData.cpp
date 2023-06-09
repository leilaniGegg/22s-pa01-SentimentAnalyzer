//
// Created by leila on 2/8/2022.
//

#include "TestingData.h"

//Some of these functions were only for testing purposes, i.e. the display functions

//Get the tweet and its ID
void TestingData::retrieveTI(const vector<vector<DSString>>& testingData){
    int size = testingData.at(0).size();
    for(int r = 0; r < testingData.size(); r++){
        long ID = atol(testingData.at(r).at(0).c_str());
        Tweet tweet((testingData.at(r).at(size-1)), ID); //correct syntax?
        tweet.toLower();
        tweetsAndIDs.insert(pair<long, Tweet>(ID, tweet));
    }
}

void TestingData::displayTI(){
    map<long, Tweet>::iterator itr;
    for(itr = tweetsAndIDs.begin(); itr != tweetsAndIDs.end(); itr++){
        cout << itr->first << "--" << itr->second << endl;
    }
}

//calculate the sentiment of each tweet. parameter is the wordFrequency map from training
void TestingData::calculateTS(const map<DSString, Word, DSStringCompare>& wordFrequency){
    //go through each word of the tweet, find its corresponding word in the
    // tweetsAndIds map, and calculate its sentiment by adding up the ranks
    vector<Word> wordsFromTweet;
    map<long, Tweet>::iterator itr;
    for(itr = tweetsAndIDs.begin(); itr != tweetsAndIDs.end(); itr++){
        Tweet* currTweet = &itr->second;
        //store the words from the tweet in a vector to loop through
        wordsFromTweet = currTweet->getWords();
        for(int i = 0; i < wordsFromTweet.size(); i++){
            Word* currWord = &wordsFromTweet.at(i);
            if(wordFrequency.count(currWord->getActualWord())){
                auto itr2 = wordFrequency.find(currWord->getActualWord());
                //Add the sentiment rank of each word to this tweet sentiment rank
                currTweet->addtoRank(itr2->second.getRank());
            }
        }
        currTweet->determinePS(); //the predicted sentiment, 0 or 4
    }
}

//show the predicted sentiment value for each tweet
void TestingData::displayPredictedTS(){
    map<long, Tweet>::iterator itr;
    for(itr = tweetsAndIDs.begin(); itr != tweetsAndIDs.end(); itr++){
        //print the predicted sentiment and tweet (testing purposes mainly)
        cout << itr->second.getPS() << endl;
    }
}

void TestingData::compareSentiments(const vector<vector<DSString>>& input){
    //loop through the vector of actual sentiments and tweet IDS (3rd file)
    for(int r = 0; r < input.size(); r++){
        long ID = atol(input.at(r).at(1).c_str());
        int actualSentiment = atoi(input.at(r).at(0).c_str());
        if(tweetsAndIDs.count((ID))){
            auto itr = tweetsAndIDs.find(ID);
            if(itr->second.getPS() != actualSentiment){
                //add incorrectly matched tweets to vector
               incorrectTweets.push_back(itr->first);
            }
        }
    }
}

void TestingData::calculateAccuracy(){
    //correct tweets divided by total tweets
    accuracy = (float)(tweetsAndIDs.size() - incorrectTweets.size())/(tweetsAndIDs.size());
}

float TestingData::getAccuracy()const{
    return accuracy;
}

//show incorrect tweet ids
vector<long>& TestingData::getIT(){
    return incorrectTweets;
}