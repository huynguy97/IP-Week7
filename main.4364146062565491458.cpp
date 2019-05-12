#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstdlib>
using namespace std;

//                       
//                     

const int MAX_WORDS = 1000 ;
bool stop(ifstream& );
bool enter_filename (ifstream& infile)
{
    //              
    assert (! infile.is_open());
    //              
    //                                                                   
    cout << "Please enter the file name: " << endl;
    string filename;
    getline(cin, filename);
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        cout << "The file is opened successfully." << endl;
    }
    else
    {
        cout << "The file could not open." << endl;
    }
    return infile.is_open();

}

bool read_word ( ifstream& infile, string& word)
{
    //              
    assert(infile.is_open());
    //               
    //                                

    infile >> word;

    return infile;
}

bool count_words (ifstream& infile, string file [MAX_WORDS])
{
    //              
    assert(true);
    //               
    //                                           
    int i = 0;
    string word;
    while (read_word(infile, word))
    {
        file[i] = word;
        i++;
    }
    cout << "The number of words red is: " << i << endl;
    return i;
}

bool content (ifstream& infile, string word_list [MAX_WORDS])
{
    //              
    assert(true);

    //               
    //                                                 
    int i = 0;
    string word;
    cout << "The list of stored words is: " << endl;
    while (read_word(infile, word))
    {
        word_list[i]  = word;
        cout << word_list[i] << endl;
        i++;
    }

    return i;
}

bool stop (ifstream& infile)
{
    //              
    assert (infile.is_open());
    //               
    //                     
    infile.clear ();
    infile.close ();
    cout << "The file is closed successfully." << endl;

    return true;

}

bool count_given_word (ifstream& infile, string& given_word, string& word, string total_given_word[], string total_word[])
{
    //              
    assert(infile.is_open());
    //              
    //                                                                                
    //                                                                         
    //                                                   
    cin >> given_word;
    int i = 0;
    int j = 0;
    int h = 0;
    while (read_word(infile, word))
    {
        if (given_word == word)
        {
            total_given_word[j] = word;
            j++;
        }
        else
        {
            total_word [h] = word;
            h++;
        }
        i++;
    }
    int totalwords = h + j;
    int frequency  = j;
    double percentage = 100 * j / (h+j);

    cout << "The total number of words in the file is: " << totalwords << endl;
    cout << "The total number of given words in the file is: " << frequency << endl;
    cout << "The percentage of the occurrence of the given word with respect to the total number of words is: " << percentage <<" %"<< endl;

    return true;

}

int main()
{
    ifstream infile;
    string given_word;
    string word;
    string total_given_word[MAX_WORDS];
    string total_word [MAX_WORDS];
    string file[MAX_WORDS];
    string word_list [MAX_WORDS];
    string command;
    enter_filename(infile);
    //                          
    //                           
    //             

    cout << "Enter a command and value" << endl;
    cin >> command;

    if (command == "count")
    {
        count_given_word(infile, given_word, word, total_given_word, total_word );
    }

    return 0;

}

