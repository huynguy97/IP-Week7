//                        

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

const char enter [] = "enter";
const char content [] = "content";
const char stop [] = "stop";
const char wrdcount [] = "count";
const char where [] = "where";
const char context [] = "context";

const int MAX_CHAR = 60;
const int MAX_WORDS = 30000;

int count_words (ifstream& infile, char word [MAX_CHAR])
{
//               
    assert ( true);
//                
//                                             
    int nr = 0;
    do
    {
        nr++;
    }
    while (infile >> word);
    infile.clear();
    infile.seekg(0, ios::beg);
    return nr;
}

void read_word (ifstream& infile, char word[MAX_CHAR])
{
//               
    assert(infile.is_open());
//                
//                                               
    int i = 0;

    do {
        i++;
    }
    while(infile >> word);

    infile.clear();
    infile.seekg(0, ios::beg);
}

void show_words(ifstream& infile, char words[MAX_WORDS][MAX_CHAR])
{
//               
    assert(infile.is_open());
//                
//                                                    
    int i = 0;
    while(infile >> words[i])
    {
        i++;
    }
}

void user_command (char filename[10], ifstream& infile, char word[MAX_CHAR], char words[MAX_WORDS][MAX_CHAR])
{
//               
    assert ( true );
//                
//                                                                            

    char command[10];
    char sequence [200];
    char number [20];
    do
    {
        cout << "Please enter your command, starting with a lowercase letter \n(please enter a space character after your command before hitting enter): " << endl;
        cin.getline ( command, 10, ' ');
        if ( strcmp ( command, enter ) == 0 )
        {
            cin.getline ( filename, 80, '\n');
            infile.clear();
            infile.close();
            infile.open (filename);
            if (infile)
            {
                int nr_of_words = count_words(infile, word);
                cout << "The number of words in this file is: " << nr_of_words-1 << endl;
            }
            else
            {
                cout << "The file could not be opened. Please try again." << endl;
            }
        }
        else if ( strcmp (command, content) == 0 )
        {
            read_word(infile, word);
            show_words(infile, words);
            for (int i = 0; i <= count_words(infile, word); i++)
            {
                for (int j = 0; j < MAX_CHAR; j++)
                {
                    cout << words[i][j] ;
                }
                cout << endl;
            }
        }
        else if ( strcmp (command, wrdcount) == 0 )
        {
            cin.getline ( sequence, 200, '\n');
            cout << sequence << endl;

            /*               
                                                                
             
                                              
                                                          
                                  
                     
             
                                                                                              
                                     
                                                    
                                             
                                                                                             
*/
        }
        else if ( strcmp (command, where) == 0 )
        {
            cin.getline ( sequence, 200, '\n');
            cout << sequence << endl;
        }
        else if ( strcmp (command, context) == 0 )
        {
            cin.getline ( number, 20, ' ');
            cin.getline ( sequence, 200, '\n');
            cout << number << "\t" << sequence << endl;
        }
    }
    while ( strcmp (command, stop) != 0 );
}

int main()
{
    char filename[80];
    char word [MAX_CHAR];
    char words [MAX_WORDS][MAX_CHAR];
    ifstream infile;
    int nr = count_words(infile, word);
    user_command(filename, infile, word, words);
    return 0;
}

