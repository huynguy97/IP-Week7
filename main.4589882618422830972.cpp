#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

int const MAX_FILENAME = 80;
int const MAX_WORD_SEARCH = 80;
int const MAX_COMMAAND = MAX_FILENAME + 6;
int const MAX_WORDS = 30000;
int const MAX_CHARS = 60;

bool compare_char_array(char array1 [], char array2 [], int length)
{
    //            
    assert(length >= 0);

    //                                                                                                

    for(int i = 0; i < length; i++)
    {
        if(array1[i] != array2[i])
            return false;
    }
    return true;
}

void get_substring(char original[], char substring[], int start, int length)
{
    //            
    assert(length >= 0 && start >= 0);

    //                                                                                                                      

    for(int i = 0; i < length; i++)
        substring[i] = original[i + start];
}

int read_words(ifstream& infile, char words[MAX_WORDS][MAX_CHARS])
{
    //            
    assert (infile.is_open());

    //              
    //                                                                      

    int total_words = 0;

    do
    {
        infile >> words[total_words];
        if(infile)
        {
            total_words++;
        }

    }while(infile);

    cout << total_words << " words were read." << endl;
    return total_words;
}

void show_content(char words[MAX_WORDS][MAX_CHARS])
{
    //            
    assert(true);

    //              
    //                                                                                            

    int i = 0;
    while(i < MAX_WORDS)
    {
        if(words[i][0] == '\0')
        {
            i = MAX_WORDS;
        }
        else
        {
            cout << words[i] << endl;
            i++;
        }
    }
}

bool find_word(char words[MAX_WORDS][MAX_CHARS], char word [MAX_CHARS], int from, int& last_searched)
{
    //            
    assert(from >=0);

    //              
    //                                                                                                                                                   

    int i = 0; //                               
    int w = from; //                                  

    int l = 0;
    while(l < MAX_CHARS && w < MAX_WORDS)
    {
        if (words[w][l] == word[i])
        {
            if(words[w][l] == '\0')
            {
                last_searched = w;
                return true;
            }

            l++;
            i++;
        }
        else if(word[i] == ' ' && words[w][l] == '\0')
        {
            i++;
            w++;
            l = 0;
        }
        else
        {
            w++;
            l = 0;
        }
    }

    return false;
}

//                                                   
//                                                   

int main()
{
    char content_string [] = { 'c', 'o', 'n', 't', 'e', 'n', 't' };
    char stop_string [] = { 's', 't', 'o', 'p' };
    char enter_string [] = { 'e', 'n', 't', 'e', 'r', ' '};
    char count_string [] = {'c','o','u','n','t', ' '};

    char words [MAX_WORDS][MAX_CHARS];
    char command [MAX_COMMAAND];

    int word_count = 0;
    //                      

    do
    {
        cout << "Enter a command:" << endl;
        cin.getline(command, MAX_COMMAAND, '\n');

        //      
        //                
        if(compare_char_array(command, content_string, 7))
        {
            show_content(words);
        }
        //                        
        else if(compare_char_array(command, enter_string, 6))
        {
            char filename [MAX_FILENAME];
            get_substring(command, filename, 6, MAX_FILENAME + 6);
            ifstream inputfile(filename);

            if(inputfile)
                word_count = read_words(inputfile, words);
            else
                cout << "Failed to open file!" << endl;
        }

        //       
        //                                
        else if(compare_char_array(command, count_string, 5))
        {
            char word [MAX_CHARS];
            get_substring(command, word, 6, MAX_WORD_SEARCH);
            int from = 0;
            int last_found = 0;
            int counter = 0;

            while(find_word(words, word, from, last_found))
            {
                counter++;
                from = last_found + 1;
            }

            cout << counter << "," << word_count << "," << (counter * 1.0) / word_count * 100.0 << endl;
        }
    }
    //              
    while(!compare_char_array(command, stop_string, 4));

    return 0;
}

