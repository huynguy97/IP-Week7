#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <stdio.h>
#include <string.h>

//                                                                                   

using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

bool enter_filename (ifstream& infile)
{
    //              

    assert (!infile.is_open());

    //                 
    /*
                                                                                   
                                                
    */

    cout << "Please enter file name: ";
    char filename [80];
    cin.getline(filename, 80, '\n');
    infile.open(filename);
    return infile.is_open();
}

bool read_word (ifstream& infile, char word [MAX_CHARS])
{
    //              

    assert (infile.is_open());

    //                 
    /*
                                                                         
    */

    infile >> word;

    return infile;

}

int count_words (ifstream& infile, char words [MAX_WORDS][MAX_CHARS])
{

    //              

    assert (infile.is_open());

    //                
    /*
                                                                                    
    */

    int no = 0;
    char next [MAX_CHARS];
    while (read_word(infile, next) && no < MAX_WORDS)
    {
        strcpy (words[no], next);
        no ++;

    }
    return no;
}

void display_words (char words [MAX_WORDS][MAX_CHARS], int output)
{

    //              
    assert (output >= 0 && output < MAX_WORDS);

    //                 
    /*
                                                                                                                      
    */

    for (int i = 0; i < output; i ++)
    {

        cout << words [i] << '\n';
    }

}

void count_word_sequence (char words [MAX_WORDS][MAX_CHARS], int frequency, int output, double percentage)
{
    //             
    assert (output >= 0 && output < MAX_WORDS);

    //                 
    /*
                                                                                                           
                                                                                                                     
    */

    char lookfora[60];
    char lookforb[60];
    char lookforc[60];

    int result;
    frequency = 0;
    cout << "Enter string of maximum three words of which you would like to see the frequency: " << endl;
    cin >> lookfora >> lookforb >> lookforc;

    strcat(lookfora, lookforb);
    strcat(lookfora, lookforc);

    int amount_of_words = 3;

    if (lookforc && !lookforc[0])
    {
     amount_of_words = amount_of_words -1;
    }

    if (lookforb && !lookforb[0])
    {
     amount_of_words = amount_of_words -1;
    }

    for (int i = 0; i < output; i++)
    {
        result = strcmp(lookfora, words[i]);
        if( result = 0)
        {
            frequency ++;
        }
    }
    int singlepercentage = frequency * amount_of_words;
    percentage = singlepercentage / output;

    cout << "The string " << lookfora << " occurs " << frequency << " times in this text" << endl;
    cout << "In total there are " << output << " words in the text.";
    cout << "And your chosen string makes up " << percentage << " percent of the text.";

}

int main()
{

    char filename[80];
    ifstream infile(filename);
    if(!enter_filename(infile))
    {
        cout << "Filename too long!" << endl;
        return -1;
    }

    char words[MAX_WORDS][MAX_CHARS];
    int output;
    output = count_words(infile, words);
    cout << "The number of words in the file is " << output << endl;
    cout << endl;

    display_words(words, output);

    int frequency;
    double percentage;
    count_word_sequence(words, frequency, output, percentage);

    infile.close();
}

