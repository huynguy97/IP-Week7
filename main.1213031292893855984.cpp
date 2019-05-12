#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <stdlib.h>

using namespace std;

const int MAX_FILENAME_LENGTH = 80;
const int MAX_WORDS = 30000;
const int MAX_CHARS = 80;

const char ENTER[] = {"enter"};
const char CONTENT[] = {"content"};
const char STOP[] = {"stop"};

bool check_words_occurences (char *words[MAX_WORDS], char new_word[MAX_CHARS], int freqs[MAX_WORDS], int no_of_read_words)
{
    //              
    assert(true);
    //               
    //                                                                                                          
    int i = 0;
    while(strcmp( words[i], new_word) && i < no_of_read_words)
        i++;

    if(! strcmp(words[i], new_word))
    {
        freqs[i]++;
        return 0;
    }
    else
    {
        copy(new_word, new_word+MAX_CHARS, words[i]);        //                           
        freqs[i] = 1;
        return true;
    }
}

int count_words( ifstream& infile, char *words[MAX_WORDS], int freqs[MAX_WORDS], int& no_of_read_words)
{
    //              
    assert(true);
    //                
    char read_word[MAX_CHARS];

    while(infile && no_of_read_words < MAX_WORDS)
    {
        infile >> read_word;
        infile.get();  //                
        if (check_words_occurences(words, read_word, freqs, no_of_read_words))
            no_of_read_words++;
    }
    return no_of_read_words;
}

void read_file (ifstream& infile, char *words[MAX_WORDS], int freqs[MAX_WORDS], char filename[MAX_FILENAME_LENGTH], int& no_of_read_words)
{
    //               
    assert(strlen(filename) <= MAX_FILENAME_LENGTH && strlen(filename) > 0);
    //               
    //                                                                                                                                            
    infile.open(filename);
    cout << "file opened" << endl;
    cout << count_words(infile, words, freqs, no_of_read_words) << " words were read from the file." << endl;
    infile.close();
}

void show_content (char *words[MAX_WORDS], int freqs[MAX_WORDS], int no_of_read_words)
{
    //               
    assert(no_of_read_words > 0);
    //                
    //                                                    
    cout << "Word:               frequency:" << endl;

    for (int i = 0; i < no_of_read_words; i++)
    {
        cout << words[i] << "     " << freqs[i] << endl;
        i++;
    }
}

void user_interaction (ifstream& infile, char *words[MAX_WORDS], int freqs[MAX_WORDS])
{
    //               
    assert(true);
    //                
    bool run = true;
    int no_of_read_words = 0;
    while(run)
    {
        char command[50];
        char argument[100];
        cout << "awaiting user command >";
        cin >> command;

        cin.get(); //                          
        cin.getline(argument, 100);

        cout << "command:" << (command) << endl;
        cout << "argument:" << argument << endl;
        if( ! strcmp(command, ENTER))
            read_file(infile, words, freqs, argument, no_of_read_words);

        else if (! strcmp(command, CONTENT))
            show_content(words, freqs, no_of_read_words);

        else if (! strcmp(command, STOP))
            run = false;

        else
            cout << "could not find command:" << command << endl;
    }
}

int main()
{
    ifstream infile;
    //                
    //                                                                                                     
    char *words[MAX_WORDS];
    for(int i = 0; i<MAX_WORDS; i++) {
        words[i] = (char *) malloc(MAX_CHARS);
    }
    //                
    int freqs[MAX_WORDS] ;
    for(int i = 0; i<MAX_WORDS; i++)
        freqs[i] = 0;

    user_interaction(infile, words, freqs);
    return 0;
}

