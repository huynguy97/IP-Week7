//                                                
//                                                  

#include <iostream>
#include <fstream>
#include <cassert>
#include <string.h>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_NAME_LENGTH = 100;
const int MAX_WORDS = 10000;
const int MAX_CHARS = 30;

bool enter_filename (ifstream& file)
{
    assert (!file.is_open());

    char filename[MAX_NAME_LENGTH];
    //                                              
    //                                      

    file.open("desktop.txt");
    return file.is_open();
}

bool read_word (ifstream& file, char word[MAX_CHARS])
{
    file >> word;
    return file;
}

int sequential_search (char data[][MAX_CHARS], int from, int to, char search_value[MAX_CHARS])
{
    assert(0 <= from && 0 <= to);

    if (from > to)
    {
        return to+1;
    }
    int position = from;
    while (position <= to && strcmp(data[position], search_value))
    {
        position++;
    }
    return position;

}

bool tally_word (char word[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int& no)
{
    int pos = sequential_search(words,0,no,word);
    if (pos<no)
    {
        freqs[pos]++;
        no++;
        return true;
    }
    else if (pos<MAX_WORDS)
    {
        if (word != '\0')
        {
            strcpy(words[pos],word);
            freqs[pos]=1;
            no++;
            return true;
        }

    }
    return false;
}

void display_frequencies (char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int no)
{
    for (int i = 1; i<= no; i++)
    {
        cout << words[i] << "\t" << freqs[i] << endl;
    }
}

int count_words (ifstream& file, char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS])
{
    assert (file.is_open());

    int no = 0;
    char c;
    char next_word[MAX_CHARS];

    cout << "Would you like to see the content? (y/n)" << endl;
    cin >> c;
    while (read_word(file,next_word) && tally_word(next_word,words,freqs,no) && no < MAX_WORDS)
    {
        if (c == 'y')
        {
            cout << next_word << " ";
        }
    }
    cout << endl;
    return no;
}

void show_content (ifstream& file, char words[MAX_WORDS][MAX_CHARS])
{
    assert (file.is_open());

    char next_word[MAX_CHARS];
    while (read_word(file, next_word))
    {
        cout << next_word << " ";
    }
}

void searchwhere (char data[MAX_WORDS][MAX_CHARS], char search_values[][MAX_CHARS], int data_length)
{
    int position[MAX_WORDS] = {0};
    bool found = false;

    while (!found)
    {
        for (int i = 0; i < data_length-2; i++)
        {
            position[i+1] = sequential_search(data, position[0] , data_length, search_values[i+1]);
        }
        for (int i = 0; i <= data_length-1; i++)
        {
            if (position[i] != position[i+1]-1)
            {
                fill_n(position,MAX_WORDS,position[1]);
            }
            else if (position[1] == data_length-1)
            {
                cout << "The sequence of words could not be found" << endl;
                found = true;
            }
            else
            {
                cout << position[1] << endl;
                found = true;
            }
        }
    }
}

int main()
{
    ifstream file;
    char words[MAX_WORDS][MAX_CHARS];
    string action;
    int freqs[MAX_WORDS];

    while (action != "ef" && action != "s")
    {
        cout << "Would you like to enter a filename (ef) or stop the program (s)" << endl;
        cin >> action;
    }

    if (action == "s")
    {
        cout << "The program has been stopped" << endl;
        return 0;
    }

    if (action == "ef")
    {
        if (enter_filename(file))
        {
            int total_words = count_words(file,words,freqs);
            cout << "The number of words in the given file is " << total_words << endl;

            display_frequencies(words,freqs,total_words);

            char search_values[MAX_WORDS][MAX_CHARS] = {{"is"},{"a"}}; //                        
            searchwhere(words,search_values,total_words);
        }
        else
        {
            cout << "The given file name could not be opened" << endl;
        }
        file.close();
    }

    return 0;

}

