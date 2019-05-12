#include <iostream>
#include <fstream>
#include <cassert>
#include <string.h>
using namespace std;

const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000;
const int MAX_USER_INPUT = 10;
const int MAX_LINE = 2000;

enum Action {Enter_file, Content, Stop, Count, Where, Context};
//         

void parse_line ( char line[MAX_LINE], int line_lenght, char action_input[MAX_USER_INPUT][MAX_CHARS], int& n)
{
    //              
    assert(line_lenght>0);
    //               
    /*                                                                                         
    */
    int pos = 0;
    n = 0;
    while (pos < line_lenght)
    {
        int ind = 0;
        while (line[pos] != ' ' && pos < line_lenght)
        {
            action_input[n][ind++] = line[pos++];
        }
        action_input[n][ind] = '\0';
        n++;
        pos++;
    }

}
Action get_user_action (char action_input[MAX_USER_INPUT][MAX_CHARS], int& m, int& n)
{//               
    assert ( true ) ;
/*                 
                                                                                               
    */
    cout << endl << "Chose your next action  " << endl ;
    cout << "       enter file.txt - for opening a new file " << endl ;
    cout << "       content - for showing the content of the opened file" << endl ;
    cout << "       count word1,..,wordn - for counting appearances of the given sequence of words" << endl ;
    cout << "       where word1,..,wordn - for showing where the given sequence of words was found in the text" << endl ;
    cout << "       context m word1,..,wordn  - for showing the context where the given sequence of words was found" << endl ;
    cout << "       stop - for exiting the application" << endl ;

    string answer;
    cin >> answer;
    Action action;

    if (answer == "enter") //                                                                                    
    {
        action = Enter_file;
        cin.get(); //                                                 
        cin.getline ( action_input[0], MAX_CHARS, '\n') ; //                                           
    }
     else if (answer == "content")
            action = Content;
         else if (answer == "stop")
                action = Stop;
            else if (answer == "count")
                {
                    action = Count;
                    n = 0;
                    cin.get(); //                                                              
                    char line[MAX_LINE];
                    cin.getline ( line, MAX_LINE, '\n') ; //                                           
                    parse_line(line, strlen(line),action_input,n);
                }
                else if (answer == "where")
                    {
                        action = Where;
                        n = 0;
                        cin.get(); //                                                              
                        char line[MAX_LINE];
                        cin.getline ( line, MAX_LINE, '\n') ;
                        if (strlen(line) > 0)
                            parse_line(line, strlen(line),action_input,n);
                    }
                    else if (answer == "context")
                        {
                            n = 0;
                            m = 0;
                            cin >> m;
                            cin.get(); //                                                              
                            action = Context;
                            char line[MAX_LINE];
                            cin.getline ( line, MAX_LINE, '\n') ;
                            if (strlen(line) > 0)
                                parse_line(line, strlen(line),action_input,n);
                        }
                        else
                            cout << "invalid action, try again" << endl;

    return action;
}

bool open_text_file ( ifstream& infile, char filename[MAX_CHARS] )
{
     //                 
     assert(true);
     //                 
    /*                                                           */
    infile.open ( filename ) ;
    return infile.is_open () ;
}

int count_words (ifstream& infile, char words[MAX_WORDS][MAX_CHARS])
{
    //               
    assert ( infile.is_open () );
    //                
    /*                                                                                   
                                           */
    int pos = 0;
    while ( infile )
    {
        char word[MAX_CHARS];
        infile >> word;
        strcpy ( words [pos++], word ) ;
    }
    return pos-1;
}
void show_content (char words[MAX_WORDS][MAX_CHARS], int number_of_words)
{
  //             
    assert(number_of_words > 0);
    //                
    //                                                               
    for(int i=0; i< number_of_words; i++)
        cout << words[i] << endl;
}

//        
int search_word_sequence(char words[MAX_WORDS][MAX_CHARS], int number_of_words, char search_words[MAX_USER_INPUT][MAX_CHARS], int number_of_search_words, int number_of_context_words, Action action)
{
    //              
    assert(number_of_words > 0 && number_of_search_words > 0);
    //                
    /*
                                                                                                                                               
    */
    int occurrences = 0;
    for (int i = 0; i<number_of_words; i++)
    {
        if (0 == strcmp(words[i],search_words[0]))
        {
            bool match = true;
            for (int j=1; (j<number_of_search_words) && (i+j < number_of_words); j++)
            {
                if (0 != strcmp(words[i+j],search_words[j]))
                {
                    match = false;
                }
            }
            if (match)
            {
                occurrences++;
                if (action == Where)
                    cout << i+1 << " ";
                if (action == Context)
                {
                    for (int k=number_of_context_words;(k>=0);k--)
                        cout << words[i-k] << " ";
                    for (int k=1;(k<number_of_search_words+number_of_context_words) && (i+k < number_of_words);k++)
                        cout << words[i+k] << " ";
                    cout << endl;
                }
            }
        }
    }
    cout << " number of occurrences " << occurrences ;

    if (action == Count)
        cout << " out of " << number_of_words << " number of words in the text. Percentage " << 100.0*occurrences/number_of_words  << "%" << endl;
    else
        cout << endl;

}
int main ()
{
    ifstream file ;
    char words[MAX_WORDS][MAX_CHARS];
    int number_of_words = 0, number_of_searched_words = 0, number_of_context_words = 0;
    char action_input[MAX_USER_INPUT][MAX_CHARS];
    Action action = get_user_action(action_input,number_of_context_words,number_of_searched_words);

    while (Stop != action)
    {
        switch (action)
        {
        case Enter_file :
            if (open_text_file ( file, action_input [0] ))
            {
                number_of_words = count_words ( file, words) ;
                cout << "Open file succeeded. Number of words read: " << number_of_words << endl;
                file.close () ;
            }
            else
            {
                cout << "Could not open file " << endl;
            }
            break;
        case Content:
            if (number_of_words>0)
                show_content(words,number_of_words);
            else
                cout << " no file entered yet " << endl;

            break;
        case Count:
        case Where:
        case Context:
            if (number_of_words>0 && number_of_searched_words>0)
                search_word_sequence(words, number_of_words,action_input,number_of_searched_words, number_of_context_words, action);
            else
                cout << " invalid input request " << endl;
            break;
        }
        action = get_user_action(action_input,number_of_context_words,number_of_searched_words);
    }
}

