//                                      
//                                      

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

const int MAX_WORDS = 30000;
const int MAX_CHARS = 60;
char word [MAX_CHARS];
string words [MAX_WORDS];

bool open_file (ifstream& infile)
{
    //                
        assert(!infile.is_open());
    /*                 
                                                       
    */

    cout << "Please enter your filename (do not forget .txt): " << endl;
    char filename [80];
    cin.getline (filename, 80, '\n');
    infile.open (filename);

    if (!infile.is_open())
        {
            cout << " ERROR, the file could not be opened." << endl;
        }
    else
        {
            cout << "The file has been opened." << endl;
        }

    return infile.is_open ();
}

void put_and_show_words_in_array (ifstream& infile, int& counter)
{
    //                
        assert( infile.is_open());
    /*                 
                                                                                         
    */

    counter = 0;
    while ( infile )
    {
      infile >> words[counter];
      counter++;
    }
    counter--;
    cout << "The amount of words is " << counter << "." << endl;

    for(int i = 0; i <= counter; i++)
    {
        cout << words[i] << endl;
    }
}

void count_words (ifstream& infile, int counter)
{
    //                
        assert(infile.is_open());
    /*                 
                                                                           
    */

    double counter2 = 0;
    string input;
    cout << "Type in the word, you want the frequency of:" << endl;
    cin >> input;
    for(int i = 0; i <= counter; i++)
    {
        if (input == words [i])
        {
            counter2++;
        }
    }
    cout << "The frequency of the word is: " << counter2 << endl;
    cout << "The total frequency of words is: " <<counter << endl;
    double percentage = (counter2 * 100) / counter;
    cout << "The percentage of the word is: " << percentage << "%" << endl;
}

void where_word (ifstream& infile, int counter)
{
    //               
        assert(infile.is_open());
    /*                
                                                                              
    */

    int counter3 = 0;
    string input;
    cout << "Type in the word, you want the place of:" << endl;
    cin >> input;

    for(int i = 0; i <= counter; i++)
    {
        if (input == words [i])
        {
            cout << "The index position is: " << i + 1 << endl;
            counter3++;
        }
    }
    cout << "The total amount of occurrences is: " << counter3 << endl;
}

void context_word (ifstream& infile, int counter)
{
 //                                                
}

void close_file (ifstream& infile)
{
    //                
        assert(infile.is_open());
    /*                 
                                                                                                      
    */

    infile.close();

    if(!infile.is_open())
    {
        cout << "The file was closed successfully." << endl;
    }
    else
    {
        cout << "ERROR: The file was not closed successfully." << endl;
    }

}

void choose_operation(ifstream& infile, int counter)
{
    //                 
        assert(infile.is_open());
    /*                 
                                                            
    */

    int input;
    cout << "Choose the operation you want to executed: For count press 1, for where press 2 and for context press 3." <<endl;
    cin >> input;

    switch (input)
    {
    case 1:
        count_words(infile, counter);
        break;
    case 2:
        where_word (infile, counter);
        break;
    case 3:
        cout << "We have not been able to finish this one." << endl;
        break;
    };
}

int main()
{
    ifstream infile;
    int counter = 0;
    open_file(infile);
    put_and_show_words_in_array(infile, counter);
    choose_operation(infile, counter);
    close_file (infile);
    return 0;
}

