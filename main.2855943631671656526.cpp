/*                                                                                                                                                                                                                  
                                                                                                                                                                                                      
                                                                                                                                                                                                                                             
                                                                                                                    
                    
                           
*/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <fstream>

using namespace std;

const int MAX_WORDS = 30000;
const int MAX_CHARS = 60;

bool open_text_file (ifstream& infile)
{
    //               
    assert (true);
    //                                                                      
    cout << "Please enter a filename:" << endl;
    string Filename;
    getline (cin, Filename);
    infile.open (Filename.c_str());
    return infile.is_open ();
}

bool read_word (ifstream& infile, char word [MAX_CHARS])
{
    //               
    assert (infile.is_open());
    //                                                                                          
    infile >> word ;
    return infile ;
}

void enter (ifstream& infile, string words [MAX_WORDS], int& no)
{
    no = 0;
    char word[MAX_CHARS];
    while(read_word(infile, word))
    {
        words[no] = word;
        no++;
    }
    return;
}

void show_words (string words [MAX_WORDS], int& no)
{
    //               
    assert (no >= 0 && no <= MAX_WORDS);
    //                                                     
    for (int i = 0; i < no; i++ )
    {
        cout << words [i] << '\t' ;
    }
    return;enum command {content, count, where, context};
}

int main()
{
    ifstream Filename ;
    string words [MAX_WORDS];
    string Giveword;
    int no;
    string command;
    if (open_text_file(Filename))
    {
        enter(Filename, words, no);
        cout << "The number of words is " << no << endl;
        cout << "Please enter a command" << endl;
        cin >> command ;

        if (command == "content")
        {
            show_words (words, no);
            return 0;
        }
        cout << "Please enter a word" << endl;
        cin >> Giveword ;
        if (command == "count")
        {
            int counter = 0;
            for (int i = 0; i < no; i++)
            {
                if (Giveword == words [i])
                    counter++;
            }
            double percentage = ((double)counter/(double)no*100);
            cout << Giveword << " occurs " << counter << " times in the text. The total number of words in the text is " << no << " and the percentage is " << percentage << "%" << endl;
        }
            if (command == "where")
            {
                int counter = 0;
                int pos = 1;
                cout << "The positions are:" << endl;
                for (int i = 0; i < no; i++)
                {
                    if (Giveword == words [i])
                    {
                        cout << i << endl;
                        counter++;
                    }
                }
                cout << "The number of words is " << counter << endl;
            }
            if (command == "context")
            {
                int m ;
                cout << "How many words do you want to have before and after the given word?" << endl;
                cin >> m ;
                int counter = 0;
                for (int i = 0; i < no; i++)
                {
                    if (Giveword == words [i])
                    {
                        cout << words [i-m] << " " << words [i] << " "<< words [i+m] << endl;
                        counter++;
                    }

                }
                cout << "The number of words is " << counter << endl;
            }

    }
    return 0;
}

