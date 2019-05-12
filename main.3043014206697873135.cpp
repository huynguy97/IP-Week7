//                              
//                                

#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_FILENAME_LENGTH = 80;
const int MAX_WORDS = 30000;

ifstream inputfile;

bool open_inputfile (ifstream& inputfile, char filename [MAX_FILENAME_LENGTH])
{
    //              
    assert (!inputfile.is_open());

    //               
    //                                                                                                                                                            
    cin.get();
    cin.getline(filename, MAX_FILENAME_LENGTH, '\n');
    inputfile.open (filename);
    return inputfile.is_open();
}

void read_file (ifstream& inputfile, string stored_words [MAX_WORDS], int& word_count)
{
    //              
    assert (inputfile.is_open());

    //              
    //                                                                                                                                                                                                                                      
    string word;
    int index = 0;

    while (inputfile >> word)
    {
        stored_words[index] = word;
        index++;
    }

    inputfile.clear ();
    inputfile.close ();
    word_count = index;
}

int enter_search_value (string search_value[MAX_WORDS])
{
    //              
    assert (true);

    //               
    //                                                                                                                                                                                    
    int search_value_count = 0;

    while(cin.get() != '\n')
    {
        cin >> search_value[search_value_count];
        search_value_count++;
    }
    return search_value_count;
}

void sequential_search (string stored_words [MAX_WORDS], int word_count, string search_value [MAX_WORDS], int search_value_count, int& frequency, int positions [MAX_WORDS])
{
    //              
    assert (true);

    //               
    //                                                                                         
    int index;
    int index2;

    for (index = 0;  index < word_count; index++)
    {
        bool equality = true;
        for (index2 = 0; index2 < search_value_count; index2++)
        {
            if (search_value[index2] != stored_words[index+index2])
            {
                equality = false;
            }
        }
        if (equality){
            positions[frequency] = index;
            frequency++;
        }
    }

}

int main()
{
    bool exit = false;
    string stored_words [MAX_WORDS];
    int word_count = 0;

    string command;
    cin >> command;

    while (!exit)
    {
        if (command == "enter")
        {
            char filename [MAX_FILENAME_LENGTH];

            if (open_inputfile (inputfile, filename))
            {
                cout << filename << " successfully opened." << endl;
                read_file(inputfile, stored_words, word_count);
                cout << word_count << " words counted" << endl;
            }

            else
                cout << filename << " could not be opened. Please try a different file." << endl;

        }

        else if (command == "content")
        {
            if (word_count > 0)
            {
                for (int i = 0; i < word_count; i++)
                {
                    cout << stored_words[i] << " ";
                }
            }
            else
                cout << "No file entered. Please enter a file first." << endl;

            cout << endl;
        }

        else if (command == "stop")
        {
            exit = true;
        }

        else if (command == "count")
        {

            string search_value[MAX_WORDS];
            int search_value_count = enter_search_value(search_value);
            int frequency = 0;
            int positions [MAX_WORDS];

            sequential_search(stored_words, word_count, search_value, search_value_count, frequency, positions);

            cout << "Number of occurrences: " << frequency << endl;
            cout << "Total number of words: " << word_count << endl;
            cout << "Percentage: " << (frequency*100.0)/word_count << "%" << endl;
        }

        else if (command == "where")
        {

            string search_value[MAX_WORDS];
            int search_value_count = enter_search_value(search_value);
            int frequency = 0;
            int positions [MAX_WORDS];

            sequential_search(stored_words, word_count, search_value, search_value_count, frequency, positions);

            cout << "Index-positions: ";
            for (int i = 0; i < frequency; i++)
            {
                cout << 1+positions[i] << ", ";
            }
            cout << "\nNumber of occurrences: " << frequency << endl;
        }

        else if (command == "context")
        {
            //                          
        }

        else
        {
            cout << command << " is an invalid command. Please enter a valid command." << endl;
        }

        if (!exit)
            cin >> command;
    }

    return 0;
}
