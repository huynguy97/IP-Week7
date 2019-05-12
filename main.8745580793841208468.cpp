#include <iostream>
#include <fstream>
#include <cassert>

#include <string>
#include <stdlib.h>

using namespace std;

//                            
//                       

const int MAX_CHAR = 80;
const int MAX_WORDS = 30000;

string GetCommand(string& input){
    //               
    assert(true);
/*                 
                                                 
*/
    char charInput[MAX_CHAR];

    cin.getline(charInput, MAX_CHAR);
    input = charInput;

    int commandLength = 0;

    for(int i = 0; i < MAX_CHAR; i++){
        if(charInput[i] == ' ')
            break;

        commandLength++;
    }

    string commandToString = charInput;
    return commandToString.substr(0, commandLength);
}

int Enter(string inputFileName, string result[MAX_CHAR]){
    //               
    assert(true);
/*                 
                                                                            
                                                                 
*/
    ifstream stream;

    stream.open(inputFileName.c_str());

    if(!stream.is_open())
        cout << "Could not enter " << inputFileName << endl;

    char a;
    int wordIndex = 0;

    string word = "";

    while(stream){
        stream.get(a);

        if(a == ' ' || a == '\n' || a == '.' || a == ','){
            if(word != ""){
                result[wordIndex] = word;
                wordIndex++;

                word = "";
            }
        }
        else{
            word += a;
        }
    }

    cout << "Number of words: " << wordIndex << endl;
    return wordIndex;
}

void Content(int wordCount, string words[MAX_CHAR]){
    //               
    assert(true);
/*                 
                                                               
                           

*/
    for(int i = 0; i < wordCount; i++){
        cout << words[i] << endl;
    }
}

string FileName(string input){
    //               
    assert(true);
/*                 
                                                        
*/
    int filenameLength = 0;
    int filenameStart = 0;

    bool foundSpace = false;

    for(int i = 0; i < MAX_CHAR; i++){
        if(input[i] == ' ' || input[i] == '\n'){
            if(!foundSpace){
                foundSpace = true;
            }
            else if(input[i] == '\n'){
                break;
            }
        }
        else{
            if(foundSpace){
                filenameLength++;

                if(filenameStart == 0)
                    filenameStart = i;
            }
        }
    }

    return input.substr(filenameStart, filenameLength);
}

int GetWordCount(string input){
    //               
    assert(true);
/*                 
                                                                              
*/
    int wordCount = 1;

    for(int i = 0; i < input.length(); i++){
        char a = input[i];

        if(a == ' '){
            wordCount++;
        }
    }

    return wordCount;
}

int Count(string inputWords, string allWords[MAX_WORDS]){
    //               
    assert(true);
/*                 
                                                                                     
                    
*/
    int result = 0;
    int wordCount = GetWordCount(inputWords);

    for(int i = 0; i < 500; i++){

        string checkWord = allWords[i];

        for(int j = 1; j < wordCount; j++){
            if(wordCount != 1)
                checkWord = checkWord + " " + allWords[i + j];
        }

        if(inputWords == checkWord)
            result++;
    }

    return result;
}

int TotalCount(string allWords[MAX_WORDS]){
    //               
    assert(true);
/*                 
                                                   
*/
    bool stopCountingAll = false;

    int all = 0;

    for(int i = 0; i < 500; i++){
        if(allWords[i] == "")
            stopCountingAll = true;

        if(!stopCountingAll)
            all++;
    }

    return all;
}

void Where(string word, string words[MAX_WORDS], int index_nr[MAX_WORDS]){
    //               
    assert(true);
/*                 
                                                                              
                            
*/
    int wordAmount = GetWordCount(word);
    int occurrences = 0;

    for(int i = 0; i < 500; i++){
        string checkWord = words[i];

        for(int j = 1; j < wordAmount; j++){
            if(wordAmount != 1)
                checkWord = checkWord + " " + words[i + j];
        }

        if(word == checkWord){
            index_nr[occurrences] = i+1;
            occurrences++;
        }
    }
}

void SplitNumberFromWord(string& number, string& words, string word){
    //               
    assert(true);
/*                 
                                                                                                                           
*/
    bool findingNumber = true;

    for(int i = 0; i < word.length(); i++){
        char currentCharacter = word[i];

        if(findingNumber){
            if(currentCharacter != ' '){
                number += currentCharacter;
            }
            else{
                findingNumber = false;
            }
        }
        else{
            words += currentCharacter;
        }
    }
}

void Context(string word, string allWords[MAX_WORDS]){
    //               
    assert(true);
/*                 
                                                                                             
*/
    string number;
    string words;

    SplitNumberFromWord(number, words, word);

    int contextCount = atoi(number.c_str());

    int wordAmount = GetWordCount(words);
    int occurrences = 0;

    cout << "\n";

    for(int i = 0; i < 500; i++){
        string checkWord = allWords[i];

        for(int j = 1; j < wordAmount; j++){
            if(wordAmount != 1)
                checkWord = checkWord + " " + allWords[i + j];
        }

        if(words == checkWord){
            occurrences++;

            cout << occurrences << ". ";

            for(int k = i - contextCount; k < i + contextCount + wordAmount; k++){
                if(k >= 0){
                    cout << allWords[k] << " ";
                }
            }

            cout << endl;
        }
    }

    cout << "\nYour word(s) occur " << occurrences << " times in the file." << endl;
}

int main()
{
    string words[MAX_WORDS];
    int index_nr[MAX_WORDS];
    int wordCount = NULL;

    bool stop = false;

    while(!stop){
        string originalInput;
        string command = GetCommand(originalInput);

        string possibleCommands[6] = {"enter", "content", "stop", "count", "where", "context"};

        if(command == possibleCommands[0]){
            wordCount = Enter(FileName(originalInput), words);
        }
        else if(command == possibleCommands[1]){
            if(wordCount != NULL){
                Content(wordCount, words);
            }
            else{
                cout << "Please enter a file first, Thanks" << endl;
            }
        }
        else if(command == possibleCommands[2]){
            cout << "Program stopped" << endl;
            stop = true;
        }
        else if(command == possibleCommands[3]){
            string wordInput = FileName(originalInput);

            if(GetWordCount(wordInput) > 0){
                int all = TotalCount(words);
                int wordPresence = Count(wordInput, words);
                int percentage = (float)wordPresence/(float)all * 100;
                cout << "Your word(s) appear(s) " << wordPresence << " times and the total number of words is " << all << " so the percentage of occurrences is " << percentage << "%." << endl;
            }
        }
        else if(command == possibleCommands[4]){
            string wordInput = FileName(originalInput);
            int frequency = Count(wordInput, words);
            wordInput = FileName(originalInput);

            Where(wordInput, words, index_nr);

            cout << "The index numbers of your word(s) are: ";

            for(int i = 0; i < frequency; i++){
                cout << index_nr[i] << ((i == frequency - 1) ? "" : ", ");
            }

            cout << endl;
            cout << "Your word(s) occur " << frequency << " times in the file." << endl;
        }
        else if(command == possibleCommands[5]){
            string wordInput = FileName(originalInput);
            Context(wordInput, words);
        }
    }
}

