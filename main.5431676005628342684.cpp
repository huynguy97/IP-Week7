//                         
//                        
//             

#include <iostream>
#include <cassert>  //                   
#include <fstream>  //                          
#include <string>

using namespace std;

const int filename_length = 90;
char infile;
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

bool open_text_file (ifstream& infile, string filename)
{
    //               
    assert (true);
    /*
                       
                                                                                                       
    */

    infile.open(filename.c_str());

    return infile.is_open ();

}

bool read_word (ifstream& infile, char word [MAX_CHARS])
{
    //              
    assert (infile.is_open ());
    /*                
                                               
    */
    infile >> word;

    return infile;
}

bool read_file (ifstream& infile, char word [MAX_CHARS])
{
    //              
    assert(infile.is_open());
    /*                
                                                                
    */

    int y = 0;
    string text[MAX_WORDS];

    while(read_word(infile, word))
    {
        text[y] = word;
        y++;
    }
    cout << endl << "You opened the file!" << endl;
    cout << "The file contains " << y << " words " <<  endl;
}

char order_appearance (ifstream& infile, char word [MAX_CHARS])
{
    //              
    assert (infile.is_open());
/*                
                                                                                            
*/
    infile >> word;
    char words [MAX_WORDS];

    int m = 0;

    words[m];
    cout << word << endl;
     while(read_word(infile, word))
        {
            cout << word << endl;
            m++;
        }

}

int main()
{
    cout << "Give a commando:" << endl;
    cout << "Command 'enter' + filename opens a file and displays the amount of words" << endl;
    cout << "Command 'content' + filename to display all words in their order of appearance." << endl;
    cout << "Command 'stop programme' will terminate the programme" << endl;
    char word[MAX_CHARS];
    ifstream file;

    string command, filename;
    cin >> command;
    cin >> filename;

    if (command == "enter")

        {
        open_text_file(file, filename);
        read_file(file, word);

        }

    if (command == "content")
            {
                open_text_file(file, filename);
                order_appearance(file, word);
            }
    if (command == "stop programme")
            {
              return 0;
            }
}

