//                       

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cassert>

using namespace std;

const int MAX_FILENAME_LENGTH = 100;
const int MAX_WORDS = 50000;
const int MAX_SEQUENCE = 20;

string wordList[MAX_WORDS];
int totalNumberOfWords = 0;
int wordSequenceLength = 0;

void getFileName(char fileName[MAX_FILENAME_LENGTH]){
//                     
    assert(true);
//                                              

    char next = '0';
    int index = 0;

    cin.get(next);

    while(next != '\n'){
        cin.get(next);
        fileName[index] = next;
        index++;
    }

    fileName[index - 1] = '\0';
}

void storeAllWords(ifstream& inputFile){
//                                               
    assert(inputFile);
//                                              

    int index = 0;

    while(!inputFile.eof()){
        inputFile >> wordList[index];
        index++;
    }

    totalNumberOfWords = index;
}

void wordSequenceMaker(string wordSequence[MAX_SEQUENCE]){
//                     
    assert(true);
//                                                            

    string next;
    char last;
    int index = 0;

    while(last != '\n' && index < MAX_SEQUENCE){
        cin >> next;
        wordSequence[index] = next;
        index++;
        cin.get(last);
    }

    wordSequenceLength = index;
}

int countWord(string wordSequence[MAX_SEQUENCE]){
//                     
    assert(true);
//                                                            
    int amount = 0;

    for(int i = 0; i < totalNumberOfWords; i++){
        if(wordSequence[0] == wordList[i]){
            bool sameSequence = true;

            for(int j = 1; j < wordSequenceLength; j++){
                if(wordSequence[j] != wordList[i + 1]){
                    sameSequence = false;
                }
            }

            if(sameSequence)
                amount++;
        }
    }

    return amount;
}

void countWordPrint(int amount){
//                     
    assert(true);
//                                             

    cout << "The sequence appears " << amount << " time(s)." << endl;
    cout << "The total amount of words in the text is: " << totalNumberOfWords << endl;
    cout << "Thus the sequence is " << ((amount * wordSequenceLength * 1.0) / totalNumberOfWords) * 100 << "% of the total text." << endl;
}

void whereWord(string wordSequence[MAX_SEQUENCE]){
//                     
    assert(true);
//                                                             

    cout << "The sequence starts at: ";

    for(int i = 0; i < totalNumberOfWords; i++){
        if(wordSequence[0] == wordList[i]){
            bool sameSequence = true;

            for(int j = 1; j < wordSequenceLength; j++){
                if(wordSequence[j] != wordList[i + 1]){
                    sameSequence = false;
                }
            }

            if(sameSequence)
                cout << i + 1 << ", ";
        }
    }

    cout << endl;
}

void contextWord(string wordSequence[MAX_SEQUENCE], int num){
//                                        
    assert(num >= 0);
//                                                        

    cout << "The different occurrences: " << endl;

    for(int i = 0; i < totalNumberOfWords; i++){
        if(wordSequence[0] == wordList[i]){
            bool sameSequence = true;

            for(int j = 1; j < wordSequenceLength; j++){
                if(wordSequence[j] != wordList[i + 1]){
                    sameSequence = false;
                }
            }

            if(sameSequence){
                cout << "\t";
                for(int k = i - num; k < i + wordSequenceLength + num; k++){
                    if(k >= 0 && k < totalNumberOfWords){
                        cout << wordList[k] << " ";
                    }
                }
                cout << endl;
            }

        }
    }
}

void fileNameEnter(){
//                     
    assert(true);
//                                            

    char fileName[MAX_FILENAME_LENGTH];
    getFileName(fileName);
    ifstream inputFile(fileName);

    if(!inputFile.is_open()){
        cout << "The file could not be opened for some reason." << endl;
        exit(EXIT_FAILURE);
    }

    storeAllWords(inputFile);
    cout << "The file consists of " << totalNumberOfWords << " words." << endl;
}

void showContent(){
//                     
    assert(true);
//                                                      

    for(int i = 0; i < totalNumberOfWords; i++){
        cout << wordList[i] << " ";
    }
}

void userCommands(){
//                     
    assert(true);
//                                                

    cout << "Use a command (enter, content, stop, count, where, context): ";

    string command;
    cin >> command;

    if(command == "enter"){
        fileNameEnter();
    }else if(command == "content"){
        showContent();
    }else if(command == "stop"){
        exit(EXIT_SUCCESS);
    }else if(command == "count"){
        string wordSequence[MAX_SEQUENCE];
        wordSequenceMaker(wordSequence);

        int amount = countWord(wordSequence);
        countWordPrint(amount);
    }else if(command == "where"){
        string wordSequence[MAX_SEQUENCE];
        wordSequenceMaker(wordSequence);

        whereWord(wordSequence);
        int amount = countWord(wordSequence);
        cout << "The sequence has been found " << amount << " time(s)." << endl;
    }else if(command == "context"){
        int num = 0;
        cin >> num;

        string wordSequence[MAX_SEQUENCE];
        wordSequenceMaker(wordSequence);

        contextWord(wordSequence, num);
        int amount = countWord(wordSequence);
        cout << "The sequence has been found " << amount << " time(s)." << endl;
    }else{
        cout << "This is not a valid command." << endl;
        exit(EXIT_FAILURE);
    }

    cout << endl;
}

int main()
{
    while(true)
        userCommands();

    return 0;
}

