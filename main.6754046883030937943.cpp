#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>
#include <cstring>
using namespace std;

const int MAX_FILENAME_LENGTH = 80;
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

bool read_word(ifstream& infile, char word [MAX_CHARS])
{
//              
    assert(infile.is_open());
//               
//                                                                          
//                                                              
    infile >> word;
    return infile;
}

int sequential_search(char words [MAX_WORDS][MAX_CHARS], int from, int no, char word [MAX_CHARS] )
{//               
    assert ( 0 <= from && 0 <= no ) ;
//                

    if ( from >= no )
        return no ;
    int position = from ;
    while (position < no && strcmp(words [ position ] , word) != 0)
        position++ ;
    return position ;
}

bool tally_word (char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int& no)
{
//              
    assert(no<MAX_WORDS && word[0]!='\n');
//               
//                                                                                                   
//                                                                                                       
//                                                                      
    int pos = sequential_search( words, 0, no, word ) ;
    if ( pos < no )
    {
        freqs [pos]++ ;
        return true ;
    }
    else if ( pos < MAX_WORDS )
    {
        strcpy ( words [pos], word ) ;
        freqs [pos] = 1 ;
        no++ ;
        return true ;
    }
    return false ;
}

int count_words(ifstream& inputfile, char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS])
{
//              
    assert(inputfile.is_open());
//               
//                                                                                                                                       
//                                               
    int no = 0;
    char next [MAX_CHARS];

    while ( read_word (inputfile, next) && tally_word (next, words, freqs, no) && no < MAX_WORDS )
        ;
    return no;
}

int main()
{
    string command;
    char filename [MAX_FILENAME_LENGTH];
    char c;
    ifstream inputfile;
    char words [MAX_WORDS][MAX_CHARS] ;
    int freqs [MAX_WORDS] ;
    int no;

    cout << "Please enter a command: ";
    cin >> command;
    while(command != "stop")
    {
        if (command == "enter")
        {
            cin.get(c);
            cin.getline(filename, MAX_FILENAME_LENGTH);
            inputfile.open(filename);
            if(!inputfile)
            {
                cout << "File could not be opened.\n";
            }
            else
            {
                no = count_words(inputfile, words, freqs);
            }
        }
        else if (command == "content" )
        {
            for(int i=0;i<no;i++)
                cout <<words[i]<<endl;
            cin.ignore(1000, '\n');
        }
        else if (command == "")

        else
        {
            cout << "Not an eligible command.\n";
            cin.ignore(1000, '\n');
        }

        cout << "Please enter a command: ";
        cin >> command;
    }

}

