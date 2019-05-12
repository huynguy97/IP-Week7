//                     
//                      
//               
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_CHARS = 100;
const int WORDS = 1000;

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    int a = 0;
    char input;
    while (a < 80)
        {
        cin.get(input);
        if (input == '\n')
        {
            filename[a] = '\0';
            return true;
        }
        else
        {
            filename[a] = input;
        }
        ++a;
    }
    return false;
}

bool open_file (ifstream& inputfile, string file)
{
    inputfile.open(file.c_str());
    return inputfile.is_open();
}

bool read_word (ifstream& inputfile, char word[MAX_CHARS])
{
    if (!inputfile.eof())
    {
        inputfile >> word;
        return true;
    }
    return false;
}

int count_words (ifstream& inputfile, char words[WORDS][MAX_CHARS])
{
    int b = 0;
    char next[MAX_CHARS];
    while (read_word(inputfile, next))
    {
        memcpy(words[b], next, sizeof(next));
        ++b;
    }
    cout << b << " words in file.";
    return b;
}

void display_words (char words[WORDS][MAX_CHARS], int b)
{
    for (int i = 0; i < b; i++)
    {
        cout << words [i] << "\n";
    }
}

void count_sequence (char words[WORDS][MAX_CHARS], char sequence[MAX_CHARS], int b)
{
    int d = 0;
    for (int i = 0; i < b; i++)
    {
        if (words[i][0] == sequence[0])
        {
            d++;
        }
    }
    cout << d << ", " << b << ", " << d/b*100;
}

/*                                                                      
 
                  
                      
                        
                                                              
                   
                    
 

                                                                                                 
 
                                                    
                 
     
                      
                    
     
                         
     
                                  
                        
             
                    
     
                 
 */

int main ()
{
    char words[WORDS][MAX_CHARS];
    int b;
    cout << "enter the file name: ";
    char file [MAX_FILENAME_LENGTH];
    enter_filename(file);
    ifstream inputfile;
    open_file(inputfile, file);
    b = count_words (inputfile, words);
    string command;
    while (command != "stop")
    {
        cout << "\n";
        cout << "enter command: ";
        cin >> command;
        if (command == "content")
        {
            display_words (words, b);
        }
        else if (command == "count")
        {
            /*                                          
                                                   */
            char sequence [MAX_CHARS];
            cout << "enter word sequence: ";
            cin.ignore(1);
            char a = cin.get();
            int i = 0;
            while(a != '\n')
            {
                sequence[i];
                a = cin.get();
                i++;
            }
            count_sequence(words, sequence, b);
        }
    }
    return 0;
}

