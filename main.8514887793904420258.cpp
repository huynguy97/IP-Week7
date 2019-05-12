#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_WORDS = 1500;
const int MAX_CHAR = 30000;
const int MAX_AMOUNT_OF_CHAR = 80;

bool open_text_file (ifstream& infile, char text [MAX_CHAR])
{
    //             
    assert (MAX_CHAR >= 0);
    //                                                        
    string filename;
    char a;
    cin.get(a);
    getline(cin, filename);
    infile.open(filename.c_str());
    for (int j = 0; infile; j++)
    {
        infile >> text [j];
    }

    filename.c_str();
    return infile.is_open();
}

bool show_text (char text [])
{
    //             
    assert (MAX_CHAR >= 0)
    //                                                          
    for (int c = 0; c < MAX_CHAR; c++)
        {
            cout << text [c] << " ";
        }
    cout << endl;

}

int sequential_search (int data [], int from, int to, int search_value)
{
    if (from > to)
        return to+1;
    int position = from;
    while (position <=to && data [position] != search_value)
        position++;
    return position;
}

bool read_word (ifstream& infile, char word [MAX_CHAR])
{
    infile >> word;
    return infile;
}

void strcpy (char destination [], char source [])
{
    for (int i = 0; i < MAX_CHAR; i++)
    {
        source [i] = destination [i];
    }
}

int main()
{
    //             
    assert (true)
    //                                                                                                                                 
    ifstream file;
    string command ;
    cin >> command;
    char text [MAX_CHAR];
    if (command == "enter")
    {
        open_text_file(file, text);
        if (file.is_open()){
            cout << "The file was successfully opened." << endl;
        }
        else
            cout << "Failed to open file.";
    }
    while (file.is_open())
    {
        cout << "Enter next command:" << endl;
        cin >> command;
        if (command == "content")
        {
            show_text(text);
        }
        if (command == "stop")
        {
            file.close();
            cout << "The program has stopped." << endl;
        }

    }

}

