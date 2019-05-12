#include <iostream>
#include <fstream>
#include <cassert>
#include <windows.h>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

//           
//                               
//                       

const int MAX_WORDS = 30000;              //                                                                                   
const int MAX_WORD_LENGTH = 50;
const int MAX_SEARCH_WORDS = 20;

int sequential_search(char words[MAX_WORDS][MAX_WORD_LENGTH], char reference_string[MAX_WORD_LENGTH], int from, int to)
{
    assert(from <= to);
    //                                                                                   

    while(strcmp(words[from], reference_string)&& from <= to)
    {
        from++;
    }
    if(!strcmp(words[from], reference_string))
    {
        return from;
    }
    return to + 1;
}

void read_input(string& action, string& text)
{
    assert(true);
    //                                                                          

    cout << "Choose an action and what to apply it to:\n";
    cin >> action;
    char dummy;
    cin.get(dummy);
    getline(cin, text);
}

int split_text(string text, char sequence[MAX_SEARCH_WORDS][MAX_WORD_LENGTH])
{
    assert(true);
    //                                                                                                   

    istringstream iss(text);
    int n = 0;

    while(iss)
    {
        iss >> sequence[n];
        n++;
    }

    return n-1;
}

void enter_filename(string& text, char words[MAX_WORDS][MAX_WORD_LENGTH], int& word_count)
{
    assert(true);
    //                                                                                                                 

    ifstream infile;
    word_count = 0;
    infile.open(text.c_str());

    if(!infile)
    {
        cout << "Failed to open the file. Try again.\n";
        return;
    }
    while(infile)
    {
        infile >> words[word_count];
        word_count++;
    }
    cout << "The amount of words in the file is: " << word_count << endl;
    infile.close();
}

void show_content(char words[MAX_WORDS][MAX_WORD_LENGTH], int& word_count)
{
    assert(word_count >= 0);
    //                                                        

    for(int i = 0; i < word_count; i++)
    {
        cout << words[i] << "\n";
    }
}

void count_sequence(char words[MAX_WORDS][MAX_WORD_LENGTH], string text, int word_count)
{
    assert(word_count >=0);
    //                                                                                                                                                         

    char sequence[MAX_SEARCH_WORDS][MAX_WORD_LENGTH];
    int text_length = split_text(text, sequence);
    int start = -1;
    int counter = 0;

    while(start <= word_count-text_length)
    {
        int succes = 1;
        start = sequential_search(words, sequence[0], start+1, word_count-text_length);
        for(int i = 0;i < text_length; i++)
        {
            if(strcmp(words[start+i], sequence[i]))
            {
               succes = 0;
            }

        }
        counter += succes;
    }
    cout << "The number of appearances of your sequence is: " << counter << "\n";
    cout << "The total number of words in the text is: " << word_count << "\n";
    cout << "The sequence is " << static_cast<double>(text_length*counter*100)/word_count << "%.\n";
}

void where(char words[MAX_WORDS][MAX_WORD_LENGTH], string text, int word_count)
{
    char sequence[MAX_SEARCH_WORDS][MAX_WORD_LENGTH];
    int text_length = split_text(text, sequence);
    int start = -1;
    int counter = 0;

    while(start <= word_count-text_length)
    {
        int succes = 1;
        start = sequential_search(words, sequence[0], start+1, word_count-text_length);
        for(int i = 0;i < text_length; i++)
        {
            if(strcmp(words[start+i], sequence[i]))
            {
               succes = 0;
            }

        }

        if (succes)
        {
            counter++;
            cout << "Index = " << start+1 << endl;
        }
    }
    cout << "The number of appearances of your sequence is: " << counter << "\n";
}

void context(char words[MAX_WORDS][MAX_WORD_LENGTH], string text, int word_count)
{
    assert(word_count >= 0);
    //                                                                                            

    char sequence[MAX_SEARCH_WORDS][MAX_WORD_LENGTH];
    int text_length = split_text(text, sequence)-1;
    int counter = 0;
    int m = atoi(sequence[0]);

    int start = -1+m;
    cout << "The occurrences are: \n";
    while(start <= word_count-text_length-m)
    {
        int succes = 1;
        start = sequential_search(words, sequence[1], start+1, word_count-text_length-m);
        for(int i = 0;i < text_length; i++)
        {
            if(strcmp(words[start+i], sequence[i+1]))
            {
               succes = 0;
            }

        }

        if (succes)
        {
            counter++;

            for(int i = start-m; i < start + text_length + m; i++ )
            {
                cout << words[i] << " ";
            }
            cout << "\n";
        }
    }
    cout << "\nThe number of appearances of your sequence is: " << counter << "\n";
}

int choose_action(string& action)
{
    assert(true);
    //                                                     

    if(action == "enter")
    {
        return 1;
    }
    else if(action == "content")
    {
        return 2;
    }
    else if(action == "count")
    {
        return 3;
    }
    else if(action == "where")
    {
        return 4;
    }
    else if(action == "context")
    {
        return 5;
    }
    else if(action == "stop")
    {
        return 0;
    }
    else
    {
        return 6;
    }
}

int main ()
{
    string action;
    string text;
    char words [MAX_WORDS][MAX_WORD_LENGTH];
    int word_count;

    do
    {
        read_input(action, text);

        switch (choose_action(action))
        {
            case 0: break;
            case 1: enter_filename(text, words, word_count); break;
            case 2: show_content(words, word_count); break;
            case 3: count_sequence(words, text, word_count); break;
            case 4: where(words, text, word_count); break;
            case 5: context(words, text, word_count); break;
            default: cout << "Invalid input. Try again.\n"; break;
        }
    }
    while(action != "stop");

}

