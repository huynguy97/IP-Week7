//                                                                                  
//                                                                                                                        
//                                                

//                                                                                                                                          
//                                                                                                                                                                                         

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

const int MAX_COMMAND_LENGTH = 80 ;
const int MAX_FILENAME_LENGTH = 50 ;
const int MAX_WORD_LENGTH = 30 ;
const int MAX_POSITION = 30000;

void enter_command ( char command [MAX_COMMAND_LENGTH] )
{
    //              
    assert ( true );
    //               
    //                   
    cout << " Enter a command " << endl;
    cin.get( command, MAX_COMMAND_LENGTH ) ;
    cin.ignore (1000, '\n') ;
    cout << " You entered " << command << endl;
}

void command_content ( int wordcount, char command [MAX_COMMAND_LENGTH], char arrayfile [MAX_WORD_LENGTH][MAX_POSITION] )
{
    //              
    assert ( arrayfile [0][0] != ' ' );
    //               
    //
    int number = 0 ;
    int position = 0 ;
    while ( position < wordcount )
    {
        while ( number < MAX_WORD_LENGTH )
        {
            cout << arrayfile [number][position] ;
            number++ ;
            if ( arrayfile [number][position] == ' ')
            {
                cout << arrayfile [number][position] ;
                number = MAX_WORD_LENGTH ;
            }
        }
        number = 0 ;
        position++ ;
    }
    cout << "\n" ;
}

void open_file ( string filename, ifstream& infile )
{
    //                
    assert ( !infile.is_open() ) ;
    //                  
    //               
    infile.open ( filename.c_str() ) ;
        if ( infile.is_open() )
    cout << " Successfully opened " << filename << endl;
    else
        cout << " Could not open " << filename << endl;
}

void create_array ( ifstream& infile, char arrayfile [MAX_WORD_LENGTH][MAX_POSITION] )
{
    //              
    assert ( infile.is_open() ) ;
    //               
    //                                               
    char ch ;
    int position = 0 ;
    int letternumber = 0 ;
    while ( infile )
    {
        infile.get(ch) ;
        arrayfile [letternumber][position] = ch ;
        letternumber++ ;
        if ( ch == ' ' )
            {
                position++ ;
                letternumber = 0 ;
            }
    }
}

int count_words ( char arrayfile [MAX_WORD_LENGTH][MAX_POSITION] )
{
    //              
    assert ( true );
    //               
    //                        
    int wordcount = 1 ;
    int position = 0 ;
    int number = 0 ;
    while (position < 21000 )
    {
        while (number < MAX_WORD_LENGTH)
        {
            if ( arrayfile [number][position] == ' ' && arrayfile [number+1][position] != ' ' )
                {
                    wordcount++ ;
                    number = MAX_WORD_LENGTH ;
                }
                number++ ;
        }
        number = 0 ;
        position++ ;
    }
    return wordcount ;
}

void command_enter ( int x, char command [MAX_COMMAND_LENGTH], char arrayfile [MAX_WORD_LENGTH][MAX_POSITION], int& wordcount )
{
    //              
    assert ( true );
    //               
    //  
    ifstream infile ;
    string filename ;
    while ( x < MAX_COMMAND_LENGTH )
    {
        filename = filename + command[x] ;
        x++ ;
        if ( command[x] == '\0')
            x = MAX_COMMAND_LENGTH ;
    }
    open_file ( filename, infile ) ;
    create_array ( infile, arrayfile ) ;
    wordcount = count_words ( arrayfile ) ;
    cout << " The amount of words is " << wordcount << endl;
}

void command_stop ( char command [MAX_COMMAND_LENGTH], int& s )
{
    //              
    assert ( true );
    //               
    //
    cout << " command is stop " ;
    s = 1;
}

void command_where ( int x, char command [MAX_COMMAND_LENGTH] )
{
    //              
    assert ( true );
    //               
    //
    cout << " command is where " ;
    string wherewords ;
    while ( x < MAX_COMMAND_LENGTH )
    {
        wherewords = wherewords + command[x] ;
        x++ ;
        if ( command[x] == '\0')
            x = MAX_COMMAND_LENGTH ;
    }
}

void command_context ( int x, char command [MAX_COMMAND_LENGTH] )
{
    //              
    assert ( true );
    //               
    //
    cout << " command is context " ;
    string contextwords ;
    while ( x < MAX_COMMAND_LENGTH )
    {
        contextwords = contextwords + command[x] ;
        x++ ;
        if ( command[x] == '\0')
            x = MAX_COMMAND_LENGTH ;
    }
}

void command_count ( int x, char command [MAX_COMMAND_LENGTH] )
{
    //              
    assert ( true );
    //               
    //
    cout << " command is count " ;
    string countwords ;
    while ( x < MAX_COMMAND_LENGTH )
    {
        countwords = countwords + command[x] ;
        x++ ;
        if ( command[x] == '\0')
            x = MAX_COMMAND_LENGTH ;
    }
}

void command_default ()
{
    //              
    assert ( true );
    //               
    //  
    cout << " Could not recognise the command, try again. " ;
}

int string_to_number ( string type )
{
    //              
    assert ( true );
    //               
    //                         
    if ( type == "content" )
        return 1 ;
    if ( type == "context" )
        return 2 ;
    if ( type == "count" )
        return 3;
    if ( type == "enter" )
        return 4;
    if ( type == "stop" )
        return 5;
    if ( type == "where" )
        return 6;
}

void determine_command ( char command [MAX_COMMAND_LENGTH], int& s )
{
    //              
    assert ( true );
    //               
    //                      

    //                                                                                                        
    //                                                                                                                                
    //                                                                                                                                                          
    char arrayfile [MAX_WORD_LENGTH][MAX_POSITION] ;
    int x = 0 ;
    if ( command [0] == '\0' )
        s = 1 ;
    for ( int n = 0 ; n < MAX_COMMAND_LENGTH ; n++ )
    {
        if ( command [n] == ' ' )
            n = MAX_COMMAND_LENGTH ;
        if ( command [n] == '\0')
            n = MAX_COMMAND_LENGTH ;
        x++ ;
    }
    string type ;
    int number = 0 ;
    while ( number < x-1 )
    {
        type = type + command [number] ;
        number++ ;
    }
    int typenumber = string_to_number ( type ) ;
    int wordcount ;
    switch ( typenumber ) //                                                                                                                                                     
    //                                                                                 
    {
        case 1 : command_content ( wordcount, command, arrayfile ) ;   break ;
        case 2 : command_context ( x, command ) ;   break ;
        case 3 : command_count ( x, command )   ;   break ;
        case 4 : command_enter ( x, command, arrayfile, wordcount );   break ;
        case 5 : command_stop ( command, s ) ;   break ;
        case 6 : command_where ( x,command )   ;   break ;
        default : command_default () ; break ;
    }
}

int main()
{
    char command [MAX_COMMAND_LENGTH] ;
    int s = 0;
    while ( s == 0 )
    {
        enter_command ( command ) ;
        determine_command ( command, s ) ;
    }
    return 0;
}

