#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
//                              
using namespace std;
const int MAX_FILENAME = 80;
const int MAX_WORDS = 32767;
const int MAX_CHARS = 35;
const int MAX_COMMAND = 80;

const char ENTER[MAX_COMMAND] = {'e','n','t','e','r','\0'};
const char CONTENT[MAX_COMMAND]= {'c','o','n','t','e','n','t','\0'};
const char STOP[MAX_COMMAND] = {'s','t','o','p','\0'};
const char COUNT[MAX_COMMAND] = {'c','o','u','n','t','\0'};
const char WHERE[MAX_COMMAND]= {'w','h','e','r','e','\0'};
const char CONTEXT[MAX_COMMAND] = {'c','o','n','t','e','x','t','\0'};
//                                               
void commands()
{
    assert(true);
    //               
    //                                                  
    cout << "These are the possible commands:" << endl;
    cout << "enter (filename)" << endl;
    cout << "content" << endl;
    cout << "stop" << endl;
    cout << "count [word1] [word2] ... [word n]" << endl;
    cout << "where [word1] [word2] ... [word n]" << endl;
    cout << "context [m] [word1] [word2] ... [word n]" << endl;
}
//                                                                                                                                                                               
bool process(char command[MAX_COMMAND], char act_command[MAX_COMMAND])
{
    assert(true);
    //               
    //                                                           
    //                                                       
    int i =0;
    while(i < MAX_COMMAND && command[i] != ' ' && command[i] != 0)
    {
        act_command[i] = command[i];
        i++;
    }
    act_command[i] = '\0';

    if(command[i] == ' ')
        i++;
    else
        return false;

    const int k = i;

    while(i < MAX_COMMAND)
    {
        command[i - k] = command[i];
        i++;
    }
}
//                                           
int word_counter (char command[MAX_COMMAND])
{
    assert(true);
    //              
    //                                                                      
    int i = 0;
    int counter = 0;
    while (i < MAX_COMMAND && command[i] != 0){
        if (command[i] == ' '){
            counter++;
        }
        i++;
    }

    return counter + 1;
}
//                                                             
int sequential_search ( char data[MAX_WORDS][MAX_CHARS], int from, int to, char search_value[MAX_CHARS] ){
    assert ( 0 <= from && 0 <= to ) ;
    //                 
    //                                  
    //                                                              
    //                     
    //                                                                
    //                                        
    //                                   
    if ( from > to )
        return to + 1 ;
    int  position = from ;
    while (position <= to && strcmp(data[position],search_value) != 0)
        position++ ;
    return position ;
}
//                  
bool open_text_file(ifstream& infile, char filename[MAX_COMMAND])
{
    assert(!infile.is_open());
    //               
    //                                                          
    infile.open(filename);
    return infile.is_open();
}
//                                            
int store_words(ifstream& infile, char words[MAX_WORDS][MAX_CHARS], char word[MAX_CHARS])
{
    assert(infile.is_open());
    //               
    //                                                                                                         
    int i = 0;
    while(infile)
    {
        infile >> word;
        if(word[strlen(word) - 1] == '.')//                                       
        {
            word[strlen(word) - 1] = 0;
        }
        strcpy(words[i],word);
        i++;
    }
    return i;
}
//                                                                     
void display_words(char words[MAX_WORDS][MAX_CHARS], int length)
{
    assert(length >= 0);
    //               
    //                                                                           
    cout << endl;
    if(length != 0)
    {
        for(int i = 0; i < length ; i++)
            {
                cout << words [i]<< " ";
            }
        cout << endl;
    }
    else //                                            
    {
        cout << "You did not read in a file yet" << endl;
    }
}
//                                                 
void c_count(char command[MAX_COMMAND], char words[MAX_WORDS][MAX_CHARS], int no )
{
    assert(no >= 0);
    //                
    //                                                                               
    cout << endl;
    int counter = 0;
    int sen = word_counter(command);
    char sequence[sen][MAX_CHARS];

    for(int i =0; i < sen; i++)
    {
        process(command,sequence[i]);
    }
    int posseq1 = sequential_search(words,0,no,sequence[0]);
    bool checker;
    while(posseq1 <= (no-sen))
    {
        checker = true;
        for(int k = 1;k < sen;k++)
        {
            if(strcmp(words[posseq1 + k],sequence[k]) != 0)
            {
                checker = false;
            }
        }
        if(checker)
          counter++;
        posseq1 = sequential_search(words,posseq1 + 1,no,sequence[0]);
    }
    cout << "The sequence was found " << counter << " times." << endl;
    cout << "With the total number of words within the text being : " << no << endl;
    double percentage = (static_cast<double>(counter) * static_cast<double>(sen) * 100)/static_cast<double>(no);
    cout << "The percentage of this sequence against the number of words is : " << percentage << " %" <<  endl;
}
//                                                 
void c_where(char command[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int no)
{
    assert(no > 0);
    //                
    //                                                                               
    cout << endl;
    int sen = word_counter(command);
    char sequence[sen][MAX_CHARS];

    for(int i =0; i < sen; i++)
    {
        process(command,sequence[i]);
    }
    int posseq1 = sequential_search(words,0,no,sequence[0]);
    bool checker;
    int counter = 0;
    while(posseq1 <= (no-sen))
    {
        checker = true;
        for(int k = 1;k < sen;k++)
        {
            if(strcmp(words[posseq1 + k],sequence[k]) != 0)
            {
                checker = false;
            }
        }
        if(checker)
        {
            counter++;
            if (counter == 1)
            {
                cout << "The found indexes are:" << endl;
            }
            for(int k = 1; k <= sen;k++)
            {
                cout << posseq1 + k << " ";
            }
            cout << endl;
        }
        posseq1 = sequential_search(words,posseq1 + 1,no,sequence[0]);
    }
    cout << "The amount of times the sequence is found: " << counter << endl;
}
//                                                   
void c_context(char command[MAX_COMMAND], char words[MAX_WORDS][MAX_CHARS], int no)
{
    assert(no > 0);
    //                
    //                                                                               
    cout << endl;
    int sen = word_counter(command);
    char sequence[sen][MAX_CHARS];
    for(int i =0; i < sen; i++)
    {
        process(command,sequence[i]);
    }
    int posseq1 = sequential_search(words,0,no,sequence[1]);
    int m = atoi(sequence[0]);
    bool checker;
    int counter = 0;
    while(posseq1 <= (no-(sen-1)))
    {
        checker = true;
        for(int k = 1;k < (sen - 1) ;k++)
        {
            if(strcmp(words[posseq1 + k],sequence[k+1]) != 0)
            {
                checker = false;
            }
        }
        if(checker)
        {
            counter++;
            cout << "The context of the sequence is : " << endl;
            for(int k = -m ;k < ((sen-1) + m); k++)
            {
                cout << words[posseq1 + k] << " ";
            }
            cout << endl;
        }
        posseq1 = sequential_search(words,posseq1 + 1,no,sequence[1]);
    }
    cout << "The amount of times the sequence is found: " << counter << endl;
}
//                                                 
void c_enter(char filename[MAX_COMMAND], char words[MAX_WORDS][MAX_CHARS], char word[MAX_CHARS],int& no)
{
    assert(no >= 0);
    //                
    //                                              
    ifstream infile;
    if(open_text_file(infile,filename))
       {
           no = store_words(infile,words,word) - 1;
           infile.close();
           if(!infile.is_open())
           {
              cout << "The amount of stored words is " << no << endl;
              return;
           }
           else
           {
               cout << "Be careful the file may not have closed correctly" << endl;
               cout << "The amount of stored words is " << no << endl;
               return;
           }
       }
    cout << "For some reason the file did not open, please use another filename when using the command enter" << endl;
}
//                                                   
bool command_get(char words[MAX_WORDS][MAX_CHARS], char word[MAX_CHARS], int& no)
{
    assert(no >= 0);
    //               
    //                                                                                         
    char user_command[MAX_COMMAND];
    cin.getline(user_command,MAX_COMMAND);

    char actual_command[MAX_COMMAND];
    process(user_command,actual_command);

    if(strcmp(actual_command,ENTER) == 0)
    {
        c_enter(user_command,words,word,no);
    }
    else if(strcmp(actual_command,CONTENT) == 0)
    {
        display_words(words,no);
    }
    else if(strcmp(actual_command,STOP) == 0)
    {
        cout << "You terminated this program" << endl;
        return false;
    }
    else if(strcmp(actual_command,COUNT) == 0)
    {
        c_count(user_command,words,no);
    }
    else if(strcmp(actual_command,WHERE) == 0)
    {
        c_where(user_command,words,no);
    }
    else if(strcmp(actual_command,CONTEXT) == 0)
    {
        c_context(user_command,words,no);
    }
    else
    {
        cout << "This command was not recognised, please enter a different one" << endl;
    }
    return true;
}
//             
int main()
{
    char words[MAX_WORDS][MAX_CHARS];
    char word[MAX_CHARS];
    int no = 0;

    commands();
    while(command_get(words, word ,no))
    {
        commands();
    }
    return 0;
}

