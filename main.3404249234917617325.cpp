#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>

//                              
using namespace std;

const int MAX_WORDS = 10000;
const int MAX_CHARS = 100;

bool isFileOpen(ifstream& myfile){
    //                         
    //             
    char fileName [80];
    cout << "Enter Filename." << endl;
    cin.getline(fileName, 80, '\n');
    myfile.open(fileName);
    return myfile.is_open();
}

bool readWord(ifstream& myfile, char word [MAX_CHARS]){
    assert(myfile.is_open());
    myfile >> word;
    return myfile;
}

int sequentialSearch(char words[MAX_WORDS][MAX_CHARS], int from, int to, char word[MAX_CHARS]){
    assert(0 <= from && 0 <= to);

    if (from > to){
        return to + 1;
    }
    int pos = from;
    while (pos <= to && words[pos] != word){
        pos++;
    }
    return pos;
}

bool tallyWord(char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int frequency [MAX_WORDS], int& no ){
    assert(no >= 0 && no < MAX_WORDS);
    int pos = sequentialSearch(words, 0, no, word);
    if(pos < no){
        frequency[pos]++;
        return true;
    } else if (pos < MAX_WORDS){
        strcpy(words[pos], word);
        frequency[pos] = 1;
        no++;
        //                           
        return true;
    }
    return false;
}

int countWords(ifstream& myfile, char words [MAX_WORDS][MAX_CHARS], int frequency [MAX_WORDS] ){
    assert(myfile.is_open());

    int no = 0;
    char next [MAX_CHARS];
    while (readWord (myfile, next) && tallyWord (next, words, frequency, no) && no < MAX_WORDS){
        ;
    }
        return no;
}

void displayFrequencies(char words [MAX_WORDS][MAX_CHARS], int frequency [MAX_WORDS], int no ){
    assert(no >= 0 && no < MAX_WORDS);
    for(int i = 0; i < no; i++){
        cout << words[i] << "\t" << frequency[i] << "\n";
    }
}

int main(){
    ifstream myfile;
    if(isFileOpen(myfile)){
        char words [MAX_WORDS][MAX_CHARS];
        int frequency [MAX_WORDS];
        int nr = countWords(myfile, words, frequency);
        displayFrequencies(words, frequency, nr);
        myfile.close();
        return 0;
    } else {
         return 1;
    }
    return 0;
}

