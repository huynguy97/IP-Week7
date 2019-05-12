#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;
const int MAX_CHARS = 30000;
/*                                   
                
                           

                                  
                               
                                      */

int enter_filename(ifstream& infile)
{
    /*                */
    assert (true)
    /*                
                                                                                                */
    string filename ;
    string action ;
    cin >> action ;
    getline (cin, filename) ;
    filename.erase(0,1) ;
    if (action == "enter")
    {
        infile.open(filename.c_str());
        if (!infile.is_open())
        {
            cout << "Unable to open the file you entered" ;
            action = "stop" ;
        }
        else
        {
            int command = 0 ;
            return command ;
        }
    }
    if (action == "content")
    {
        int command = 1 ;
        return command ;
    }
    if (action == "stop")
    {
        int command = 2 ;
        return command ;
    }

    else
    {
        cout << endl << "Unable to open file" ;
        return false ;
    }
}

int command_enter(ifstream& infile, string text[MAX_CHARS])
{
    /*                */
    assert (infile)
    /*                
                                                     */
    int i = 0;
    while (infile)
    {
        string word;
        infile >> text[i];
        cout << word;
        i++;
    }
    int lenght = i - 1;
    cout << "The amount of words in this file is " << lenght << endl;
}

int command_content(int lenght, string text[MAX_CHARS])
{
    /*                */

    /*                 */
    for (int i = 0; i < lenght-1; i++ )
    {
        cout << text[i];
    }
}

int main()
{
    while(true)
    {
    ifstream infile;
    string text[MAX_CHARS];
    int lenght;
    switch (enter_filename(infile))
        {
        case 0:
            command_enter(infile, text);
            break;
        case 1:
            command_content(lenght, text);
            break;
        case 2:
            return 0;
            break;
        }
    }
}

