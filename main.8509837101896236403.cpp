#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>

using namespace std;

enum {later};
const int MAX_WORD_COUNT = 32767;

void get_word (string &line, string &word, string &rest_of_line)
{
//                
    assert (true);
//                 
//                                                                                                     

    word = "", rest_of_line = "";

    bool word_done = false;
    for(int i = 0; i < line.length(); i++)
    {
        char c = line[i];
        if(!word_done  && (c == ' ' || c == '\n'))
        {
            word_done = true;
            continue; //                                 
        }

        if(word_done)
            rest_of_line += c;
        else
            word += c;
    }
}

bool read_word (ifstream & input_file, string &word)
{
//                
    assert (input_file.is_open());
//                 
//                                                                          

    input_file >> word;
    return input_file;
}

bool close_file (ifstream & input_file)
{
//                
    assert (input_file.is_open());
//                 
//                                                                     

    input_file.clear();
    input_file.close();
    if(input_file)
    {
        cout << "File closed successfully.\n";
        return true;
    }
    cout << "File closed unsuccessfully.\n\n";
    return false;
}

void split_words (string words, string word_array[MAX_WORD_COUNT], int &m)
{
//                
    assert (true);
//                 
//                                                        

    int beginning = 0;
    m = 0;
    for (int i = 0; i < words.length(); i++)
    {
        if(isspace(words[i]) || i == words.length() - 1)
        {
            if( i == words.length() - 1) i++;
            word_array[m++] = words.substr(beginning, i - beginning);
            beginning = i + 1;
        }
    }
}

int count_sequence_instances (string read_text[MAX_WORD_COUNT], int n, string word_array[MAX_WORD_COUNT], int m, int indexes[MAX_WORD_COUNT])
{
//                
    assert (true);
//                 
//                                                                   

    int counted_instances = 0;
    bool found;
    for (int i = 0; i < n; i++)
    {
        found = true;
        for (int ii = 0; ii < m; ii++)
        {
            if(read_text[i + ii] != word_array[ii])
            {
                found = false;
                break;
            }
        }
        if(found)
            indexes[counted_instances++] = i + 1;
    }
    return counted_instances;
}

bool enter (ifstream & input_file, string filename, string read_text[MAX_WORD_COUNT], int &n)
{
//                
    assert (true);
//                 
//                                                    

    n = 0;
    if(input_file.is_open())
        close_file(input_file);

    input_file.open(filename.c_str());
    if(!input_file)
    {
        cout << "File \"" << filename << "\" opening was unsuccessful.\n\n";
        return false;
    }

    bool read_successful;
    do
    {
        string temp;
        read_successful = read_word(input_file, temp);
        if(read_successful)
        {
            if (temp != "")
                read_text[n++] = temp;
        }
    } while(read_successful && n < MAX_WORD_COUNT);
    cout << "Number of words read from file \"" << filename << "\": " << n << endl << endl;
    return true;
}

void content (string read_text[MAX_WORD_COUNT], int n)
{
//                
    assert (true);
//                 
//                                                      

    cout << "All words and their positions in the text:\n";
    for(int i = 0; i < n; i++)
        cout << " * " << read_text[i] << endl;
    cout << endl;
}

void count_words (string read_text[MAX_WORD_COUNT], int n, string words)
{
//                
    assert (true);
//                 
//                                                                                      

    string word_array[MAX_WORD_COUNT];
    int m, index_array[MAX_WORD_COUNT];
    split_words(words, word_array, m);

    int counted_instances = count_sequence_instances(read_text, n, word_array, m, index_array);

    cout << "\"" << words << "\" word sequence was counted: " << counted_instances << " times.\n";
    cout << "Total number of words in text: " << n << endl;
    cout << "Frequency of word sequence in text: " << (float)(counted_instances * m ) * 100 / n << "%\n\n";
}

void where (string read_text[MAX_WORD_COUNT], int n, string words)
{
//                
    assert (true);
//                 
//                                                                                         

    string word_array[MAX_WORD_COUNT];
    int m, index_array[MAX_WORD_COUNT];
    split_words(words, word_array, m);

    int counted_instances = count_sequence_instances(read_text, n, word_array, m, index_array);

    cout << "\"" << words << "\" word sequence was found in these positions:";
    for (int i = 0; i < counted_instances; i++)
    {
        cout << (i == 0 ? " " : ", ") << index_array[i];
    }
    cout << ".\nWord sequence was found: " << counted_instances << " times.\n\n";
}

