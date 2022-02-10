//
//
//Resources used:
//  https://www-geeksforgeeks-org.cdn.ampproject.org/v/s/www.geeksforgeeks.org/overloading-stream-insertion-operators-c/amp/?amp_gsa=1&amp_js_v=a8&usqp=mq331AQKKAFQArABIIACAw%3D%3D#amp_ct=1643261252202&amp_tf=From%20%251%24s&aoh=16432612505518&referrer=https%3A%2F%2Fwww.google.com&ampshare=https%3A%2F%2Fwww.geeksforgeeks.org%2Foverloading-stream-insertion-operators-c%2F
//  https://stackoverflow.com/questions/54526582/implementing-getline-for-my-custom-string-class (used for reference for implementing getline
//
#include "DSString.h"

//
//   Constructors and Destructor
//
DSString::DSString(){
    word = nullptr;
}
DSString::DSString(const char* input){
    if(input == nullptr){
        word = nullptr;
    }
    else {
        word = new char[strlen(input) + 1];
        strcpy(word, input);
    }
}
DSString::DSString(const DSString& input){
    word = new char[strlen(input.word) + 1];
    strcpy(word, input.word);
}
DSString::~DSString(){
    if(word != nullptr){
        delete word;
    }
}

//
//  Overloaded Operators
//
//works!
DSString& DSString::operator= (const char* temp){
    word = new char[strlen(temp) + 1];
    strcpy(word, temp);
    return *this;
}
//works!
DSString& DSString::operator= (const DSString& temp){
    if(this == &temp){
        return *this;
    }
    word = new char[strlen(temp.word) + 1];
    strcpy(this->word, temp.word);
    return *this;
}
//working !!!!!!!!!!!!!!!wait double check
DSString DSString::operator+ (const DSString& temp){
    DSString newWord(*this);
    strcat(newWord.word, temp.word);
    return newWord;
}
//working
DSString& DSString::operator+= (const DSString& temp){
    strcat(this->word, temp.word);
    return *this;
}

//works!
bool DSString::operator== (const char* temp){
    if(strcmp(word, temp) == 0){
        return true;
    }
    return false;
}
//works
bool DSString::operator== (const DSString& temp){
    if (strcmp(this->word, temp.word) == 0){
        return true;
    }
    return false;
}
//works
bool DSString::operator> (const DSString& temp) const{
    if (strcasecmp(this->c_str(), temp.c_str()) > 0){
        return true;
    }
    return false;
}
//works
bool DSString::operator> (const char* temp){
    if (strcasecmp(this->c_str(), temp) > 0){
        return true;
    }
    return false;
}
//works , back to const?
bool DSString::operator< (const DSString& temp) const{
    if (strcasecmp(this->c_str(), temp.c_str()) < 0){
        return true;
    }
    return false;
}
//works
bool DSString::operator< (const char* temp){
    if (strcasecmp(this->c_str(), temp) < 0){
        return true;
    }
    return false;
}
//code the throw better? but it still works!
char& DSString::operator[] (const int index){
    if (index >= this->getLength()){
        throw std::out_of_range ("Index out of range!");
    }
    return word[index];

}

//
// Other functions
//
//works!
int DSString::getLength(){
    return strlen(word);
}
//works!
DSString DSString::substring(int start, int numChars){
    char tempWord[numChars + 1];
    int i = 0;
    while(i < numChars) {
        tempWord[i] = word[start + i];
        i++;
    }
    return DSString(tempWord);
}

DSString DSString::substringIndex(int start, int end){
    char tempWord[end - start];
    int i = start;
    int x = 0;
    while(i < end) {
        tempWord[x] = word[i];
        i++;
        x++;
    }
    return DSString(tempWord);
}

//works?
char * DSString::c_str() const {
    return word;
}

//works now!
ostream& operator<< (ostream& output, const DSString& temp){
    output << temp.word;
    return output;
}
//file getline
ifstream& DSString::getline(ifstream& inSS, DSString& word){
    char* temp;
    inSS.get(temp, 500);
    word = DSString(temp); //will this work?
    return inSS;
}

//string stream getline
istream& DSString::getline(istream& inSS, DSString& word,const char& delim){
    /*char* temp;
    inSS.get(temp, 500, delim);
    word = DSString(temp); //will this work?
    return inSS;*/
    char *c=new char[500];
    inSS.get(c,500);
    int i=0;
    while(c[i]!=delim)
    {
        inSS.get(c,500);
        word+=c;
    }
    delete[]c;
    return inSS;
}

istream& operator>>(istream& inSS, DSString& word){
    char* temp;
    //memset(&buff[0], 0, sizeof(buff));
    inSS >> temp;
    word = temp;
    return inSS;
}

bool DSString::isAllSpecialCharacters(){
    for(int i = 0; i < this->getLength(); i++){
        if(!isalpha(this->c_str()[i])){
            return false;
        }
    }
    return true;
}

vector<DSString> DSString::parseTweet(const char* delim)const{
    vector<DSString> wordsFromTweet;
    char* tempWord = strtok(this->c_str(), delim);
    while(tempWord != NULL){
        DSString newWord(tempWord);
        wordsFromTweet.push_back(newWord);//will this work?
        tempWord = strtok(NULL, " ");
    }
    return wordsFromTweet;
}

DSString& DSString::toLower(){
    for(int i = 0; i < strlen(word); i++){
        word[i] = tolower(word[i]);
    }
    return *this;
}

bool DSString::isAlpha(char x){
    if(isalpha(x)){
        return true;
    }
    return false;
}


DSString& DSString::removeAllSpecialCharacters(){
    DSString temp;
    char* start = this->c_str();
    char* end = this->c_str() + (strlen(this->c_str()) + 1);
    //end = remove_if(start, end, isAlpha());
}