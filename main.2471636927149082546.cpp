//                                                      
#include <iostream>
#include <cassert>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <string>
using namespace std;

int const MAX_CHARS=60;
int const MAX_WORDS=30000;
char word [MAX_CHARS];
string words [MAX_WORDS];

bool open_text_file( ifstream& infile)
{
//               
    assert (!infile.is_open());
/*                
                                                  
*/
    cout << "Please enter file name: " << endl;
    char filename[80];
    cin.getline(filename,80,'\n');
    infile.open(filename);
    if (infile)
    {
        cout << "the file has been opened succesfully" << endl;
    }
    else
    {
        cout << "the file couldn't be opened/doesn't exist" << endl;
    }
    return infile.is_open();
}

void words_in_array (ifstream& infile, int& counter)
{
    //              
    assert (infile.is_open());
    /*               
                                                    
    */
    counter = 0;
    while (infile)
    {
        infile >> words[counter];
        counter++;
    }
    counter--;
    cout << "the amount of words is: " << counter << endl;
    for (int i=0; i <= counter; i++)
    {
        cout << words[i] << endl;
    }
}

void count_words (int counter, ifstream& infile)
{
    //              
    assert (infile.is_open());
    /*              
                                                                                   
    */
    double counter2 = 0;
    string input;
    cout << "type in the word you want the frequency of:" << endl;
    cin >> input;
    for (int i=0; i <= counter; i++)
    {
        if (input == words[i])
        {
            counter2++;
        }
    }
    cout << "the frequency of the word: " << counter2 << endl;
    cout << "the total amount of words is: " << counter << endl;
    double percentage = (counter2 * 100) / counter;
    cout << "the occurrence of the word in percentage is: " << percentage << "%"<< endl;
}
void index_position(ifstream& infile, int counter)
{
    //              
    assert (infile.is_open());
    /*               
                                                                         
    */
    int counter3=0;
    string input;
    cout << "type in the word you want the index position from: " << endl;
    cin >> input;
    for (int i=0; i <= counter; i++)
    {
        if (input == words[i])
        {
            cout << "the index position is: " << i + 1 << endl;
            counter3++;
        }
    }
    cout << "the total amount of occurrences is: " << counter3 << endl;
}
void close_file (ifstream& infile)
{
    //              
    assert (infile.is_open());
    /*               
                                                  
    */
    infile.close();
    if (!infile.is_open())
    {
        cout << "the file was succesfully closed" << endl;
    }
    else
    {
        cout << "the file wasnt closed" << endl;
    }
}
void context_file()
{
    //                                                                                      
}
int main()
{
    int counter = 0;
    ifstream infile;
    char* word[MAX_CHARS];
    open_text_file(infile);
    words_in_array(infile, counter);
    cout << "what action do you want to perform: count=1, where=2." << endl;
    int choice;
    cin >> choice;
    if (choice==1)
    {
        count_words(counter, infile);
    }
    if (choice==2)
    {
        index_position(infile, counter);
    }
    close_file(infile);
    return 0;
}

