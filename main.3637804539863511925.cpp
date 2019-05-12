#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
//                      
//                                                                                                  
//                                                                                                     
using namespace std ;

//                                                     
const int MAX_CHARS = 50 ;
const int MAX_WORDS = 30000 ;
const int MAX_COMMAND = 80 ;

typedef char Command [MAX_COMMAND] ;
//                          
const Command Enter = {'e', 'n', 't', 'e', 'r', 0} ; //                                                                                
const Command Content = {'c', 'o', 'n', 't', 'e', 'n', 't', 0} ;
const Command Stop = {'s', 't', 'o', 'p', 0} ;
const Command Count = {'c', 'o', 'u', 'n', 't', 0} ;
const Command Where = {'w', 'h', 'e', 'r', 'e', 0} ;
const Command Context = {'c', 'o', 'n', 't', 'e', 'x', 't', 0} ;

void ask_command()
{
    assert(true) ;//             
    //                                                   
    cout << "Enter a command from the following list:" << endl ;
    cout << "1.enter [filename]" << endl ;
    cout << "2.content" << endl ;
    cout << "3.stop" << endl ;
    cout << "4.count [word1] [word2] ... [wordn]" << endl ;
    cout << "5.where [word1] [word2] ... [wordn]" << endl ;
    cout << "6.context [m] [word1] [word2] ... [wordn]" << endl ;
}

void split_command(Command command, Command operation, char variable [])
{
    assert(command && operation && variable) ;//             
    //                                                                                              
    int i = 0 ;
    while (i < MAX_COMMAND && command[i] != ' ' && command [i] != 0)
    {
        operation [i] = command [i] ;
        i++ ;
    }
    operation [i] = 0 ;
    if (command[i] == ' ')
        i++ ;
    const int done = i ; //                                                                                                               
    while (i < MAX_COMMAND)
    {
        variable[i - done] = command [i] ;
        i++ ;
    }
}

bool compare_command(Command operation, const Command command_type)
{
    assert(operation && command_type) ;//             
    //                                                                                      
    int i = 0 ;
    while (i < MAX_COMMAND && operation [i] != 0 && command_type [i] != 0)
    {
        if (operation [i] != command_type [i])
            return false ;
        i++ ;
    }
    return true ;
}

//                        
bool open_file(ifstream& inputfile, Command filename)
{
    assert(inputfile && filename) ; //             
    //                                                                                             
    inputfile.open(filename) ;
    return inputfile.is_open() ;
}

bool copy_word(ifstream& inputfile, char words [MAX_WORDS][MAX_CHARS], int& wordcount)
{
    assert(inputfile && words) ; //             
    //                                                                                         
    //                                                                          
    char word [MAX_CHARS] ;
    inputfile >> word ;
    if (inputfile)
    {
        for (int i = 0 ; i < MAX_CHARS ; i++)
            words [wordcount][i] = word[i] ;
        wordcount++ ;
        return true ;
    }
    else
        return false ;
}

void enter(Command variable, char words [MAX_WORDS][MAX_CHARS], int& wordcount)
{
    assert(variable && words) ; //             
    //                                                                                                                   
    //                                                                               
    ifstream inputfile ;
    if (open_file(inputfile, variable))
    {
        while (wordcount < MAX_WORDS && copy_word(inputfile, words, wordcount)) ;
        inputfile.close() ;
        cout << "\nThe following words have been read: \n " << endl ;
        for (int i = 0 ; i < wordcount ; i++)
        {
            int j = 0 ;
            while(words[i][j] != 0 && j < MAX_CHARS)
            {
                cout << words[i][j] ;
                j++ ;
            }
            cout << ' ' ;
        }
        cout << "\n\nThe number of words read is: " << wordcount << "\n" << endl ;
    }
    else
        cout << "File could not be opened. \n" << endl ;
}

//                          
void content(char words [MAX_WORDS][MAX_CHARS], int& wordcount)
{
    assert(words) ; //             
    //                                                                      
    //                                                 
    cout << "\n";
    if (wordcount > 0 && wordcount <= MAX_WORDS)
    {
        for (int i = 0 ; i < wordcount ; i++)
        {
            int j = 0 ;
            while(words[i][j] != 0 && j < MAX_CHARS)
            {
                cout << words[i][j] ;
                j++ ;
            }
            cout << ' ' ;
        }
        cout << "\n\n" ;
    }
    else
        cout << "No words stored.\n" << endl ;
}

//                        
void count_operation(char words [MAX_WORDS][MAX_CHARS], int& wordcount, Command variable)
{
    assert(words && variable) ; //             
    //                                                                                                       
    //                                                                                  
    //                                              
    int no_of_variables = 0 ;
    int i = 0 ;
    while (i < MAX_COMMAND && variable[i] != 0)
    {
        if (variable[i] = ' ')
            no_of_variables++ ;
        i++ ;
    }
    if (no_of_variables > 0)
        no_of_variables++ ; //                                                         
    if (no_of_variables > 0)
    {
        char sequence [no_of_variables][MAX_CHARS] ;
        for (int i = 0 ; i < no_of_variables ; i++)
            split_command(variable, sequence[i], variable) ;
        int occurances = 0 ;
        int j = 0 ;
        int k = 0 ;
        while (j < wordcount)
        {
            if (compare_command(sequence[k], words[j]))
                k++ ;
            if (k == no_of_variables)
            {
                occurances++ ;
                k = 0 ;
            }
            j++ ;
        }
        cout << "\nThe number of occurances of the word sequence is:" << occurances << endl ;
        cout << "The total number of words is:" << wordcount << endl ;
        double percentage = (static_cast<double>(occurances)*static_cast<double>(no_of_variables)*100)/static_cast<double>(wordcount) ;
        cout << "The percentage is:" << percentage << "%\n" << endl ;//                      
    }
    else
        cout << "\nNo words given to count.\n" << endl ;
}

//                       
bool choose_command(char words [MAX_WORDS][MAX_CHARS], int& wordcount)
{
    assert(true) ;//             
    //                                                                  
    //                                                                                                
    Command command ;
    cin.getline(command, MAX_COMMAND, '\n') ;
    Command operation ;
    Command variable ;
    split_command(command, operation, variable) ;
    if (compare_command(operation, Enter))
    {
        enter(variable, words, wordcount) ;
        return false ;
    }
    else if (compare_command(operation, Content))
    {
        content(words, wordcount) ;
        return false ;
    }
    else if (compare_command(operation, Stop))
    {
        return true ;
    }
    else if (compare_command(operation, Count))
    {
        count_operation(words, wordcount, variable) ;
        return false ;
    }
    else if (compare_command(operation, Where))
    {
        //       
        return false ;
    }
    else if (compare_command(operation, Context))
    {
        //         
        return false ;
    }
    else
    {
        cout << "Command not recognized, try again. \n" << endl ;
        return false ;
    }
}

int main()
{
    char words[MAX_WORDS][MAX_CHARS];
    int wordcount = 0 ;
    bool stop = false ;
    while(!stop) //                                         
    {
        ask_command() ;
        stop = choose_command(words, wordcount) ;
    }
    return 0;
}

