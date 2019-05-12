/*
                         
                          
 */

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

string validactions[] = {"enter", "content", "count", "where", "context", "stop"};

const int NUMBER_OF_ACTIONS = 6;

const int MAX_FILENAME_LENGTH = 80;
const int MAX_WORDS = 30000;

string currentaction = "none";
int currentm = 0;
string currentsequence[MAX_WORDS];
int currentsequencelength = 0;
int occurencesofsequence[MAX_WORDS];

string currentFileName;
ifstream currentFile;

string wordsinfile[MAX_WORDS];
int numofwordsinfile = 0;

bool isValidAction(string action) {
    //             
    assert(!action.empty());
    //              
    //                                                                         

    for (int i = 0; i < NUMBER_OF_ACTIONS; i++) {
        if (action == validactions[i]) {
            return true;
        }
    }
    return false;
}

void getInput(string words[MAX_FILENAME_LENGTH]) {
    //             
    assert(true);
    //              
    //                                                            

    char wordss[MAX_FILENAME_LENGTH] = {0};
    cin.getline(wordss, MAX_FILENAME_LENGTH);
    int c = 0;
    //                
    string currentword;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++) {
        char current = wordss[i];
        if (current > 32 && current <= 126) {
            currentword += current;
        } else if (current == 32) {
            //                      
            words[c] = currentword;
            currentword = "";
            c++;
        }
    }
    words[c] = currentword;
}

bool openFile() {
    //             
    assert(!currentFile.is_open());
    //              
    //                                                                

    currentFile.open(currentFileName.c_str());
    return currentFile.is_open();
}

void readFile() {
    //             
    assert(currentFile.is_open());
    //              
    //                                                                                                                             

    string word;
    int c = 0;
    while (currentFile >> word) {
        wordsinfile[c] = word;
        c++;
    }
    numofwordsinfile = c;
    cout << "Succesfully read " << c << " words" << endl;
}

void printContent() {
    //             
    assert(currentFile.is_open());
    //              
    //                                                                                   

    if (!currentFile.is_open()) {
        cout << "No file has been openend yet! Please first open a file using 'enter [filename]'" << endl;
        return;
    }
    cout << "Printing all contents of currently selected file " << currentFileName << endl;
    for (int i = 0; i < MAX_WORDS; i++) {
        if (wordsinfile[i] != "") {
            cout << wordsinfile[i] << " ";
        }
    }
    cout << endl;
}

int countSequenceOccurences() {
    //             
    assert(currentFile.is_open());
    //              
    //                                                                                                                                                                                         

    int occurences = 0;
    for (int i = 0; i < numofwordsinfile; i++) {
        int similarities = 0;
        for (int j = 0; j < currentsequencelength; j++) {
            int k = i + j;
            string fileword = wordsinfile[k];
            //                                                 
            for (int k = 0; k < currentsequencelength; k++) {
                if (currentsequence[k] == fileword) {
                    similarities++;
                }
            }
        }
        if (similarities == currentsequencelength) {
            occurencesofsequence[occurences++] = i + 1;
        }
    }
    return occurences;
}

int main() {
    cout << "Welcome, please enter one of the following actions:" << endl;
    cout << "enter: enter a filename." << endl;
    cout << "content: display all words in order of appearance in the current file." << endl;
    cout << "count [sequence]: count the number of occurences of the sequence in the current file." << endl;
    cout << "where [sequence]: print the indices where sequence occurs in the current file." << endl;
    cout << "context [m] [sequence]: print all occurences of sequence and the m words preceding and following that occurence, in the current file" << endl;
    cout << "stop: to stop" << endl;
    bool running = true;
    while (running) {
        bool f = false;
        string words[MAX_WORDS];
        while (!isValidAction(currentaction)) {
            if (f) {
                cout << "Please enter a valid action, as listed above:" << endl;
            }
            getInput(words);
            //                                   
            currentaction = words[0];
            f = true;
        }
        if (currentaction == "enter") {
            if (currentFile.is_open()) {
                currentFile.close();
            }
            //                                             
            for (int i = 1, j = 0; i < MAX_WORDS; i++) {
                currentsequence[j] = words[i];
                j++;
            }
            string filename;
            for (int k = 1; k < MAX_FILENAME_LENGTH; k++) {
                string currentword = words[k];
                if (currentword != "") {
                    for (int i = 0; i < currentword.length(); i++) {
                        char current = words[k][i];
                        if (current > 32 && current <= 126) {
                            filename += current;
                        }
                    }
                    filename += " ";
                }
            }
            currentFileName = filename;
            //             
            if (openFile()) {
                readFile();
            } else {
                cout << "Something went wrong while trying to open that file!" << endl;
            }
        } else if (currentaction == "content") {
            printContent();
        } else if (currentaction == "count") {
            currentsequencelength = 0;
            if (!currentFile.is_open()) {
                cout << "No file has been openend yet! Please first open a file using 'enter [filename]'" << endl;
            } else {
                //                        
                for (int i = 1; i < MAX_WORDS; i++) {
                    string currentword = words[i];
                    if (!currentword.empty()) {
                        currentsequence[currentsequencelength] = currentword;
                        currentsequencelength++;
                    }
                }
                int occurences = countSequenceOccurences();
                cout << "The given sequence occures " << occurences << " times in the file" << endl;
                cout << "The file contains " << numofwordsinfile << " words in total" << endl;
                double onepercent = static_cast<double>(numofwordsinfile) / 100;
                double percentage = occurences / onepercent;
                cout << "So the given sequence makes up " << percentage << "% of the total amount of words in the file."
                     << endl;
            }
        } else if (currentaction == "where") {
            currentsequencelength = 0;
            for (int i = 1; i < MAX_WORDS; i++) {
                string currentword = words[i];
                if (!currentword.empty()) {
                    currentsequence[currentsequencelength] = currentword;
                    currentsequencelength++;
                }
            }
            int occurences = countSequenceOccurences();
            cout << "The given sequence occures at indices: ";
            for (int i = 0; i < MAX_WORDS; i++) {
                if (occurencesofsequence[i] >= i) {
                    cout << occurencesofsequence[i] << " ";
                }
            }
            cout << endl << "The given sequence was found " << occurences << " times in total" << endl;
        } else if (currentaction == "context") {
            currentsequencelength = 0;
            currentm = stoi(words[1]);
            for (int i = 2; i < MAX_WORDS; i++) {
                string currentword = words[i];
                if (!currentword.empty()) {
                    currentsequence[currentsequencelength] = currentword;
                    currentsequencelength++;
                }
            }
            int occurences = countSequenceOccurences();
            cout << "The " << currentm << "-word context of the current sequence is: " << endl;
            for (int i = 0; i < occurences; i++) {
                //                                      
                int beforeindex = (occurencesofsequence[i] - currentm) - 1;
                if (beforeindex < 0) {
                    beforeindex = 0;
                }
                int afterindex = (occurencesofsequence[i] + currentm) - 1;
                if (afterindex > numofwordsinfile) {
                    afterindex = numofwordsinfile;
                }
                //                
                for (int j = beforeindex; j <= afterindex; j++) {
                    cout << wordsinfile[j] << " ";
                }
                cout << endl;
            }
            cout << "The given sequence was found " << occurences << " times in total" << endl;
        }
        if (currentaction == "stop") {
            //           
            currentFile.close();
            running = false;
        } else {
            currentaction = "";
            cout << "Please enter next action:" << endl;
        }
    }
    return 0;
}
