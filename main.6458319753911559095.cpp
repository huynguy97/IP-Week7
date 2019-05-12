#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>

//                                                      

using namespace std;

const int MAX_FILENAME_LENGTH = 80;
const int MAX_WORDS = 50000;
const int MAX_WORD_LENGTH = 50;
const int MAX_SEQUENCE_LENGTH = 200;

char word_storage [MAX_WORDS][MAX_WORD_LENGTH];
char words_in_sequence [MAX_WORDS][MAX_WORD_LENGTH];
int total_words = 0;
int amount_words_in_sequence = 0;

bool store_words (ifstream& infile, char word_storage [MAX_WORDS][MAX_WORD_LENGTH])
{
    //               
    assert (true);
    //                
    //                                                                                 

    int i = 0;

    while (infile && i <= MAX_WORDS)
    {
        infile >> word_storage[i];
        i++;
    }

    total_words = i - 1;

    return (i > 0);
}

bool enter_filename (ifstream& infile)
{
    //               
    assert (true);
    //                
    //                                                                                                                                             

    char filename [MAX_FILENAME_LENGTH];

    cout << "Please enter filename: ";

    cin.getline(filename, MAX_FILENAME_LENGTH, '\n');

    infile.open(filename);

    if (!infile.is_open())
    {
        return false;
    }

    return store_words(infile, word_storage);
}

void report_to_user ()
{
    //               
    assert (true);
    //                
    //                                                                                       

    if (enter_filename && store_words)
    {
        cout << "The total number of words in this file is " << total_words << "." << endl;
    }
    else
    {
        cout << "Something went wrong while reading the file." << endl;
    }
}

void show_content ()
{
    //               
    assert (enter_filename && store_words);
    //                
    //                                                                                                              

    int i = 0;
    while (i < total_words)
    {
        cout << word_storage[i] << " ";
        i++;
    }
}

void input_conversion (string word_input)
{
    //               
    assert (word_input.length() < MAX_SEQUENCE_LENGTH);
    //                
    //                                                

    char char_word_input[word_input.length()+1];
    strcpy(char_word_input, word_input.c_str());

    int a = 0;
    int b = 0;

    while (a < MAX_WORDS) //              
    {
        while (b < MAX_WORD_LENGTH)
        {
            words_in_sequence[a][b] = '\0';
            b++;
        }

        a++;
        b = 0;
    }

    int i = 0;
    int j = 0;
    int k = 1;

    while (i < MAX_WORDS)
    {
        if (char_word_input [k] == ' ')
        {
            i++;
            j = 0;
            k++;
        }
        else if (char_word_input [k] == '\0')
        {
            amount_words_in_sequence = i+1;
            i = MAX_WORDS;
        }
        else
        {
            words_in_sequence [i][j] = char_word_input [k];
            j++;
            k++;
        }
    }
}

void count_word (string word_input)
{
    //               
    assert (word_input.length() < MAX_SEQUENCE_LENGTH);
    //                
    //                                                                    

    input_conversion(word_input);

    int a = 0;
    int c = 0;
    double freq = 0.00;

    while (c < total_words)
    {
        if (strcmp(words_in_sequence[a], word_storage[c]) == 0)
        {
            while (strcmp(words_in_sequence[a], word_storage[c]) == 0 && a < amount_words_in_sequence)
            {
                a++;
                c++;
            }

            if (a == amount_words_in_sequence)
            {
                freq++;

                a = 0;
                c++;
            }
            else
            {
                a = 0;
                c++;
            }
        }

        else
        {
            c++;
        }
    }

    cout << "The frequency is " << freq << "." << endl;
    cout << "The total number of words in the text is " << total_words << "." << endl;
    cout << "The percentage of occurences compared to total number of words is " << freq/total_words*100.00 << "%." << endl;
}

void where_word (string word_input)
{
    //               
    assert (word_input.length() < MAX_SEQUENCE_LENGTH);
    //                
    //                                                               

    input_conversion(word_input);

    int a = 0;
    int c = 0;
    double freq = 0.00;
    int index [30000];

    while (c < total_words)
    {
        if (strcmp(words_in_sequence[a], word_storage[c]) == 0)
        {
            while (strcmp(words_in_sequence[a], word_storage[c]) == 0 && a < amount_words_in_sequence)
            {
                a++;
                c++;
            }

            if (a == amount_words_in_sequence)
            {
                index[(int)freq] = c - a + 1;
                freq++;

                a = 0;
                c++;
            }
            else
            {
                a = 0;
                c++;
            }
        }

        else
        {
            c++;
        }
    }

    cout << "The index positions are ";
    int j = 0;

    while (j < freq)
    {
        cout << index[j] << " ";
        j++;
    }

    cout << "\nThe frequency is " << freq << "." << endl;
}

void context_word (string word_input)
{
    //               
    assert (word_input.length() < MAX_SEQUENCE_LENGTH);
    //                
    //                                                   

    input_conversion(word_input);

    int m = atoi(words_in_sequence[0]);

    int a = 1;
    int c = 0;
    double freq = 0.00;

    while (c < total_words)
    {
        if (strcmp(words_in_sequence[a], word_storage[c]) == 0)
        {
            while (strcmp(words_in_sequence[a], word_storage[c]) == 0 && a < amount_words_in_sequence)
            {
                a++;
                c++;
            }

            if (a == amount_words_in_sequence)
            {
                freq++;

                int q = -m;

                while (q < m)
                {
                    cout << word_storage[c + q] << " ";
                    q++;
                }
                cout << "\n";

                a = 1;
                c++;
            }
            else
            {
                a = 1;
                c++;
            }
        }

        else
        {
            c++;
        }
    }

    cout << "\nThe frequency is " << freq << "." << endl;
}

void input_text ()
{
    //               
    assert (true);
    //                
    //                                                           

    cout << "\n\nPossible commands are: content, count, where, context and stop." << endl;
    cout << "Please enter command: ";
}

int ask_user_input ()
{
    //               
    assert (enter_filename && store_words);
    //                
    //                                   

    string command = "empty";
    string word_input = "empty";

    input_text();

    while (command == "empty")
    {
        cin >> command;
        getline(cin, word_input);

        if (command == "content")
        {
            show_content();
            command = "empty";
            input_text();
        }
        else if (command == "count")
        {
            count_word(word_input);
            command = "empty";
            input_text();
        }
        else if (command == "where")
        {
            where_word(word_input);
            command = "empty";
            input_text();
        }
        else if (command == "context")
        {
            context_word(word_input);
            command = "empty";
            input_text();
        }
        else if (command == "stop")
        {
            return 0;
        }
        else
        {
            command = "empty";
            cout << "Please enter a valid command: ";
        }
    }
}

int main()
{
    ifstream infile;

    enter_filename(infile);

    report_to_user();

    ask_user_input();

    infile.close();

    return 0;
}

