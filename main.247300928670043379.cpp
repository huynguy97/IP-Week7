//
//                                                         
//
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>
using namespace std;
int MAX_FILELENGTH = 80;
const int MAX_WORDS = 200;
const int MAX_CHARS = 2000;

string words[2][200];

int read_words (ifstream& infile ) {
    char number[MAX_WORDS][MAX_CHARS];
    int count = 0;
    do {
        count++;
    }

    while (infile  >> number[count]);
    infile.close();

    return  count;
}

bool getfilename(char filename[12]) {
    cout << "Enter filename: ";
    char c;
    int i = 0;

    while(c != '\n') {
        if (i <= MAX_FILELENGTH){
            c = cin.get();
            filename[i] = c;
            i++;
        } else {

            return false;
        }
    }
    filename[i-1] = '\0';

    return true;
}

bool open_file(char filename[12], ifstream& infile){

    infile.open(filename);
    int count = read_words(infile);
    infile.open(filename);
    if (infile.is_open()) {
        cout << "File opened succesfully and read: "  << count << " words read" <<  "\n";
    } else {
        cout << "Failed to open file" << "\n";
    }
}
int count_file(string words[2][200], char word[60]){
    int count = 0;
    for(int i = 0; i < 200; i ++) {
        if (words[0][i] == word) {
            count++;
        }

    }
    return count;
}

bool read_file (ifstream& infile, string words[2][200]) {
    assert (infile.is_open());

    char c;
    char word[60];

    int i = 0;
    int x = 0;

    for (int z = 0; z < 200; z++) {
        words[1][z] = "0";
    }

    while (infile.get(c)) {
        if (c == ' ' || c == '\n' || c == '.' || c == ',') {
            word[i] = '\0';

            string string_word(word);
            words[0][x] = string_word;
            int counter = count_file(words, word);

            for (int y = 0; y < 200; y++) {
                if(words[0][y] == word ) {
                    words [1][y] = to_string(counter);
                }
            }
            x++;
            i = -1;
        } else {
            word[i] = c;
        }
        i++;
    }

}

int main() {
    char filename[12];
    ifstream infile;
    char operation[50];
    char read[100];
   while (true) {
       cout << "Enter operation (enter (Nothing after it), stop, content";
       cin.getline(operation, sizeof(operation));

        string operationstring(operation);
       if ( operationstring == "enter") {
           getfilename(filename);
           open_file(filename, infile);
           read_file(infile, words);

       } else if (operationstring == "content") {
           for(int y = 0; y < 200; y++) {
               cout << words[0][y] << " Has a frequency of  " << words[1][y] << "\n";
           }
           cout << "\n";
       } else if (operationstring ==  "count") {

       } else if (operationstring == "stop"){
           break;
       }

   }

    infile.close();

}
