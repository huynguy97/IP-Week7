#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

//                                                                                

const int MAX_WORDS = 50000;
const int MAX_OCCURRENCES = 5000;
const int MAX_INPUT = 20;

//                                                                     
//                                                                                                                
//                                                                                                      
bool OpenFile(ifstream& filename, const char* name)
{
//                
    assert (true);
/*                  
                                                                                                                                                  
                         
*/
    filename.open(name);
    if (!filename.is_open())
        return false;
    return true;
}

//                                                                                                                                  
//                                                                             
int ReadFile(ifstream& filename, string words[MAX_WORDS])
{
//                
    assert (filename.is_open());
/*                  
                                                                                                                                    
*/
    string word = "";
    int counter = 0;
    while ((filename >> word) && counter < MAX_WORDS)
    {
        words[counter] = word;
        counter++;
    }
    return counter;
}

//                                                                                                                                                 
//                                                                                                                                             
int ExtractInput(string input[MAX_INPUT])
{
//                                                                                             
//                                                      
    assert (true);
/*                  
                                                                                                      
                                                                                                            
*/
    string userInput = "";
    size_t position = 0; //                                                                      
    getline(cin, userInput);
    userInput.erase(0, 1);
    int noOfWords = 0;
    while ((position = userInput.find(" ")) != string::npos)
//                                                                                                                                               
//                                                                                                                             
    {
        if (noOfWords >= MAX_INPUT - 2)
//                                                                                                                                            
//                                                
        {
            cout << "Too much input." << endl;
            return -1;
        }
        input[noOfWords] = userInput.substr(0, position);
        userInput.erase(0, position + 1);
        noOfWords++;
    }
    input[noOfWords] = userInput;
    noOfWords++;
//                                                                                                                               
    return noOfWords;
}

//         
int CountWordSequence(string input[MAX_INPUT], int inputLength, string words[MAX_WORDS], int noOfWords,
                      int indices[MAX_OCCURRENCES] = {}, bool use = false)
{
//                
    assert (inputLength > 0);
/*                  
                                                                                                               
                                                                                                   
*/
    int counter = 0;
    int occurrence = 0;
    for (int i = 0; i < noOfWords; i++)
    {
        if (counter == inputLength)
        {
            counter = 0;
            if (use)
                indices[occurrence] = i - inputLength;
            occurrence++;
        }
        if (words[i] == input[counter])
            counter++;
        else
        {
            if (counter > 0)
                i--;
            counter = 0;
        }
    }
    return occurrence;
}

//                                               
void PrintContext(string words[MAX_WORDS], int noOfWords, int indices[MAX_OCCURRENCES], int numberOfIndices, int inputLength, int contextSize)
{
//                
    assert (contextSize >= 0);
/*                  
                                                                                                                              
                                                    
*/
    for (int i = 0; i < numberOfIndices; i++)
    {
        for (int j = -contextSize; j < (inputLength + contextSize); j++)
        {
            if (!(indices[i] + j < 0) && !(indices[i] + j > noOfWords))
                cout << words[indices[i] + j] << " ";
        }
        cout << "\n\n";
    }
}

//         
void Help()
{
//                
    assert (true);
/*                  
                                                                                                                  
*/
    cout << "Valid commands are:\n"
         << "enter\tFollow this up with the name of a file (with extension) that you would like to open to open that file.\n"
         << "content\tThis displays all different words in the file, in order of their appearance.\n"
         << "count\tFollow this up with one or more words, to count how many times that word sequence occurs in the text,\n"
         << "\tas well as the total number of words in the text, and the percentage that the occurrence rate makes up\n"
         << "\tof the total number of words, in that order.\n"
         << "where\tFollow this up with one or more words, to be shown where this word (sequence) occurs in the text,\n"
         << "\tas well as the number of times it occurs in the text.\n"
         << "context\tFollow this up with an integer number and one or more words to be shown those words\n"
         << "\tand that number of words immediately preceding and following it in the text,\n"
         << "\tfor each occurrence of that word sequence.\n"
         << "stop\tThis terminates the program.\n";
}

//         
void Command()
{
//                
    assert (true);
/*                  
                                                                                                
*/
    ifstream filename;
    string command = "";
    string name = "";
    string input[MAX_INPUT];
    int noOfWords = 0;
    int occurrence = 0;
    int inputLength = 0;
    int indices[MAX_OCCURRENCES];
    const char* newName;
    string words[MAX_WORDS];
    while (command != "stop")
    {
        cout << "Please enter a command (or 'help'):" << endl;
        cin >> command;
        if (command == "enter")
        {
            getline(cin, name);
            name.erase(0, 1); //                                                                               
            newName = name.c_str();
            if (!OpenFile(filename, newName))
            {
                cout << "Filename was incorrect. The program will now terminate." << endl;
                return;
            }
            noOfWords = ReadFile(filename, words);
            cout << "The number of words in this file is " << noOfWords << "." << endl;
        }
        else if (command == "content")
        {
            for (int i = 0; i < noOfWords; i++)
                cout << words[i] << ((i % 10 == 0) ? "\n" : " ");
        }
        else if (command == "count")
        {
            inputLength = ExtractInput(input);
            if (inputLength == -1)
            {
                cout << "Input was incorrect. The program will now terminate." << endl;
                return;
            }
            occurrence = CountWordSequence(input, inputLength, words, noOfWords);
            cout << occurrence << ", " << noOfWords << ", " << ((double)occurrence / (double)noOfWords * 100.0) << endl;
        }
        else if (command == "where")
        {
            inputLength = ExtractInput(input);
            if (inputLength == -1)
            {
                cout << "Input was incorrect. The program will now terminate." << endl;
                return;
            }
            occurrence = CountWordSequence(input, inputLength, words, noOfWords, indices, true);
            for (int i = 0; i < occurrence; i++)
            {
                cout << indices[i];
                if (i < occurrence - 1)
                    cout << ", ";
                if (i % 15 == 0 && i != 0)
                    cout << endl;
            }
            cout << "\nNumber of occurrences: " << occurrence << endl;
        }
        else if (command == "context")
        {
            int contextSize = 0;
            cin >> contextSize;
            inputLength = ExtractInput(input);
            if (inputLength == -1)
            {
                cout << "Input was incorrect. The program will now terminate." << endl;
                return;
            }
            occurrence = CountWordSequence(input, inputLength, words, noOfWords, indices, true);
            PrintContext(words, noOfWords, indices, occurrence, inputLength, contextSize);
        }
        else if (command == "help")
        {
            Help();
        }
        else if (command == "stop")
            filename.close();
        cout << endl;
    }
}

int main()
{
    Command();
    return 0;
}

