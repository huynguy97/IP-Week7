#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

//                                       
//                                 

using namespace std;

const int MAX_COMMAND_LENGTH = 80;
const int MAX_WORD_COUNT = 50000;
const int MAX_COMMAND_ARGUMENTS = 20;

int read_file_to_array(ifstream& inputfile, string words[MAX_WORD_COUNT])
{
    //               
    assert(inputfile.is_open());
    assert(words);
    //                
    //                                                                                                   
    string current_word = "";
    int i = 0;

    while (inputfile >> current_word)
    {
        words[i] = current_word;
        i++;
    }
    return i;
}

int get_command_details(char command[MAX_COMMAND_LENGTH], string command_details[MAX_COMMAND_ARGUMENTS])
{
    //               
    assert(command);
    assert(command_details);
    //                
    //                                                                                                                                                   
    int i = 0;
    int j = 0;
    string command_details_chars = "";

    while (!(command[i] == '\0'))
    {
        if (command[i] == ' ')
        {
            command_details[j] = command_details_chars;
            j++;
            command_details_chars = "";
        }
        else
        {
            command_details_chars += command[i];
        }
        i++;
    }
    command_details[j] = command_details_chars;
    return j;
}

int count_words(string command_details[MAX_COMMAND_ARGUMENTS], string words[MAX_WORD_COUNT], int word_sequence_occurrences[MAX_WORD_COUNT], int word_count, int command_count)
{
    //               
    assert(command_details);
    assert(words);
    assert(word_sequence_occurrences);
    assert(word_count >= 0);
    assert(command_count > 0);
    //                
    //                                                                                                                                                                                   
    bool flag_first_time_check;

    int number_of_occurrences = 0;

    for (int i = 0; i <= word_count - command_count; i++)
    {
        flag_first_time_check = true;
        for (int j = 1; j <= command_count; j++)
        {
            if (words[i] == command_details[1])
            {
                if (flag_first_time_check)
                {
                    word_sequence_occurrences[number_of_occurrences] = i;
                    number_of_occurrences++;
                    flag_first_time_check = false;
                }
            }
            else //                                           
            {
                j = command_count + 1;
            }
            if (!(words[i+j - 1] == command_details[j]))
            {
                if (words[i] == command_details[1])
                {
                    number_of_occurrences--;
                }
                else //                                           
                {
                    j = command_count + 1;
                }
            }
        }
    }
    return number_of_occurrences;
}

int main()
{
    string words[MAX_WORD_COUNT];
    int word_count;
    bool flag_array_made = false;
    int word_sequence_occurrences[MAX_WORD_COUNT];

    while (true)
    {
        cout << "please enter your desired command (enter, content, count, where, context, stop):\n";
        char command[MAX_COMMAND_LENGTH];
        cin.getline(command, sizeof(command));

        string command_details[MAX_COMMAND_ARGUMENTS];
        int command_count;
        command_count = get_command_details(command, command_details);

        //     
        if (command_details[0] == "stop")
        {
            return 0;
        }

        //      
        else if (command_details[0] == "enter")
        {
            string infile = command_details[1];
            for (int i = 2; i <= command_count; i++)
            {
                infile += ' ' + command_details[i];
            }

            ifstream inputfile;
            inputfile.open(infile.c_str(), std::fstream::in);
            word_count = read_file_to_array(inputfile, words);
            flag_array_made = true;
            cout << "successfully loaded file and created array of words\n";
        }

        //        
        else if (command_details[0] == "content" && flag_array_made)
        {
            cout << "displaying content of the file:\n";
            for (int i = 0; i < word_count; i++)
            {
                cout << words[i] << '\n';
            }
        }

        //      
        else if (command_details[0] == "count" && flag_array_made)
        {
            int number_of_occurrences = count_words(command_details, words, word_sequence_occurrences, word_count, command_count);
            double percentage = (double)number_of_occurrences / (double)word_count * (double)100;
            cout << "number of occurrences: " << number_of_occurrences << ", total word count: " << word_count << ", percentage: " << percentage << "%\n";
        }

        //      
        else if (command_details[0] == "where" && flag_array_made)
        {
            cout << "displaying the index positions where the entered word(s) occur:\n";
            int number_of_occurrences = count_words(command_details, words, word_sequence_occurrences, word_count, command_count);
            for (int i = 0; i < number_of_occurrences; i++)
            {
                cout << word_sequence_occurrences[i] + 1 << ", ";
            }
            cout << "\nnumber of occurrences: " << number_of_occurrences << '\n';
        }

        //        
        else if (command_details[0] == "context" && flag_array_made)
        {
            cout << "displaying context of the entered word(s):\n";
            stringstream m_string(command_details[1]);
            int m;
            m_string >> m;

            for (int i = 1; i < command_count; i++)
            {
                command_details[i] = command_details[i+1];
            }
            command_count--;

            int number_of_occurrences = count_words(command_details, words, word_sequence_occurrences, word_count, command_count);

            for (int i = 0; i < number_of_occurrences; i++)
            {
                for (int j = -m; j <= m + command_count - 1; j++)
                {
                    if (word_sequence_occurrences[i]+j >= 0)
                    {
                        cout << words[word_sequence_occurrences[i]+j] << ' ';
                    }
                }
                cout << '\n';
            }
            cout << "number of occurrences: " << number_of_occurrences << '\n';
        }

        //             
        else
        {
            cout << "incorrect command used or no file entered using the enter command, please try again\n";
        }
    }
    return 0;
}

