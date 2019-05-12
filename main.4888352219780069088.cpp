#include <iostream>
#include<cassert>
#include<fstream>
#include<string>

//                                
//                             

using namespace std;

const int MAX_WORDS = 30000;

string welcome()
{
    //            
    assert(true);
    //              
    //                                                                  
    string filename;
    getline (cin,filename);
    return filename;
}

bool open_file(ifstream& file, string filename )
{

    file.open (filename.c_str());
    if(file.is_open())
    {
        cout<<"The file is open"<< endl;
        return true;
    }
    else
    {
        cout<<"The file doesn't exist"<<endl;
        return false;
    }
}

int read_content(string words[MAX_WORDS], ifstream& file)
{
    int i;
    for ( i = 0; i< MAX_WORDS && file; i++)
    {
        file>>words[i];
    }
    cout<<"The number of words is  " << i <<endl;
    return i;

}

void display_content(string words[MAX_WORDS], int amount)
{
    for (int i = 0; i< amount; i++)
    {
        cout<<words[i]<<endl;
    }
}

bool user_interface(string words[MAX_WORDS], int& amount_of_words)

{
    string command;
    cin >> command; //                                 
    cin.ignore(1);
    ifstream file;
    if (command == "enter")
    {

        if(open_file(file, welcome()))
        {
            amount_of_words = read_content(words, file);
        }

    }
    else if (command == "content")
    {
        display_content(words,amount_of_words);

    }
    else if (command == "stop")
    {
        return false;
    }
   /*                            
     

     */
    return true;
}

/*                                                                        
 
                     
                                     

                   
                      
                         
                                                              
                    
                     
 */

int main()
{
    int amount_of_words = 0;
    string words[MAX_WORDS];
    ifstream file;
    cout<<"Please enter the filename including the command"<<endl;
    while(file)
    {
        user_interface(words, amount_of_words);
    }
    return 0;
}

