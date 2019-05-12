#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <stdlib.h>

using namespace std;

/*
                         
                    
*/

const int MAX_COMMAND_LENGTH = 10;
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

void openfile(char sequence [MAX_CHARS], ifstream& infile, char text [MAX_WORDS][MAX_CHARS], int& words) {
    //            
    assert (!infile.is_open());
    /*             
                                                                               
                                   
    */
    infile.open(sequence);
    char word [MAX_CHARS] = "";
    int pos = 0;
    if(infile.is_open()) {
        while(infile) {
            infile >> word;
            strcpy(text[pos], word);
            pos++;
        }
        words = pos - 1;
        cout << "This file has " << pos - 1 << " words" << endl;
    } else {
        cout << "Failed to open file" << endl;
    }
    infile.close();
}

void displaycontent (char text [MAX_WORDS][MAX_CHARS], int words) {
    //            
    assert (true);
    /*             
                                                      
    */
    cout << text[0];
    for(int i = 1; i < words; i++) {
        cout << "," << text[i];
    }
    cout << '\n';
}

void displaycount (char text [MAX_WORDS][MAX_CHARS], char sequence [MAX_CHARS], int words) {
    //            
    assert (true);
    /*             
                                                                                             
                                            
    */
    //          
    char *sequencewords [MAX_WORDS];
    for(int i=0; i<MAX_WORDS; i++)
        sequencewords[i] = (char *) malloc(MAX_CHARS);
    //         
    int pos = 0;
    int wordpos = 0;
    int wordlength = 0;
    while(sequence[pos] != '\0') {
        while(sequence[pos] != ' ' && sequence[pos] != '\0') {
            sequencewords[wordpos][wordlength] = sequence[pos];
            pos++;
            wordlength++;
        }
        sequencewords[wordpos][wordlength] = '\0';
        wordlength = 0;
        wordpos++;
        pos++;
    }
    int ocount = 0;
    int currw = 0;
    int p = 1;
    for(int w = 0; w < words; w++) {
        if(strcmp(sequencewords[0], text[w]) == 0) {
            currw = w + 1;
            if(wordpos == 2) {
                ocount++;
            } else {
                while(strcmp(sequencewords[p], text[currw]) == 0) {
                    if(p == wordpos - 2) {
                        ocount++;
                    }
                    currw++;
                    p++;
                }
                p = 1;
            }
        }
    }
    cout << ocount << "," << words << "," << ((ocount*100)/words) << endl;
}

void displaywhere (char text [MAX_WORDS][MAX_CHARS], char sequence [MAX_CHARS], int words) {
    //            
    assert (true);
    /*             
                                                      
    */
    //          
    char *sequencewords [MAX_WORDS];
    for(int i=0; i<MAX_WORDS; i++)
        sequencewords[i] = (char *) malloc(MAX_CHARS);
    //         
    int pos = 0;
    int wordpos = 0;
    int wordlength = 0;
    while(sequence[pos] != '\0') {
        while(sequence[pos] != ' ' && sequence[pos] != '\0') {
            sequencewords[wordpos][wordlength] = sequence[pos];
            pos++;
            wordlength++;
        }
        sequencewords[wordpos][wordlength] = '\0';
        wordlength = 0;
        wordpos++;
        pos++;
    }
    int ocount = 0;
    int currw = 0;
    int p = 1;
    for(int w = 0; w < words; w++) {
        if(strcmp(sequencewords[0], text[w]) == 0) {
            currw = w + 1;
            if(wordpos == 2) {
               cout << w+1 << "," ;
               ocount++;
            } else {
                while(strcmp(sequencewords[p], text[currw]) == 0) {
                    if(p == wordpos - 2) {
                         cout << w+1 << "," ;
                         ocount++;
                    }
                    currw++;
                    p++;
                }
                p = 1;
            }
        }
    }
    cout << ocount << endl;
}

void displaycontext (char text [MAX_WORDS][MAX_CHARS], char sequence [MAX_CHARS], int words, int times) {
    //            
    assert (true);
    /*             
                                                      
    */
    //          
    char *sequencewords [MAX_WORDS];
    for(int i=0; i<MAX_WORDS; i++)
        sequencewords[i] = (char *) malloc(MAX_CHARS);
    //         
    int pos = 0;
    int wordpos = 0;
    int wordlength = 0;
    while(sequence[pos] != '\0') {
        while(sequence[pos] != ' ' && sequence[pos] != '\0') {
            sequencewords[wordpos][wordlength] = sequence[pos];
            pos++;
            wordlength++;
        }
        sequencewords[wordpos][wordlength] = '\0';
        wordlength = 0;
        wordpos++;
        pos++;
    }
    int ocount = 0;
    int currw = 0;
    int p = 1;
    int posit;
    int time = times;
    for(int w = 0; w < words; w++) {
        if(strcmp(sequencewords[0], text[w]) == 0) {
            currw = w + 1;
            if(wordpos == 2) {
                for(int i = w-times; i < w+times+1; i++) {
                    if(i >=0 && i < words) {
                        cout  << text[i] << ",";
                    }
                }
               ocount++;
            } else {
                while(strcmp(sequencewords[p], text[currw]) == 0) {
                    if(p == wordpos - 2) {
                        ocount++;
                        for(int i = w-times; i < w+times+wordpos-1; i++) {
                            if(i >=0 && i < words) {
                                cout  << text[i] << ",";
                            }
                        }
                    }
                    currw++;
                    p++;
                }
                p = 1;
            }
        }
    }
}

int main()
{
    char command [MAX_COMMAND_LENGTH] = "";
    char sequence [MAX_CHARS];
    char text [MAX_WORDS][MAX_CHARS];
    char space [1];
    int words = 0;
    ifstream infile;
    while(strcmp(command, "stop")) {
        cin >> command;
        cin.ignore();
        if(strcmp(command, "enter") == 0) {
            cin.getline(sequence, MAX_CHARS, '\n');
            openfile(sequence, infile, text, words);
        }
        else if (strcmp(command, "content") == 0) {
            displaycontent(text, words);
        }
        else if (strcmp(command, "count") == 0) {
            cin.getline(sequence, MAX_CHARS);
            displaycount(text, sequence, words);
        }
        else if (strcmp(command, "where") == 0) {
            cin.getline(sequence, MAX_CHARS, '\n');
            displaywhere(text, sequence, words);
        }
        else if (strcmp(command, "context") == 0) {
            int times = 0;
            cin >> times;
            cin.ignore();
            cin.getline(sequence, MAX_CHARS, '\n');
            displaycontext(text, sequence, words, times);
        }
        else if (strcmp(command, "stop") != 0) {
            cout << "Command not recognized" << endl;
        }
    }
    return 0;
}

