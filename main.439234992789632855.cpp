/*
                                                   
                                                
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <string.h>
using namespace std;

const int max_file_name_size = 100;
const int max_char = 22;
const int max_words = 29705;

int sequential_search(char words[], int from, int to, int search_value)
{
    //                
    assert (0 <= from && 0 <= to);

    //                 
    //                                                       

    //                
    if(from>to)
        return to + 1;
    int position = from;
    while(position <= to && words [position] != search_value)
        position++;
    return position;
}

void enter_filename (char input_filename [max_file_name_size])
{
    //               
    assert (true);
    //                
    //                                                             
    //               

    //                               
    cout << "Please enter the name of the file you wish to open: ";
    //                                                
    cin >> input_filename;
    cout << input_filename << " wait";
}

void check_file_opened(ifstream& input_file)
{
    if (input_file.is_open())
    {
        cout << endl << "File has been opened successfully." << endl;
    }
    else
    {
        cout << endl << "Program failed to open the file.";
    }
}

void display_frequencies(char words[max_words][max_char], int frequencies[max_words], double counter)
{
    //                
    assert (counter > 0 && counter < max_words);

    //                 
    //                                          
    //                
    for(int i = 0; i < counter; i++)
    {
        cout << words[i] << "\t \t \t \t" << "\n";
        cout << "\t \t Occurences: \t \t \t" << frequencies[i] << "\n";
        cout << "\t \t index: \t \t \t " << i + 1 << "\n";
        cout << "\t \t Percentage of occurences: \t" << frequencies[i]/counter * 100 << "\n";
    }
}

bool read_word(ifstream& input_file, char word[max_char])
{
    //               
    assert (input_file.is_open());

    //               
    //                              
    //               
    input_file >> word;
    return input_file;
}

bool tally_word (char word [max_char], char words [max_words][max_char], int frequencies [max_words], int& counter)
{
    //               
    //                                                  
    assert (counter >= 0 && counter < max_words);
    //                
    //                          
    //               

    //                                              
    int position = 0;

    if(0>counter)
        position = counter + 1;
    else
    {
        while(position < counter && words [position] != word)
            position++;
    }

    if (position < counter)
    {
        frequencies [position]++;
    //                                                      
        return true;
    }
    else if (position < max_words)
    {
        int pos = 0;
        while(pos <=position && words[pos] != words[position])
        {
            pos++;
            //                                
        }

        if(pos >= position && pos >= 0)
        {
            strcpy (words [position], word);
            frequencies [position] = 1;
            counter = counter + 1;
        }
        else
        {
           frequencies [pos] = frequencies [pos] + 1;
        }
   }
   return true;
}

int count_words (ifstream& input_file, char words [max_words][max_char],int frequencies [max_words])
{
    //               
    assert (input_file.is_open());
    //                
    //                                                     
    //                
    int counter = 0;
    char next[max_char];
    while(read_word(input_file,next) && tally_word(next,words,frequencies, counter) && counter < max_words);
    return counter;
}

int clean_up(ifstream& input_file, ofstream& output_file)
{
    //               
    assert(true);
    //                
    //                                                         
    //                
    input_file.clear();
    input_file.close();
    output_file.clear();
    output_file.close();

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
}

void open_file(char name_of_file[max_file_name_size], char words[max_words][max_char], int frequencies [max_words],int& nr)
{
    //               
    assert(true);
    //                
    //                                        
    //                
    enter_filename(name_of_file);
    ifstream input_file(name_of_file);
    check_file_opened(input_file);
    nr = count_words(input_file, words, frequencies);
    cout << "The amount of words read is: " << nr << endl;
}

void show_content(char words[max_words][max_char], int counter)
{
    //               
    assert(true);
    //                
    //                                           
    //                
    for(int i = 0; i < counter; i++)
        cout << words[i] << " ";
    cout << endl;
}

void where_is_word(char words[max_words][max_char], int nr)
{
    //               
    assert(true);
    //                
    //                                                           
    //               
    cout << "Which word do you search? Please enter the index number" << endl;
    int search_word;
    cin >> search_word;
    cout << "You are searching for: " << words[search_word] << "." << endl;
    //                                                                                      
    //                                                                                                                  
}

void context_word(char words[max_words][max_char])
{
    //              
    assert(true);
    //               
    //                                                                
    //               
    int position;
    cout << "Enter the position of the word: ";
    cin >> position;
    int margin = -1;
    int errors = 0;
    cout << endl << "How many words before and after your word should be printed? ";
    while(!(margin >= 0 && margin <= position && errors < 100))
    {
        cout << "Please enter an integer between 0 and " << position <<". \n";
        cin >> margin;
        errors++;
    }
    for(int i = position - margin; i <= position + margin; i++)
    cout << words[i]<< endl;
}

int main ()
{
    int user_input;

    int frequencies [max_words];
    int nr;
 //                                         
    char name_of_file [max_file_name_size];

    char words [max_words][max_char];
    while(!(user_input == 2))
    {
        cout << "Enter a command (enter[0], content[1], stop[2], count[3], where[4], context[5]): ";
        cin >> user_input;

        if(user_input == 0 ){
            open_file(name_of_file, words, frequencies, nr);
        }
        else if(user_input == 2){
            cout << "By";
        }
        else if(user_input == 1){
            show_content(words, nr);
        }

        else if(user_input == 4 )
        {
            display_frequencies(words, frequencies, nr);
            where_is_word(words, nr);
        }
        else if(user_input == 5)
            context_word(words);
        }

    cout << endl << endl << endl;

    return 0;
}

