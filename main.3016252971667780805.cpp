#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstdlib>
using namespace std;

/*
                                                  

                              

                                                  

                                          
                                          

                                                  
*/

const int MAX_WORDS = 30000; //                                                                                          
const int MAX_PARAMS = 37; //                                                                              

string words[MAX_WORDS];
int total_words = 0;

int split_parameters(string parameters, string params[])
{   //               
    assert(true);
    //                
    //                                          

    int pos = 0;

    for (int i=0; i<parameters.length(); i++)
    {
        char c = parameters.at(i);

        if (c == ' ')
        {
            pos++;
            if (pos >= MAX_PARAMS)
            {
                cout << "Error: Too many parameters, you can have at most " << MAX_PARAMS << " parameters." << endl;
                return 0;
            }
        } else {
            params[pos] += c;
        }
    }

    return pos+1;
}

void split_command(string& command, string& parameters)
{   //               
    assert(true);
    //                
    //                                                                                                                      

    string output_command = "";
    parameters = "";

    bool encountered_first_space = false;

    for (int i=0; i<command.length(); i++)
    {
        char c = command.at(i);

        if (c == ' ' && !encountered_first_space)
        {
            encountered_first_space = true;
        } else {
            if (encountered_first_space)
                parameters += c;
            else
                output_command += c;
        }
    }

    command = output_command;
}

bool read_word(ifstream& infile, string& word)
{   //               
    assert(infile.is_open());
    //                
    //                                                                   
    infile >> word ;

    //                                                             
    if (word.length() == 0 && infile)
        read_word(infile, word);

    return infile;
}

bool save_word(string word, int& no)
{   //               
    assert(no >= 0 && no < MAX_WORDS);
    //                
    //                                                                                                               
    //                                                     

    if (no < MAX_WORDS)
    {
        words[no] = word;
        no++;
        return true;
    }
    return false;
}

int count_all_words(ifstream& infile)
{   //               
    assert(infile.is_open());
    //                
    //                                             
    int no = 0;
    string next;
    while(read_word(infile, next) && save_word(next, no) && no < MAX_WORDS);
    return no;
}

void command_enter(string parameters)
{   //               
    assert(true);
    //                
    //                                                                                                             

    if (parameters.length() == 0)
    {
        cout << "Missing parameter: please enter the filename of the file you want to analyze." << endl;
        return;
    }

    ifstream infile(parameters.c_str());

    if (infile.is_open())
    {
        total_words = count_all_words(infile);
        infile.close();
        cout << "File has been read, total number of words is " << total_words << endl;
    } else {
        cout << "Error: Something went wrong when trying to open the file..." << endl;
    }
}

void command_content()
{   //               
    assert(true);
    //                
    //                                                 
    cout << "Here are all the words from the file (separated by commas): " << endl;

    for (int i=0; i<total_words-1; i++)
        cout << "\'" << words[i] << "\', ";

    cout << "\'" << words[total_words-1] << "\'" << endl;
}

void command_count(string parameters)
{   //               
    assert(true);
    //                
    //                                                                                                               

    if (parameters.length() == 0)
    {
        cout << "Missing parameter: please enter the word sequence to count." << endl;
        return;
    }

    string params[MAX_PARAMS];
    int number_of_params = split_parameters(parameters, params);

    //                       
    int number_of_occurrences = 0;
    for (int i=0; i<total_words; i++)
    {
        if (words[i] == params[0])
        { //                                                                                
            bool correct = true;
            for (int j=1; j<number_of_params; j++)
            {
                if (words[i+j] != params[j])
                    correct = false;
            }
            if (correct) {
                number_of_occurrences++;
            }
        }
    }
    int percentage = (number_of_occurrences+0.0) / total_words * 100;

    cout << "Number of occurrences: " << number_of_occurrences << endl;
    cout << "Total number of words: " << total_words << endl;
    cout << "Percentage: " << percentage << "%" << endl;
}

void command_where(string parameters)
{   //               
    assert(true);
    //                
    //                                                                                                       

    if (parameters.length() == 0)
    {
        cout << "Missing parameter: please enter the word sequence to look for." << endl;
        return;
    }

    string params[MAX_PARAMS];
    int number_of_params = split_parameters(parameters, params);

    cout << "The word sequence can be found at word position ";

    //                       
    bool found_first_result = false;
    int number_of_occurrences = 0;
    for (int i=0; i<total_words; i++)
    {
        if (words[i] == params[0])
        { //                                                                                
            bool correct = true;
            for (int j=1; j<number_of_params; j++)
            {
                if (words[i+j] != params[j])
                    correct = false;
            }
            if (correct) {
                if (!found_first_result)
                {
                    found_first_result = true;
                    cout <<(i+1);
                } else {
                    cout << ", " << (i+1);
                }
                number_of_occurrences++;
            }
        }
    }

    cout << endl << "Number of occurrences: " << number_of_occurrences << endl;
}

string concat_words_with_spaces(int from, int to)
{   //               
    assert(from >= 0 && to < MAX_WORDS && from <= to);
    //                
    //                                                                                                               

    int number_of_words = to - from + 1;

    string output = words[from];
    for (int i=1; i<number_of_words; i++)
        output += " " + words[from + i];

    return output;
}

void command_context(string parameters)
{   //               
    assert(true);
    //                
    //                                                                                                                      

    if (parameters.length() == 0)
    {
        cout << "Missing parameter: please enter the value of m, followed by the word sequence to search for." << endl;
        return;
    }

    string params[MAX_PARAMS];
    int number_of_params = split_parameters(parameters, params) - 1; //                                              

    int m = atoi(params[0].c_str()); //                                                 

    cout << "The word sequence can be found in the following contexts: " << endl;

    //                       
    int number_of_occurrences = 0;

    for (int i=0; i<total_words; i++)
    {
        if (words[i] == params[1])
        { //                                                                                
            bool correct = true;
            for (int j=1; j<number_of_params; j++)
            {
                if (words[i+j] != params[j+1])
                    correct = false;
            }
            if (correct) {
                int from = i-m;
                if (from < 0)
                    from = 0;

                int to = i+m+number_of_params-1;
                if (to > total_words-1)
                    to = total_words-1;

                cout << " \'" << concat_words_with_spaces(from, to) << "\'" << endl;

                number_of_occurrences++;
            }
        }
    }

    cout << "Number of occurrences: " << number_of_occurrences << endl;
}

int main()
{
    cout << "Please enter a command, possible commands are \'content\', \'context\', \'count\', \'enter\', \'stop\' and \'where\'." << endl;
    bool exit = false;
    while (!exit)
    {
        string command;
        cout << "> ";
        getline(cin, command);
        string parameters;
        split_command(command, parameters);

        //                       
        if (command == "enter")
            command_enter(parameters);
        else if (command == "content")
            command_content();
        else if (command == "stop")
            exit = true;
        else if (command == "count")
            command_count(parameters);
        else if (command == "where")
            command_where(parameters);
        else if (command == "context")
            command_context(parameters);
        else
            cout << "Unknown command: " << command << ", please enter a valid command." << endl;
    }
    return 0;
}

