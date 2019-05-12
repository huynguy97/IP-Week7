#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_WORDS = 30000;
const int MAX_CHAR = 60 ;

//                                                            

void count(string words [MAX_WORDS], string command[MAX_CHAR], int size)
{
    int no_of_occurances=0;
    bool occurance=true;

    for (int k = 0; k < MAX_WORDS; ++k)
    {
        if(words[k]==command[1])
        {
            cout<<"found the first"<<endl;
            for (int i = 1; i <= (size-2); ++i)
            {
                if(words[k+i]!=command[1+i])
                {
                    occurance=false;
                }
                else
                {
                    cout<<"it's true"<<endl;
                }
            }
            if (occurance)
            {
                no_of_occurances++;
            }
        }
    }
    cout<<no_of_occurances<<endl;
    }

int read_file(ifstream& myfile, string words [MAX_WORDS] )
{
    assert(myfile.is_open());

    int i=0;
    int counter=0;
    while(!myfile.eof())
    {
        myfile>>words[i];
        i++;
        counter++;
    }
    return counter;
}

void print_array(string words [MAX_WORDS], int& counter)
{
    for (int i=0; i<counter; i++)
    {
        cout << words[i];
        cout << " ";
    }
    cout<<endl;
}

int main()
{
    int counter=0;
    string filename;
    string words [MAX_WORDS];

        bool exit =true;

        cout<<"Hello, welcome to assignment 7's interface. I am C.H.I.P Computerised Human Interface Program."<<endl;

        while(exit)
        {
            cout<<"Please enter your command: "<<endl;

            string command[MAX_CHAR];
            char input[MAX_CHAR];
            int j=0;
            bool found=true;

            cin.getline(input, MAX_CHAR);

            cout<<endl;

            int i=0;

            string word="";

            while(found)
            {
                    if (input[i] != 32 && input[i]!='\0' )
                    {
                        word+=input[i];
                    }

                    else if(input[i]==32 || input[i]=='\0')
                    {
                        command[j]=word;
                        j++;
                        word="";
                        if (input[i]=='\0')
                        {
                            found=false;
                        }
                    }
                    i++;
                }

            if (command[0]=="enter")
            {
                for (int l = 1; l < j; ++l)
                {
                    filename+=command[l];
                    filename+=" ";
                }

                    ifstream input_file;
                    input_file.open(filename); //                                                                                          
                    if (!input_file.is_open())
                    {
                        cout<<"Something went wrong with opening the file, please try again"<<endl;
                    }
                    counter=read_file(input_file, words);
                    cout<<"the file has "<< counter<<" words \n"<<endl;
            }
            else if(command[0]=="stop")
            {
                exit=false;
                cout<<"Good bye :'("<<endl;
            }
            else if (command[0]== "content")
            {
                print_array(words, counter);
            }
            else if (command[0]== "count")
            {
                count(words, command, j);
            }
            else
            {
                cout<<"I'm sorry, i dont understand you."<<endl;
            }
        }
    }

