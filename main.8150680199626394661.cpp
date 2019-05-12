#include <iostream>
#include <fstream>
#include <cassert>

//                               
//                        

using namespace std;

const int MAX_LENGTH = 128;
const int MAX_WORDS = 30000;
const int MAX_LETTERS = 35;
const int MAX_ENTERED_WORDS = 30;

void enter_filename(char filename[MAX_LENGTH])
{
    assert(true);
    //                                                                                                                                
        char a;
        int x = 0;

        while(a != '\n')
        {
            cin.get(a);
            if( !(x == 0 && a == ' ') && a != '\n')
            {
                filename[x] = a;
                x++;
            }
        }

}

//                                          

bool read_word(ifstream& inputFile, char word[MAX_WORDS][MAX_LETTERS], int wordNumber)
{
    assert(inputFile.is_open() && wordNumber >= 0);
    //                                                                                                         
    inputFile >> word[wordNumber];
    return inputFile;
}

int count_words(ifstream& inputFile, char words[MAX_WORDS][MAX_LETTERS])
{
    assert(inputFile.is_open());
    //                                                                                                                             
    int wordNumber = 0;

    while(read_word(inputFile,words,wordNumber))
    {
        words[wordNumber];
        wordNumber++;
    }
    return wordNumber;
}

void show_content(char words[MAX_WORDS][MAX_LETTERS], int maxWordNumber)
{
    assert(maxWordNumber >= 0);
    //                                                                                                          
    int wordNumber = 0;
    while(wordNumber <= maxWordNumber)
    {
        cout << words[wordNumber] << endl;
        wordNumber++;
    }

}

void count_specific_words(char words[MAX_WORDS][MAX_LETTERS], int length)
{
        assert(length >= 0);
        //                                                                                                                                                                  
        string word;
        cin >> word;
        int position = 0;
        int frequency = 0;

        while(position < length)
        {
            if(words[position] == word)
                frequency++;
            position++;
        }
        int percentage_words = (frequency*100/length);

        cout << endl << frequency << "\t" << length << "\t" << percentage_words << "%" << endl;
}

void position_words(char words[MAX_WORDS][MAX_LETTERS], int length)
{
        assert(length >= 0);
        //                                                                                                                         
        string word;
        int location_words[length];
        cin >> word;
        int position = 0;
        int frequency = 0;
        int order = 0;
        while(position < length)
        {
            if(words[position] == word)
            {
                location_words[frequency] = position + 1;
                frequency++;
            }

            position++;
        }

        cout << "The places where this word(s) are located are: \n";
        while (order < frequency)
        {
          cout << location_words[order] << "\t";
          order++;
        }
        cout << endl << frequency<< endl;
}

void context(char words[MAX_WORDS][MAX_LETTERS], int length)
{
        assert(length >= 0);
        //                                                                                                                                                 
        string word;
        int location_words[length];
        int m;
        cin >> m;
        cin >> word;
        int position = 0;
        int frequency = 0;
        int order = 0;
        while(position < length)
        {
            if(words[position] == word)
            {
                location_words[frequency] = position + 1;
                frequency++;
            }

            position++;
        }

        while (order < frequency)
        {
            int x = m;
            while(-x != m)
            {
                cout << words[location_words[order]-x] << "\t";
                x--;
            }
            cout << endl;
            order++;
        }
        cout << endl << frequency<< endl;
}

void recognizing_command()
{
    assert(true);
    //                                                                                                                    

    bool continuing = true;

    while(continuing)
    {
        typedef string command;
        command input_order;

        char filename[MAX_LENGTH];
        ifstream inputFile;

        cin >> input_order;
        char words[MAX_WORDS][MAX_LETTERS];
        int output_count_words;

        if(input_order == "enter")
        {
            enter_filename(filename);
            inputFile.open(filename);

            if(inputFile.is_open())
            {
                output_count_words = count_words(inputFile,words);
                cout << output_count_words << endl;
            }

            else if(!inputFile.is_open())
                cout << "error, wrong filename" << endl;
        }
        else if(input_order == "content")
            show_content(words,output_count_words);

        else if(input_order == "stop")
            continuing = false;

        else if(input_order == "count")
            count_specific_words(words,output_count_words);

        else if(input_order == "where")
            position_words(words,output_count_words);

        else if(input_order == "context")
            context(words,output_count_words);

    }

}

int main()
{
    cout << "Enter the command (always in lowercase letters): ";

    recognizing_command();

    return 0;
}

