//                            
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdlib.h>

//                                                          

using namespace std;

bool enter_filename(ifstream& inputfile)
{
    //                
    assert(true);

    //                         

    string name;
    getline(cin, name);
    inputfile.open(name.c_str());
    return inputfile.is_open();
}

int read_content(ifstream& inputfile, string words[30000])
{
    int numOfWords = 0;
    while(inputfile)
    {
        inputfile >> words[numOfWords];
        numOfWords++;
    }
    numOfWords -= 1;
    return numOfWords;
}

void display_content(ifstream& inputfile)
{
    string content;
    while(inputfile >> content)
    {
        cout << content << " ";
    }
}

int main()
{
    //                        
    ifstream file;
    string words[30000];

    //             
    cout << "Multiple possible actions of this program:" << endl;
    cout << "1: Enter filename," << endl << "2: Content," << endl << "3: Stop" << endl << endl;
    cout << "Please enter the operation, you want to execute, followed by the filename!" << endl << endl;
    cout << "Possible filenames:" << endl << "- Alice's Adventures In Wonderland.txt" << endl << "- desktop.txt" << endl << "- Vogon poem.txt" << endl << endl;

    string command;
    cin >> command;
    cin.ignore();

    while(command != "stop")
    {
        if(command == "enter")
        {
            if(enter_filename(file))
            {
                int word_count = read_content(file, words);
                cout << word_count << endl;
            }
        }
        if(command == "content")
        {

            if(enter_filename(file))
            {
                display_content(file);
                //                               
            }
        }
        break;
    }

    return 0;
}

