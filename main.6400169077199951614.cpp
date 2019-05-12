#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <cstring>
#include <string>

using namespace std;

//                                 
//                             

//                                                          
//                                                 

ifstream inputfile;
const int MAX_WORDS = 30000;
const int MAX_CHARS = 60;

char filename [100];
char words [MAX_WORDS][MAX_CHARS];
char word [MAX_CHARS];
char sequence_ask [MAX_WORDS][MAX_CHARS];
int where_index [MAX_WORDS];

double words_in_text = 0.0;
double words_in_function_count = 0.0;

bool enter_filename (char filename [100], ifstream& inputfile)
{
    //               
    assert (!inputfile.is_open());
    //                
    //                              
    inputfile.open(filename);
    if (inputfile.is_open())
    {
        cout << "Opened successfully." << endl;
        return true;
    }
    cout << "Failed to open file." << endl;
    return false;
}

int sequential_search ( char words[MAX_WORDS][MAX_CHARS], int from, int to, char word[MAX_CHARS])
{
    //               
    assert ( 0 <= from && 0 <= to &&  MAX_WORDS > 0 && MAX_CHARS > 0) ;
//                
//                                  
//                                                            
//                      
//                                                                
//                                 
//                          
    if ( from > to )
        return to + 1 ;
    int position = from ;
    while (position <= to && (strcmp(words[position], word) != 0))
        position++ ;
    return position ;
}

bool read_word (ifstream& inputfile, char word [MAX_CHARS])
{
    //              
    assert (inputfile.is_open() && MAX_WORDS > 0 &&  MAX_CHARS > 0);
    //               
    //                                                              
    inputfile >> word ;
    return inputfile;
}

int no = 0;

bool tally_word(char word [MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int& no )
{
    //               
    assert (no >= 0 && MAX_WORDS > 0 &&  MAX_CHARS > 0);
    //                
    //                                                                                     
    int pos = sequential_search(words, 0, no, word);

    if( pos <= no )
        return true;

    else if( pos < MAX_WORDS)
    {
        strcpy( words[pos], word ) ;
        no++ ;
        return true;
    }
    return false;
}

int read_words ( ifstream& inputfile, char words [MAX_WORDS][MAX_CHARS])
{
    //              
    assert (inputfile.is_open() && MAX_WORDS > 0 && MAX_CHARS > 0);
    //               
    //                                                                
    int counter = 0;
    while (read_word(inputfile, word))
    {
        counter++;
        tally_word(word, words, no);
    }
    words_in_text = counter;
    return counter;
}

void show_content (char words [MAX_WORDS][MAX_CHARS])
{
    //               
    assert (MAX_WORDS > 0 && MAX_CHARS > 0);
    //                
    //                                              
    for (int counter = 1; counter <= no; counter++)
    {

        cout << counter << " " << words[counter] << endl;
    }
}

bool get_filename ()
{
    //               
    assert (true);
    //                
    //                                                           
    cin.ignore(1);
    cin.getline(filename, 100, '\n');
    if (enter_filename(filename, inputfile))
    {
        cout << read_words(inputfile, words) << " words read from file.\n" << endl;
        inputfile.clear();
        inputfile.close();
        return true;
    }
    return false;
}

int indexed_amount = 0;

int count_words (char sequence_ask [MAX_WORDS][MAX_CHARS])
{
    //              
    assert (MAX_WORDS > 0 && MAX_CHARS > 0);
    //                
    //                                                                          
    inputfile.open(filename);
    if (!inputfile.is_open())
    {
        cout << "ERROR: Could not open file. Please run enter filename first." << endl;
        return false;
    }

    cin.ignore(1);
    cin >> word;
    char c = '0';
    int pos_ask = 0;
    while (c != '\n')
    {
        cin >> word;
        strcpy(sequence_ask [pos_ask], word);           //                                
        pos_ask++;
        cin.get(c);
    }

    int pos_search = 0;
    inputfile >> word;
    int counter = 0;
    int total = 0;
    int index = 0;
    int counter_index = 0;
    while (inputfile)
    {
        if (strcmp(sequence_ask[pos_search], word) == 0 && pos_search < pos_ask)  //                               
        {
            if (pos_search == 0)
                index = total;          //                                
            pos_search++;
        }

        else if (pos_search == pos_ask)     //                                     
        {
            counter++;
            pos_search = 0;
            where_index[counter_index] = index;
            counter_index++;
            indexed_amount++;

        }

        else
        {
            pos_search = 0;
        }

        inputfile >> word;
        total++;
    }
    inputfile.clear();
    inputfile.close();
    words_in_function_count = counter;
    return counter;
}

void where_is_word ()
{
    //               
    assert (true);
    //                
    //                                   
    if (count_words(sequence_ask))
    {
        cout << "Found at indexes: " << endl;
        for (int counter = 0; counter < indexed_amount; counter++)
        {
            cout << where_index [counter] << endl;
        }
    }
    cout << words_in_function_count << " total matches found." << endl;
}

bool show_console ()
{
    //               
    assert (true);
    //                
    //                                                                                                       
    cout << "What would you like to do?\n" << endl;
    string command;
    cin >> command;

    if (command == "enter")
    {
        get_filename();
        return true;
    }

    if (command == "content")
    {
        show_content(words);
        return true;
    }

    if (command == "stop")
    {
        cout << "Bye!" << endl;
        return false;
    }

    if (command == "count")
    {
        cout << "Times found: " << count_words(sequence_ask) << endl;
        cout << "Total words read: " << words_in_text << endl;
        cout << "Percentage: " << ((words_in_function_count / words_in_text) * 100) << "%" << endl;
        return true;
    }

    if (command == "where")
    {
        where_is_word();
        return true;
    }

    if (command == "context")
    {

    }
}

int main()
{
    while(show_console())
    {

    }
}

