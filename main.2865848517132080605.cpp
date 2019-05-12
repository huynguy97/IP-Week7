//                      
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>

using namespace std;

const int Max_filelength   = 51;                    //                                                             
const int Max_commandlength= 20;                    //                                                            
const int MAX_CHARS        = 20;                    //                                                 
const int MAX_WORDS        = 20000;                 //                                                  
const char entercmd[]      = "enter";               //                                                       
const char contentcmd[]    = "content";             //                                                       
const char stopcmd[]       = "stop";                //                                                       
const char countingcmd[]   = "count";               //                                                       
const char wherecmd[]      = "where";               //                                                       
const char contextcmd[]    = "context";             //                                                       

int Enter_filename(ifstream& Inputfile, string array_of_words[])
{
    //              
    assert (true);

    //               
    /*                                                         
                                                          
                                               */

    //               
    int counter = 0;
    char c;
    cin.get(c);
    string filename;
    getline(cin, filename);
    Inputfile.open(filename);
    if (Inputfile.is_open())
    {
        while(Inputfile)
        {
            Inputfile >> array_of_words[counter];
            counter++;
        }
        return counter -1;
    }

    else
    {
        return -1;
    }

}

char content(string array_of_words[], int ammount_of_words)
{
//               
    assert(true);
//                
    /*                                                */

//               
    for (int i= 0; i<ammount_of_words; i++)
    {
        cout << array_of_words[i] << endl;
    }

}

int stop()
{

//               
    assert(true);

//                
//                                               

//              

    cout << "Good bye see you next time!" << endl;
    return 0;
}

int counting(const char array_of_words[], char row_of_words)
{
    /*       
               
                                  
                                        
                                                                               */

}

int where()
{

}

string context()
{

}

int main()
{
    while (true)
    {
        char command[Max_commandlength];
        string filename;
        cout << "**********Concordancer**********" << endl;
        cout << "I'm ready my lord! What can i do for you?" << endl;
        cin >> command;
        ifstream input;
        string arrayname [20000];
        int ammount_of_words = 0;

        if(strcmp(command,entercmd)== 0)
        {
            ammount_of_words =Enter_filename(input,arrayname);
            if (ammount_of_words > 0)
            {
                cout <<ammount_of_words<<endl;
            }
            else
            {
                cout << "ERROR something went wrong! Try again" << endl;
            }

        }
        if(strcmp(command,contentcmd)== 0)
        {
            if(content(arrayname,Enter_filename(input, arrayname))==-1)
            {
                cout << "ERROR something went wrong! Try again" << endl;
            }

        }
        if(strcmp(command,stopcmd)== 0)
        {
            return stop();
        }
        if(strcmp(command,countingcmd)== 0)
        {
            //                                             
        }
        if(strcmp(command,wherecmd)== 0)
        {
            //            
        }
        if(strcmp(command,contextcmd)== 0)
        {
            //         
        }
    }
}

