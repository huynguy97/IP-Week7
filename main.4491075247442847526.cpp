#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstdlib>
#include <cstring>
#include <istream>
using namespace std;

typedef string Command;
enum Commands {Enter, Content, Stop, Count, Where, Context};
const int MAX_WORDS = 30000;
const int MAX_CHARS = 50;
const int COMMANDS = 6;
Command commands [COMMANDS] = {"enter", "content", "stop", "count", "where", "context"};

/*
                                
                                
*/

void word_counter(ifstream& infile)
{
    //             
        assert(infile.is_open());
    //              
    //                                                                                                          
    int counter = 0;
    char word[MAX_CHARS];
    infile >> word;
    while(infile)
    {
        counter++;
        infile >> word;

    }
    cout << "There are " << counter << " words in the file.\n";
    infile.close();
}

bool open_text_file(ifstream& infile, string filename)
{
    //             
        assert(!infile.is_open());
    //               
    //                                       
    infile.open(filename.c_str());
    if(infile.is_open())
    {
        cout << filename << " has been opened\n";
        word_counter(infile);
        infile.open(filename.c_str()); //                                                                                                                     
    }
    return infile.is_open();
}

bool read_word(ifstream& infile, char next [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS])
{
    //             
        assert(infile.is_open());
    //               
    //                                                                                      
    infile >> next;
    return infile;
}

int sequential_search(char words[MAX_WORDS][MAX_CHARS], int from, int to, char search_value[MAX_CHARS])
{
    //             
        assert(from <= MAX_WORDS);
        assert(to <= MAX_WORDS);
    //              
    //                                                                       
    if (from > to)
        return to + 1;
    int position = from;
    while(position <= to && strcmp(words[position], search_value))
        position++;
    return position;
}

void tally_word(char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int& no)
{
    //             
        assert(true);
    //              
    //                                                           
    int pos = sequential_search(words, 0, no, word);
    if(pos<no)
        freqs[pos]++;
    else if(pos<MAX_WORDS)
    {
        strcpy(words[pos],word);
        no++;
    }
}

void display_frequencies(char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int no)
{
    //             
        assert(no>0);
    //              
    //                                                   
    for(int i = 0; i < no; i++)
        cout << words [i] << '\t' << freqs [i] +1 << '\n';
}

int count_words(ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS])
{
    //             
        assert(infile.is_open());
    //              
    //                                                                                                   
    int no = 0;
    char next [MAX_CHARS];
    while(read_word(infile, next, words)) {
        tally_word(next, words, freqs, no);
    }
    display_frequencies(words, freqs, no);
    return no;
}

int main()
/*
                                                                                                                                                                                                     
                                                                                                                                                                                                           
                                                                                                                                                                                                            
                                                                                                                                                                                                         
                
*/
{
    ifstream infile;
    char words [MAX_WORDS][MAX_CHARS];
    int freqs [MAX_WORDS];
    Command command;
    Command rest;
    char remainder [MAX_CHARS];
    cin >> command;
    while(command != commands[Stop])
    {
        if(command == commands[Enter])
        {
            cin.ignore(1);
            getline(cin, rest, '\n');
            open_text_file(infile, rest);
        }
        else if(command == commands[Content])
        {
            count_words(infile, words, freqs);
        }
        else if(command == commands[Count])
        {
            char new_words [MAX_WORDS][MAX_CHARS];
            cin.ignore(1);
            for(int i = 0; i<MAX_CHARS;i++)
            {
                cin.getline(remainder, MAX_CHARS, ' ');
                strcpy(new_words[i],remainder);
            }
            count_words(infile, new_words, freqs);
        }
        else if(command == commands[Where])
        {
            char new_words [MAX_WORDS][MAX_CHARS];
            cin.ignore(1);
            int no = 0;
            for(int i = 0; i<MAX_CHARS;i++)
            {
                cin.getline(remainder, MAX_CHARS, ' ');
                strcpy(new_words[i],remainder);
            }
            tally_word(remainder, words, freqs, no);
        }
        else if(command == commands[Context])
        {
            cin.ignore(1);
            cin.getline(remainder, MAX_CHARS, '\n');
            cout << "Context - " << rest;
            //                  
        }
        cin >> command;
    }
    infile.close();
    return 0;
}

