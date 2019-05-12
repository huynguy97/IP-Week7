//                                              
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
using namespace std;

const int MAX_FILE_LENGHT = 80;
const int MAX_WORDS = 3000;
const int MAX_CHARS = 60;
bool enter_filename (ifstream& infile)
{
    //                
    assert(true);
    //                
    //                                                                  
    cout << "Enter file name: ";
    char filename[MAX_FILE_LENGHT];
    cin.getline (filename, MAX_FILE_LENGHT,'\n');
    infile.open (filename);
    if (infile.is_open())
    {
        return infile.is_open();
    }
    else
    {
        cout << "That is not a valid file name.";
        return false;
    }
}

bool read_word (ifstream& infile, char word [MAX_WORDS])
{
    //              
    assert (infile.is_open() && MAX_WORDS >= 0);
    //               
    //                                                                    
    infile >> word;
    return !!infile;
}

int sequential_search (int data[], int from, int to, int search_value)
{
    //              
    assert(0 <= from && 0 <= to);
    //               
    //                                                    
    if (from > to)
        return to + 1;
    int position = from;
    while (position <= to && data [position] != search_value)
        position ++;
    return position;
}
bool tally_word (char word[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int freq[MAX_WORDS], int& no)
{
    //              
    assert(no >= 0 && no < MAX_WORDS);
    //               
    //                                             
    int pos = sequential_search (words, 0, no, word);
    if (pos < no);
    {
        freq [pos]++;
        return true;
    }
    else if (pos < MAX_WORDS)
    {
        strcpy (words[pos],word);
        freq[pos]=1;
        no++
        return true;
    }
    return false;
}

int count_words (ifstream& infile)
{
    //              
    assert(infile.is_open());
    //               
    //                                            
    int no = 0;
    char word [MAX_CHARS];
    while (read_word(infile, word))
        no=no+1;
    cout << no;
    return no;
}

int main()
{
    ifstream infile;
    if (enter_filename(infile))
    {
        char word [MAX_WORDS];
        char words [MAX_WORDS][MAX_CHARS];
        int freq [MAX_WORDS];
        read_word(infile,word);
        cout << word << endl;
        count_words(infile);
    }

}

