#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_CHARS = 80 ;
const int MAX_WORD_AMOUNT = 30000;

//                       
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    //                                                                                                                    

    cout << "Enter an input file name" << endl;

    char c;
    int index = 0;

    while(cin.get(c))
    {
        if(index < MAX_FILENAME_LENGTH)
        {
            if(c == '\n')
            {
                filename[index] = '\0';
                break;
            }
            else
            {
                filename[index] = c;
            }
            index++;
        }
        else
        {
            if(c != '\n')
            {
                return false;
            }
            else
            {
                filename[MAX_FILENAME_LENGTH] = '\0';
            }
        }
    }

    return true;
}

bool enter_sequence (string sequence [MAX_FILENAME_LENGTH], int& sequence_length)
{
    //               
    assert (true);
    //                                                                                                                    

    cout << "Enter a sequence" << endl;

    char c;
    int index = 0;
    string a;

    while(cin.get(c))
    {
        if(index < MAX_FILENAME_LENGTH)
        {
            if(c == ' ')
            {
                sequence[sequence_length] = a;
                a = "";
                sequence_length++;
            }
            else if(c == '\n')
            {
                sequence[sequence_length] = a;
                sequence_length++;
                break;
            }
            else
            {
                a += c;
            }
            index++;
        }
    }

    return true;
}

void read_words(ifstream& infile, string word_list[MAX_WORD_AMOUNT])
{
    for(int i = 0; i < MAX_WORD_AMOUNT; i++)
    {
        infile >> word_list[i];
    }
}

void total_words(ifstream& infile, string word_list[MAX_WORD_AMOUNT], int& number_of_words)
{
    for(int i = 0; i < MAX_WORD_AMOUNT; i++)
    {
        if(word_list[i].length() > 0)
        {
            number_of_words++;
        }
    }
    cout << "This file has " << number_of_words << " words." << endl;
}

int count_sequence(ifstream& infile, string word_list[MAX_WORD_AMOUNT], int number_of_words)
{
    string sequence[MAX_CHARS];
    int occurencesofsequence[30000];
    int sequence_length = 0;

    enter_sequence(sequence, sequence_length);

    for(int i = 0; i < MAX_WORD_AMOUNT; i++)
    {
        //                   
    }

    int occurences = 0;

    for (int i = 0; i < number_of_words; i++)
    {
        int similarities = 0;

        for (int j = 0; j < sequence_length; j++)
        {
            int k = i + j;
            string fileword = word_list[k];
            //                                                 
            for (int k = 0; k < sequence_length; k++)
            {
                if (sequence[k] == fileword)
                {
                    similarities++;
                }
            }
        }
        if (similarities == sequence_length)
        {
            occurencesofsequence[occurences++] = i + 1;
        }
    }
    return occurences;

}

int main()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream input;
    input.open(filename);

    if(input.is_open())
    {
        cout << "'" << filename << "'" " was opened succesfully." << endl;
    }
    else
    {
        cout << "'" << filename << "'" " was not opened." << endl;
    }

    string word_list[MAX_WORD_AMOUNT];
    int number_of_words = 0;

    read_words(input, word_list);
    total_words(input, word_list, number_of_words);
    cout << "This sequence of words apears " << count_sequence(input, word_list, number_of_words) << " times." << endl;
    cout << "The amount of words in the text is " << number_of_words << "." << endl;
    cout << "The percentage sequence of the text is" << (count_sequence(input, word_list, number_of_words)/number_of_words)*100 << "%." << endl;

    //                                                            
    while (input.is_open())
    {
        cout << "Enter your next action. Your choices are:" << endl;
        cout << "Content, show the contents of the file." << endl;
        cout << "Count, input a sequence of words and receive the frequency of the sequence, the total amount of words in the file and a percentage of your sequence." << endl;
        cout << "Where, take the input sequence and show all index positions of the sequence and display the frequency." << endl;
        cout << "Context, input a extra number m and display the sequence plus m words in front and behind the sequence." << endl;
        cout << "Stop, stop the program." << endl;

        string action;
        cin >> action;

        if (action == "Content")
        {
            cout << "The content of the file is:" << endl;
            for (int i = 0; i < number_of_words; i++) {
                cout << word_list[i] << " ";
            }
            cout << endl << endl;
        }
        else if (action == "Count")
        {
            cout << "This sequence of words apears " << count_sequence(input, word_list, number_of_words) << " times." << endl;
            cout << "The amount of words in the text is " << number_of_words << "." << endl;
            cout << "The percentage sequence of the text is" << (count_sequence(input, word_list, number_of_words)/number_of_words)*100 << "%." << endl;
        }
        else if (action == "Where")
        {

        }
        else if (action == "Context")
        {

        }
        else if (action == "Stop")
        {
            input.close();
            if (!input.is_open())
            {
                cout << "Program terminated." << endl ;
                return 0;
            }
            else
            {
                cout << "File not closed successfully. File might be damaged. Please try again.";
            }
        }
    }
}

