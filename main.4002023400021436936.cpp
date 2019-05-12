//                                          
//                                     

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

const int MAX_WORDS = 300000;
fstream fs;
string words [MAX_WORDS];
string sequence [MAX_WORDS];
int elements = 0;

bool open_text_file (string filename)
{
    //               
    assert(true);
    //                
    //                                                                                                      
    fs.open(filename.c_str());
    if(fs.is_open())
    {
        cout << "File opened succesfully" << endl;
        return true;
    }
    else
    {
        cout << "File could not be opened" << endl;
        return false;
    }
}

int store_in_array(string s[] )
{
    //              
    assert (fs.is_open());
    //               
    //                                                                                                          
    elements = 0;
    while(fs >> s[elements])
    {
        elements++;
    }
    cout << elements << " words stored" << endl;
    return elements;
}

void print_words(string s[], int C)
{
    //              
    assert(fs.is_open());
    //              
    //                                                                         
    int counter = 0;
    while (counter < C)
    {
        cout << s[counter] << endl;
        counter++;
    }
}

int check_sequence(string s[], string sequence[])
{
    return -1;
}

int main()
{
    cout << "Please enter a command (enter, content, stop)" << endl;
    bool waiting_for_command = true;
    string command;
    while(waiting_for_command)
    {
        //                                                              
        getline(cin, command);
        if(command.substr (0,5) == "enter" && command.find(" ") == 5) //                            
        {
            string filename = command.substr(6); //                             
            cout << filename << endl;

            if(fs.is_open())
            {
                fs.close();
            }
            open_text_file(filename);
            store_in_array(words);
        }
        else if(command == "content") //                              
        {
            print_words(words, elements);
        }
        else if(command.substr (0,5) == "count" && command.find(" ") == 5)
        {
            string word_sequence = command.substr(6);
            int counter = 0;
            string word = "";

            for(int i=0;i<word_sequence.length(); i++)
            {
            char c = word_sequence.at(counter);
            if(c = '\n')
            {
                sequence[i] = word;
                word = "";
            }
            else
            {
                word += c;
            }
            counter++;
            }
        }
        else if(command == "stop") //                           
        {
            waiting_for_command = false;
        }
        else
        {
            cout << "Command not recognized, please try again" << endl;
        }
    }
    return 0;
}

