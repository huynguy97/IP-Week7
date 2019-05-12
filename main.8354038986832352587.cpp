#include <iostream>
#include <fstream>
#include <cassert>

//                                                

using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

bool open_text_file (ifstream& infile)
{
    //                      
    assert(true);

    char filename [80];

    cout << "Please enter the filename: ";
    cin.getline(filename, 80, '\n') ;

    infile.open(filename);

    return infile.is_open();
}

bool count_words (ifstream& infile, string words [MAX_WORDS], int& word_count)
{
    word_count = 0;
    infile >> words[word_count];
    while (infile)
    {
        word_count++;
        infile >> words[word_count];
    }

    return infile;
}

void display_frequencies(int freqs[MAX_WORDS], string words [MAX_WORDS], int& word_count )
{
    string givenword;
    int freq_given = 0;
    double percentage = 0.0;

    cout << "from which word do you want to know the frequency? " << endl;
    cin >> givenword;

    for(int k = 0; k <= word_count ; k++)
    {
        if (givenword == words[k])
        {
            freq_given++;
        }
    }
    percentage = 100* freq_given/word_count;
    cout << "The frequency of " << givenword << " is " << freq_given << endl;
    cout << "This is " << percentage << "% of the text" << endl;
}

void display_context(int freqs[MAX_WORDS], string words [MAX_WORDS], int& word_count )
{
    string givenword;
    int freq_given = 0;
    double percentage = 0.0;
    int m;
    int occur = 0;

    cout << "From which word do you want to know the context " << endl;
    cin >> givenword;
    cout << "And how many words around it do you want to know " << endl;
    cin >> m;

    for(int k = 0; k <= word_count ; k++)
    {
        if (givenword == words[k])
        {
            for (int x = 0; x <= m; x++) {
                cout << words[k+x] << " " ;
                cout << words[k-x] << " " ;
            }
            occur++;
            cout << ", ";
        }
    }
    cout << "Total occurrences: " << occur;
}

void display_where(int freqs[MAX_WORDS], string words [MAX_WORDS], int& word_count )
{
    string givenword;
    int freq_given = 0;

    cout << "from which word do you want to know where it is? " << endl;
    cin >> givenword;
    cout << "The given words are on this/these positions(s): ";

    for(int k = 0; k <= word_count ; k++)
    {
        if (givenword == words[k])
        {
            freq_given++;
            cout << k+1 << " ";
        }
    }
}

int main()
{
    string action;
    string words [MAX_WORDS];
    string input_words [MAX_WORDS];
    int word_count;

    int input_count;
    int freqs[MAX_WORDS];
    ifstream infile;

    if (!open_text_file(infile))
    {
        return -1;
    }

    cout << "Do you want to see the wordcount, frequencies, where, context or stop? " << endl;
    cin >> action;

    if (action == "wordcount")
    {
        count_words(infile, words, word_count);
        cout << "There are " << word_count << " words in the given file." << endl;
    }
    else if (action == "frequencies")
    {
        count_words(infile, words, word_count);
        display_frequencies(freqs, words, word_count);
    }
    else if (action == "where")
    {
        count_words(infile, words, word_count);
        display_where(freqs, words, word_count);
    }
    else if (action == "context")
    {
        count_words(infile, words, word_count);
        display_context(freqs, words, word_count);
    }
    else if (action == "stop")
    {
        return 0;

    }
    else
    {
        cout << "Sorry, I do not know that command :(";
        return -1;
    }

//                                          

    return 0;
}