void context (string read_text[MAX_WORD_COUNT], int n, string words)
{
//                
    assert (true);
//                 
//                                                                            

    string word_array[MAX_WORD_COUNT], number, rest_of_the_words;
    int m, index_array[MAX_WORD_COUNT], words_surround;

    get_word(words, number, rest_of_the_words);

    split_words(rest_of_the_words, word_array, m);

    int counted_instances = count_sequence_instances(read_text, n, word_array, m, index_array);

    words_surround = atoi(number.c_str());

    if(words_surround <= 0)
    {
        cout << "m has to be an integer positive number. Command terminated.\n\n";
        return;
    }

    cout << "\"" << rest_of_the_words << "\" word sequence was found in these contexts:\n";
    for (int i = 0; i < counted_instances; i++)
    {
        int l_bound = index_array[i] - words_surround - 1;
        int u_bound = index_array[i] + m + words_surround - 1;
        cout << " * ";
        for (int ii = (l_bound < 0) ? 0 : l_bound; ii < u_bound; ii++)
        {
            cout << read_text[ii] << " ";
        }
        cout << endl;
    }
    cout << "Word sequence was found: " << counted_instances << " times.\n\n";
}

int get_command_id (string command)
{
//                
    assert (true);
//                 
//                               

    if(command == "enter") return 0;
    if(command == "content") return 1;
    if(command == "stop") return 2;
    if(command == "count") return 3;
    if(command == "where") return 4;
    if(command == "context") return 5;
    return -1;
}

void display_all_commands ()
{
//                
    assert (true);
//                 
//                                             

    cout << "----------------------------------------------\n";
    cout << "All commands:\n";
    cout << "----------------------------------------------\n";
    cout << "enter <filename>\n";
    cout << "content\n";
    cout << "stop\n";
    cout << "count [<word_1>..<word_n>]\n";
    cout << "where [<word_1>..<word_n>]\n";
    cout << "context <m> [<word_1>..<word_n>]\n";
    cout << "----------------------------------------------\n\n";
}

int main()
{
    ifstream input_file;
    string read_text [MAX_WORD_COUNT];
    bool stop = false;
    display_all_commands();
    cout << "Enter Command:" << endl;

    while(!stop){
        string line, command, arguments;

        bool correct_command;

        do
        {
            correct_command = true;

            getline(cin, line);

            get_word(line, command, arguments);

            int command_id = get_command_id(command), number_of_words;

            switch(command_id)
            {
            case 0: //      
                enter (input_file, arguments, read_text, number_of_words);
                break;
            case 1: //        
                if(!input_file.is_open())
                {
                    cout << "No file is open. Use command \"enter\".\n\n";
                    break;
                }
                if (arguments != "")
                {
                    cout << "Command \"content\" does not require arguments. \"" << arguments << "\" not understood.\n\n";
                    break;
                }
                content(read_text, number_of_words);
                break;
            case 2: //     
                if(input_file.is_open())
                    close_file(input_file);
                stop = true;
                break;
            case 3: //      
                if(!input_file.is_open())
                {
                    cout << "No file is open. Use command \"enter\".\n\n";
                    break;
                }
                if (arguments == "")
                {
                    cout << "Command \"count\" requires arguments/words.\n\n";
                    break;
                }
                count_words(read_text, number_of_words, arguments);

                break;
            case 4: //      
                if(!input_file.is_open())
                {
                    cout << "No file is open. Use command \"enter\".\n\n";
                    break;
                }
                if (arguments == "")
                {
                    cout << "Command \"where\" requires arguments/words.\n\n";
                    break;
                }
                where(read_text, number_of_words, arguments);

                break;
            case 5: //        
                if(!input_file.is_open())
                {
                    cout << "No file is open. Use command \"enter\".\n\n";
                    break;
                }
                if (arguments == "")
                {
                    cout << "Command \"context\" requires arguments/words.\n\n";
                    break;
                }
                context(read_text, number_of_words, arguments);

                break;
            default:
                cout << "Command \"" << command << "\" is incorrect. Please enter command again.\n\n";
                correct_command = false;
            }
        } while(!correct_command);
    }
    return 0;
}

