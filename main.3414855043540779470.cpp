#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

//                               
//                          

using namespace std;

const int max_chars = 60000;

int OpenTekstFile(ifstream& infile)
{
    //              
    assert (true);
    //               
    //                                                                           
    string filename;
    string command;
    cin >> command;
    getline (cin, filename);
    filename.erase(0,1);
    //                      
    //                       
    //                         
    if(command == "enter")
    {
        infile.open(filename);
        if (!infile.is_open())
        {
            cout<< "Could not open file, terminating!!";
            command = "stop";
        }
        else
        {
            int input = 1;
            return input;
        }
    }
    if(command == "content")
    {
        int input = 2;
        return input;
    }
    if(command == "stop")
    {
        int input = 3;
        return input;
    }
}

void enter(ifstream& infile, string text [max_chars])
{
    //             
    assert(infile.is_open());
    //              
    //                                               
    //                         
    int i = 0;
    while (infile)
    {
        //            
        infile >> text[i];
        //                 
        i++;
        //             
    }

    cout << "There are this many words in your text file: " << i-1<< endl;
}

int content (string text[max_chars])
{
    //             
    assert(true);
    //               
    //                                                                 
    //                          
    cout <<"hello";
    for (int i=0; i < max_chars; i++)
    {
        cout << text [i];
        cout << ' ';
    }
}

int main()
{
    while(true)
    {
        ifstream infile;
        string text [max_chars];
        switch (OpenTekstFile(infile))
        {
        case 1:
            enter(infile, text); ;
            break;
        case 2:
            cout << "hello";
            break;
        case 3:
            return 0; ;
            break;
        }
    }
}

