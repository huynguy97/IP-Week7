#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;

//                                              
//                                             

const int MAX_INPUT_LENGTH = 100 ;
const int MAX_COMMAND_LENGTH = 100;
const int MAX_WORDS = 50000;
const int MAX_CHARS = 50;

char words[MAX_WORDS][MAX_CHARS];

bool read_user_input(char input[MAX_INPUT_LENGTH], char command[MAX_COMMAND_LENGTH])
{
//              
assert (true);
//                                                                                                                      
    for (int i = 0; i < MAX_INPUT_LENGTH; i++)
    {
        if (input[i] == ' '|| input[i] == '\0')
        {
            command [i] = '\0';
            return true;
        }
        else
        {
            command [i] = input[i];
        }

    }
    return false;
}

bool get_filename(char input[MAX_INPUT_LENGTH], char filename[MAX_INPUT_LENGTH])
{
    //              
assert (true);
//                                                                                                                                             
                                                                         //                                                                         
    for (int i = 6; i < MAX_INPUT_LENGTH; i++)
    {
        if (input[i] == '\0')
        {
            filename [i-6] = '\0';
            return true;
        }
        else
        {
            filename [i-6] = input[i];
        }

    }
    return false;
}

void read_file(ifstream& infile, string file_words[MAX_WORDS], int& length)
{
    //              
    assert (infile.is_open());
    //                                                                                 

    int counter=0;
    string word;
    while(!infile.eof())
    {
        infile >> word;
        file_words[counter]=word;
        counter++;
    }
    length = counter;
    cout << "number of words:" << counter << endl;
}

void content(ifstream& infile, string file_words[MAX_WORDS], int& length)
{
    //              
    assert (infile.is_open());
    //                                                                     

    for(int i=0; i<=length; i++)
    {
        cout << file_words[i]<< endl;
    }

}

int    sequential_search( char data[MAX_WORDS][MAX_CHARS], int from, int to, char search_value[MAX_CHARS])
{
    //               
    assert( 0 <= from&& 0 <= to  ) ;
    //                 
    //                                     
    //                                                                        
    //                 
    //                                                                      
    //                                         
    //                                  

    if(  from>  to  )
    {
        return to  + 1 ;
    }
    int position=  from;
    while(position<=   to  && data [ position] != search_value)
    {
        position++ ;
    }
    return position;
}

bool read_word(ifstream& infile, char word[MAX_CHARS])
{
    //              
    assert(infile.is_open());
    //                                                                                    
    infile >> word;
    return infile;

}

bool tally_word(char word[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int&no)
{
    //              
    assert(no>=0 && no< MAX_WORDS);
    //                                                                                       
    //                                                              

    int pos = sequential_search(words, 0, no, word);
    if(pos<no)
    {
        freqs[pos]++;
        return true;
    }
    else if(pos < MAX_WORDS)
    {
        strcpy(words[pos],word);
        freqs[pos]=1;
        no++;
        return true;
    }
    return false;
}

int count(ifstream& infile)
{
    //               
    assert (infile.is_open());
    //                                            
    //                                         
    //                                                        
    //                                                                                   
    string file_words[30000];
    string word;
    int counter=0;
    int occ=0;
    string sequence;
    while(!infile.eof())
    {
        infile >> word;
        counter++;
    }

    cout<< "Give the word sequence you look for" << endl;
    getline(cin, sequence);
    string sequence_words[128];
    int sequence_index = 0;
    for (int i=0; i<sequence.length() ; i++)
    {
        if(sequence[i] != ' ')
        {
            sequence_words[sequence_index]+= (sequence[i]);
        }
        else
        {
            sequence_index ++;
        }
    }
    int seq_length = sequence_index+1;

    for(int i=0; i<=seq_length; i++)
    {
        cout << sequence_words[i]<< endl;
    }

//                                      

    char words[MAX_WORDS][MAX_CHARS];
    int freqs[MAX_WORDS];
    int no=0;
    char next[MAX_CHARS];

    while(read_word(infile, next) && tally_word(next, words, freqs, no) && no< MAX_WORDS)
    {
        return no;
    }
    int percentage= (occ/counter)*100;
    cout<< "percentage of occurences of the word sequence with respect to the total number of words" << percentage << "%"<< endl;
}

/*
                            
 
                    
                             
                                                            
                                                                   

                                       
                             
                
                  
              
                    
                             
                          
                                                         
                           
                               

                           
                                            
     
                              
         
                                                           
         
            
         
                              
         
     
                                      

 

                                     
 
                     
                                       
                                                                                                                                                                             
                                                                         
 

*/

void do_command(string cmd, char input[MAX_INPUT_LENGTH], ifstream& infile, string file_words[MAX_WORDS], int& length)
{
    //              
    assert (true);
    //                                                        

    if (cmd == "enter")
    {
        char filename[MAX_INPUT_LENGTH];
        get_filename(input, filename);
        infile.open(filename);
        if (infile.is_open())
        {
           read_file(infile, file_words, length);
        }
        else
            cout << filename <<" is not a legit name or could not be opened" << endl;

    }
    else if (cmd == "content")
    {
        content(infile, file_words, length);
    }
    else if (cmd == "count")
    {
        //                             
        count(infile); //                                           
    }
    else if (cmd == "where")
    {
        //                               
        //                       
    }
    else if (cmd == "context")
    {
        //                                             
        //                            
    }
    else
    {
        cout << "Unknown command" << endl;
    }
    //                              
    //                       
}

int main ()
{
    char input[MAX_INPUT_LENGTH], command[MAX_COMMAND_LENGTH];
    string file_words[MAX_WORDS];
    int length = 0;

    cin.getline(input, MAX_INPUT_LENGTH);
    ifstream input_file;
    read_user_input(input, command);
    string cmd = command;
    while (cmd != "stop")
    {
        do_command(cmd, input, input_file, file_words, length);
        cin.getline(input, MAX_INPUT_LENGTH);
        read_user_input(input, command);
        cmd = command;
    }
    return 0;
}

