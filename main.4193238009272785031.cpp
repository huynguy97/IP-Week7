#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

//                             

const int MAX_WORDS_IN_FILE = 50000;
const int MAX_QUERY_LENGTH = 20;
const int MAX_WORD_LENGTH = 20;

char words[MAX_WORDS_IN_FILE][MAX_WORD_LENGTH];
int wordcount = 0;

void file_processing (ifstream& infile)
{
//              
    assert(infile.is_open() && MAX_WORDS_IN_FILE == 50000);
//               

    string word;
    wordcount = 0;

    while (infile >> word)
    {
        strcpy(words[wordcount], word.c_str());
        wordcount++;
    }

    infile.close();
    cout << "\nAmount of words in file: " << wordcount << endl;
}

int words_in_query (string query)
{
//              
    assert(query.length() <= MAX_QUERY_LENGTH && query[0] != 32);
//                                                                                                                           

    int amountofwords = 0;

    for (int i = 0; i <= query.length(); i++)           //                                                                
        if (query[i] == 32)
            amountofwords++;

    return amountofwords;
}

int word_context (string query, char delta)
{
//              
    assert(query.length() <= MAX_QUERY_LENGTH && query[0] != 32 && delta <= 10);
//                                                                                                               

    string interquery;
    int amountofwords = words_in_query(query),
        d = delta - '0',
        counter = 0;

    if (amountofwords == 0)                 //                                 
    {
        for (int i = 0; i < wordcount; i++)
        {
            if (query == words[i])
            {
                counter++;

                for (int j = i-d; j != i; j++)                          //                                   
                {
                    if (i-j >= 0)
                        cout << words[j] << ' ';
                }

                cout << words[i] << ' ';

                for (int k = i+1; k != i+d+1 && i+d <= wordcount; k++)  //                                   
                    cout << words[k] << ' ';

                cout << ',' << endl;
            }
        }
    }
    else                                    //                                   
    {
        for (int i = 0; i < wordcount-amountofwords; i++)
        {
            interquery = words[i];
            for (int j = 0; j < amountofwords; j++)
            {
                interquery = interquery + ' ' + string(words[i+j+1]);
                if (query == interquery)
                {
                    counter++;

                    for (int j = i-d; j != i; j++)                      //                                   
                    {
                        if (i-j >= 0)
                            cout << words[j] << ' ';
                    }

                    cout << interquery << ' ';

                    for (int k = i + 1 + amountofwords; k != i + d + 1 + amountofwords && i+d <= wordcount; k++)  //                                   
                        cout << words[k] << ' ';

                    cout << ',' << endl;

                }
            }
        }
    }
    return counter;
}

int word_position_finder (string query)
{
//              
    assert(query.length() <= MAX_QUERY_LENGTH && query[0] != 32);
//                                                                                                                                 

    string interquery;
    int amountofwords = words_in_query(query),
        counter = 0;

    if (amountofwords == 0)
    {
        for (int i = 0; i < wordcount; i++)
        {
            if (query == words[i])
            {

                counter++;
                cout << i + 1 << ' ';
            }
        }
    }
    else
    {
        for (int i = 0; i < wordcount-amountofwords; i++)
        {
            interquery = words[i];
            for (int j = 0; j < amountofwords; j++)
            {
                interquery = interquery + ' ' + string(words[i + j + 1]);
                if (query == interquery)
                {
                    counter++;
                    cout << i + 1 << ' ';
                }
            }
        }
    }
    return counter;
}

int word_counter (string query, int amountofwords)
{
//              
    assert(query.length() <= MAX_QUERY_LENGTH && amountofwords <= MAX_QUERY_LENGTH - 1 && query[0] != 32);
//                                                                                                                                                   

    string interquery;
    int counter = 0;

    if (amountofwords == 0)                 //                                 
    {
        for (int i = 0; i < wordcount; i++)
            if (query == words[i])
                counter++;
    }
    else                                    //                                   
    {
        for (int i = 0; i < wordcount-amountofwords; i++)
        {
            interquery = words[i];
            for (int j = 0; j < amountofwords; j++)
            {
                interquery = interquery + ' ' + string(words[i+j+1]);
                if (query == interquery)
                    counter++;
            }
        }
    }

    return counter;
}

bool user_input ()
{
    ifstream infile;
    string intext, infilename;
    char ignorespace;

    cout << "Good day! What can I do for you?" << endl;

    while (cin >> intext)
    {
        if (intext == "enter" || intext == "Enter")                                 //                
        {
            cin.get(ignorespace);
            getline(cin, infilename);
            infile.open(infilename.c_str());

            if(!infile.is_open())
                cout << "\nFile could not be opened. Try again..." << endl;
            else
                file_processing(infile);
        }

        else if (intext == "stop" || intext == "Stop")                              //               
            return true;

        else if (intext == "content" || intext == "Content")                        //                  
        {
            cout << "\nContent of file: " << endl;
            for (int i = 0; i < wordcount; i++)
                cout << words[i] << ' ';

            cout << endl;
            cout << endl;
        }

        else if (intext == "count" || intext == "Count")                            //                
        {
            string query;

            cin.get(ignorespace);
            getline(cin, query);

            int amountofwords = words_in_query(query);
            double percentage = (double)word_counter(query, amountofwords) / (double)wordcount * 100 * ((double)amountofwords + 1);

            cout << '\n' << '"' << query << "\" was found " << word_counter(query, amountofwords) << " times." << endl
                 << "The total number of words in the text is: " << wordcount << endl
                 << '"' << query << "\" makes up " << percentage << "% of total word-count." << endl
                 << endl;
        }

        else if (intext == "where" || intext == "Where")                            //                
        {
            string query;

            cin.get(ignorespace);
            getline(cin, query);

            cout << '\n' << '"' << query << "\" was found at positions: ";

            int counter = word_position_finder(query);

            cout << "\nIt occurred " << counter << " times in the text." << endl
                 << endl;
        }

        else if (intext == "context" || intext == "Context")                        //                  
        {
            char delta;
            string query;

            cin.get(ignorespace);
            cin.get(delta);
            cin.get(ignorespace);

            getline(cin, query);

            cout << '\n' << '"' << query << "\" was found in contexts: " << endl;

            int counter = word_context(query, delta);

            cout << "\nIt occurred " << counter << " times in the text." << endl
                 << endl;
        }

        else{
            cout    << "\nPlease choose one of the following commands: " << endl
                    << "1. \"Enter [Filename]\" \t\t opens a file for you." << endl
                    << "2. \"Stop\" \t\t\t terminates the program." << endl
                    << "3. \"Content\" \t\t\t shows the content of the opened file." << endl
                    << "4. \"Count [Search-query]\" \t shows the amount of times the search-query was found." << endl
                    << "5. \"Where [Search-query]\" \t finds the indices of the search-query and how often it occurred." << endl
                    << "6. \"Context [n] [Search-query]\"  shows n-amount of words preceding and following the search-query." << endl
                    << endl;
        }
    }
    return false;
}

int main()
{
    if(user_input())
        return 0;
    else
        return -1;
}

