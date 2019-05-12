/* 
                       

                                                                                                      
                                                                                                     
                                                                                                      
                                                                                                        
                                                 
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <cassert>
#include <sstream>

using namespace std;

const int MAX_WORDS_IN_FILE = 30000 ;

void console_with_file(string words[MAX_WORDS_IN_FILE], int filesize)
{
    //              
    assert(filesize >= 0);
    /*                 
                                                           
                                
                                                          
                                                                   
                                                    
                                                                                            
    */

    string command;
    cin >> command;
    while (command != "stop")
    {
        if(command == "enter")
        {
            cout << "file already opened" << endl;
        }
        else if(command == "content")
        {
            for(int i = 0; i < filesize; i++)
            {
                cout << words[i] << endl;
            }
        }
        else if(command == "count")
        {
            cin.get();
            int counter = 1;
            string wordSequenceLine;
            getline(cin, wordSequenceLine);
            for(int i = 0; i < wordSequenceLine.size(); i++)
            {
                if(wordSequenceLine[i] == ' ')
                {
                    counter++;
                }
            }
            string wordSequence[counter];
            int counter2 = 0;
            for(int j = 0; j < counter; j++)
            {
                string temp = "";
                char temp2;
                temp2 = wordSequenceLine[counter2];
                while(temp2 != ' ')
                {
                    temp += temp2;
                    counter2++;
                    if(counter2 < wordSequenceLine.size())
                        temp2 = wordSequenceLine[counter2];
                    else break;
                }
                counter2++;
                wordSequence[j] = temp;
            }

            int counter3 = 0;
            for(int k = 0; k < filesize; k++)
            {
                bool occurrence = true;
                if(words[k] == wordSequence[0])
                {
                    for(int l = 1; l < counter; l++)
                    {
                        if(words[k+l] != wordSequence[l])
                        {
                            occurrence = false;
                        }
                    }
                    if(occurrence)
                    {
                        counter3++;
                    }
                }
            }

            double percentage = ((double)counter3 / (double)filesize) * 100;
            cout << "number of occurrences: " << counter3 << endl;
            cout << "total number of words: " << filesize << endl;
            cout << "percentage of the words: " << percentage << "%"<< endl;

        }
        else if(command == "where")
        {
            cin.get();
            int counter = 1;
            string wordSequenceLine;
            getline(cin, wordSequenceLine);
            for(int i = 0; i < wordSequenceLine.size(); i++)
            {
                if(wordSequenceLine[i] == ' ')
                {
                    counter++;
                }
            }
            string wordSequence[counter];
            int counter2 = 0;
            for(int j = 0; j < counter; j++)
            {
                string temp = "";
                char temp2;
                temp2 = wordSequenceLine[counter2];
                while(temp2 != ' ')
                {
                    temp += temp2;
                    counter2++;
                    if(counter2 < wordSequenceLine.size())
                        temp2 = wordSequenceLine[counter2];
                    else break;
                }
                counter2++;
                wordSequence[j] = temp;
            }
            cout << "indexes of the occurrences of the word(s): " << endl;
            int counter3 = 0;
            for(int k = 0; k < filesize; k++)
            {
                bool occurrence = true;
                if(words[k] == wordSequence[0])
                {
                    for(int l = 1; l < counter; l++)
                    {
                        if(words[k+l] != wordSequence[l])
                        {
                            occurrence = false;
                        }
                    }
                    if(occurrence)
                    {
                        counter3++;
                        cout << k + 1 << endl;
                    }
                }
            }
            cout << "number of occurrences: " << counter3 << endl;

        }
        else if(command == "context")
        {
            int numberOfWords;
            cin >> numberOfWords;
            cin.get();
            int counter = 1;
            string wordSequenceLine;
            getline(cin, wordSequenceLine);
            for(int i = 0; i < wordSequenceLine.size(); i++)
            {
                if(wordSequenceLine[i] == ' ')
                {
                    counter++;
                }
            }
            string wordSequence[counter];
            int counter2 = 0;
            for(int j = 0; j < counter; j++)
            {
                string temp = "";
                char temp2;
                temp2 = wordSequenceLine[counter2];
                while(temp2 != ' ')
                {
                    temp += temp2;
                    counter2++;
                    if(counter2 < wordSequenceLine.size())
                        temp2 = wordSequenceLine[counter2];
                    else break;
                }
                counter2++;
                wordSequence[j] = temp;
            }
            cout << "the context of the word(s): " << endl;
            int counter3 = 0;
            for(int k = 0; k < filesize; k++)
            {
                bool occurrence = true;
                if(words[k] == wordSequence[0])
                {
                    for(int l = 1; l < counter; l++)
                    {
                        if(words[k+l] != wordSequence[l])
                        {
                            occurrence = false;
                        }
                    }
                    if(occurrence)
                    {
                        counter3++;
                        for(int m = k - numberOfWords; m < (k + counter + numberOfWords); m++)
                        {
                            if(m >= 0 && m < filesize)
                            {
                                cout << words[m] << " ";
                            }
                        }
                        cout << "\n";
                    }
                }
            }

            cout << "number of occurrences: " << counter3 << endl;

        }
        else cout << "unknown command" << endl;
        cin >> command;
    }
}

void console_without_file(string words[MAX_WORDS_IN_FILE])
{
    //              
    assert(MAX_WORDS_IN_FILE > 0);
    /*                 
                                                           
                                
                                     
                                                       
                                                       
                                                         
    */

    cout << "enter commands" << endl;
    string command;
    cin >> command;
    ifstream input;

    while (command != "stop")
    {
        if(command == "enter")
        {
            string filename;
            cin.get();
            getline(cin, filename);
            input.open(filename.c_str());
            if(input.is_open())
            {
                cout << "file opened successfully!" << endl;
                int counter = 0;
                while(!input.eof())
                {
                    input >> words[counter];
                    counter++;
                }
                console_with_file(words, counter);
                input.close();
                return;
            }
            else cout << "couldn't open file" << endl;
        }
        else if(command == "content" || command == "count" || command == "where" || command == "context")
        {
            cout << "no file opened yet" << endl;
        }
        else cout << "unknown command" << endl;
        cin >> command;
    }
}

int main()
{
    string words[MAX_WORDS_IN_FILE];
    console_without_file(words);
    return 0;
}

