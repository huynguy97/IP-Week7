#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std ;

const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000 ;

string user_action []= {"Content", "Count", "Where", "Context", "Stop"};

//              
//         

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                
    assert(true);
    //                                                
    cout << "Enter a filename:";

    char c;
    int index = 0;
    while (cin.get(c))
    {
        if (index < MAX_FILENAME_LENGTH)
        {
            if (c == '\n')
            {
                filename [index] = '\0';
                break;
            }
            else
            {
                filename [index] = c;
            }
            index++;
        }
        else
        {
            if (c != '\n')
                return false;
            else
                filename [MAX_FILENAME_LENGTH] = '\0';
        }
    }
}

void open_file ()
{
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);

    ifstream input;
    input.open (filename);

    if (input.is_open())
    {
        cout << "File is opened successfully." << endl;
    }
    else
    {
        cout << "File is not opened successfully." << endl;
    }
}

int read_words (ifstream& input, string words [MAX_WORDS])
{
    int i = 0;
    string word;
    while (input >> word)
    {
        words [i] = word;
        i++;
    }
    return i;
}

bool enter_sequence (string sequence [MAX_FILENAME_LENGTH], int& sequence_length)
{
    //               
    assert (true);
    //                                                                                                                    

    cout << "Enter a sequence" << endl;

    char c;
    int index = 0;
    string a;

    while(cin.get(c))
    {
        if(index < MAX_FILENAME_LENGTH)
        {
            if(c == ' ')
            {
                sequence[sequence_length] = a;
                a = "";
                sequence_length++;
            }
            else if(c == '\n')
            {
                sequence[sequence_length] = a;
                sequence_length++;
                break;
            }
            else
            {
                a += c;
            }
            index++;
        }
    }

    return true;
}

int count_sequence(ifstream& infile, string word_list[MAX_WORDS], int number_of_words)
{
    string sequence[MAX_CHARS];
    int occurencesofsequence[30000];
    int sequence_length = 0;

    enter_sequence(sequence, sequence_length);

    //                                                          

    for(int i = 0; i < MAX_WORDS; i++)
    {
        //                   
    }

    int occurences = 0;

    for (int i = 0; i < number_of_words; i++)
    {
        int similarities = 0;

        for (int j = 0; j < sequence_length; j++)
        {
            int k = i + j;
            string fileword = word_list[k];
            //                                                 
            for (int k = 0; k < sequence_length; k++)
            {
                if (sequence[k] == fileword)
                {
                    similarities++;
                }
            }
        }
        if (similarities == sequence_length)
        {
            occurencesofsequence[occurences++] = i + 1;
        }
    }
    return occurences;

}

int main()
{
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);

    ifstream input;
    input.open (filename);

    if (input.is_open())
    {
        cout << "File is opened successfully." << endl << endl;
    }
    else
    {
        cout << "File is not opened successfully." << endl << endl;
        return 0;
    }

    string words[MAX_WORDS];
    int word_amount = read_words(input, words);

    while (input.is_open())
    {
        cout << "Enter your next action. Your choices are:" << endl;
        cout << "Content, show the contents of the file." << endl;
        cout << "Count, input a sequence of words and receive the frequency of the sequence, the total amount of words in the file and a percentage of your sequence." << endl;
        cout << "Where, take the input sequence and show all index positions of the sequence and display the frequency." << endl;
        cout << "Context, input a extra number m and display the sequence plus m words in front and behind the sequence." << endl;
        cout << "Stop, stop the program." << endl;

        string action;
        cin >> action;

        if (action == "Content")
        {
            cout << "The content of the file is:" << endl;
            for (int i = 0; i < word_amount; i++) {
                cout << words[i] << " ";
            }
            cout << endl << endl;
        }
        else if (action == "Count")
        {
            cout << "The given sequence occurs " << count_sequence(input, words, word_amount) << " times.";
            cout << "The amount of words in the text is " << word_amount << "." << endl;
            cout << "The percentage sequence of the text is " << (count_sequence(input, words, word_amount)/word_amount)*100 << "%.";
        }
        else if (action == "Where")
        {

        }
        else if (action == "Context")
        {

        }
        else if (action == "Stop")
        {
            input.close();
            if (!input.is_open())
            {
                cout << "Program terminated." << endl ;
                return 0;
            }
            else
            {
                cout << "File not closed successfully. File might be damaged. Please try again.";
            }
        }
    }
}
/*
                                     
                                        
                                           

                       
                                          
     
                             
                                       
         
                          
                                               
                                                               
                                           
             
                                                    
                 
                                   
                 
             
         
                                  
         
                                                         
         
     
                      */
