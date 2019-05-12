#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <assert.h>

using namespace std;

const int MAXWORDS = 30000;

string enteringName ()
{
//              
assert(true);
/*
                
                              
*/
    string filename;
    cin.ignore(1);
    getline(cin, filename, '\n');
    return filename;
}

int enter_filename (string fileContent [MAXWORDS])
{
//              
assert(MAXWORDS > 0);
/*
                
                                                                                                   
                                                                                 
*/
   string filename = enteringName();
   ifstream inputFile (filename.c_str());
   if (inputFile.is_open())
   {
        int i = 0;
        while (i < MAXWORDS-1 && inputFile)
        {
            inputFile >> fileContent [i];
            i++;
        }
        int numWords = i-1;
        cout << "The number of words is " << numWords << endl;
        inputFile.close();
        return numWords;
   }
   else
   {
       cout << "File could not be opened." << endl;
   }
}

void content (string fileContent [], int numWords)
{
//              
assert(numWords > 0 && numWords < MAXWORDS);
/*
                
                                                                    
                                               
*/
    int i = 0;
    while (i < numWords)
    {
        cout << fileContent[i] << " ";
        i++;
    }
    cout << endl;
}

void count (string word, int numWords, string fileContent [MAXWORDS])
{
//              
assert(numWords > 0 && numWords < MAXWORDS && MAXWORDS > 0);
/*
                
                                                                                                                                           
*/
    int occurrences = 0;
    int i = 0;
    while (i < numWords)
    {
        if (fileContent [i] == word)
        {
            occurrences++;
        }
        i++;
    }
    if (occurrences != 0)
    {
        cout << "The number of occurrences of '" << word << "' is " << occurrences << "." << endl;
        cout << "The total of times '" << word << "' occurs in the text is " << numWords << "." << endl;
        double percentage = ((occurrences * 100.0)/ numWords);
        cout << "The percentage of the word '" << word << "' is " << percentage << "%." << endl;
    }
}

void where (string word, int numWords, string fileContent [MAXWORDS])
{
//              
assert(numWords > 0 && numWords < MAXWORDS && MAXWORDS >0);
/*
                
                                                                                                     
*/
    int i = 0;
    int occurrences = 0;
    cout << "The word '" << word << "' occurs at index-positions:";
    while (i < numWords)
    {
        if (fileContent [i] == word)
        {
            cout << " " << i+1;
            occurrences++;
        }
        i++;
    }
    if (occurrences != 0)
    {
        cout << "." << endl;
        cout << "The total number of occurrences is " << occurrences << "." << endl;
    }
}

void displayContext (int m, int i, string fileContent [MAXWORDS])
{
//              
assert(m > 0 && i >= 0 && MAXWORDS > 0);
/*
                
                                                                                                          
                                             
*/
    int index = 0;
    int a = m;
    int b = 0;
    while (a != 0)
    {
        if (i-a >= 0)
        {
            cout << fileContent [i-a] << " " ;
        }
        a = a-1;
    }
    while (b != m+1)
    {
        cout << fileContent [i+b] << " " ;
        b++;
    }
    cout << endl;
}

void context (string word, int m, int numWords, string fileContent [MAXWORDS])
{
//              
assert(m > 0 && numWords > 0 && numWords < MAXWORDS && MAXWORDS > 0);
/*
                
                                                                                                          
                                                                                                     
*/
    int i = 0;
    int occurrences = 0;
    while (i < numWords)
    {
        if (fileContent [i] == word)
        {
            occurrences++;
            cout << "Context of an occurrence: ";
            displayContext(m, i, fileContent);
            cout << endl;
        }
        i++;
    }
    if (occurrences != 0)
    {
        cout << "The number of occurrences of the word '" << word << "' is " << occurrences << "." << endl;
    }
}

int main()
{
    string command;
    string fileContent [MAXWORDS];
    bool fileRead = false;
    do
    {
        cout << "Please enter a command: " << endl;
        cin >> command;
        int numWords;
        if (command == "enter")
        {
            numWords = enter_filename(fileContent);
            fileRead = true;
        }

        if (command == "content")
        {
            if (fileRead)
            {
                content(fileContent, numWords);
            }
            else
            {
                cout << "Please enter a filename first." << endl;
            }
        }

        if (command == "count")
        {
            string words [MAXWORDS];
            int i = 0;
            while (i < MAXWORDS)
            {
                cin >> words [i];
                if (fileRead)
                {
                    int n = 0;
                    while (n < MAXWORDS)
                    {
                        count(words [n], numWords, fileContent);
                        n++;
                    }

                }
                else
                {
                    cout << "Please enter a filename first." << endl;
                }
            }
        }

        if (command == "where")
        {
            string words [MAXWORDS];
            int i = 0;
            if (fileRead)
            {
                while (i < MAXWORDS)
                {
                    cin >> words [i];
                    where(words [i], numWords, fileContent);
                }
            }
            else
            {
                cout << "Please enter a filename first." << endl;
            }
        }

        if (command == "context")
        {
            int m;
            string word;
            if (fileRead)
            {
                cin >> m;
                cin >> word;
                context(word, m, numWords, fileContent);
            }
            else
            {
                cout << "Please enter a filename first." << endl;
            }
        }
    }
    while (command != "stop");
    return 0;
}

