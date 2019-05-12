#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

using namespace std;

const int MAX_CHARACTERS = 80;
const int MAX_WORDS = 30000;
string text[MAX_WORDS];
int words_in_text;
string command [MAX_CHARACTERS];
char filename [MAX_CHARACTERS];
bool again = true;
int words = 0;

void put_text_in_array(ifstream& inputfile, char filename[MAX_CHARACTERS])
{
    //                
    assert( inputfile );
    //                 
    inputfile.close();
    inputfile.open(filename);

    int index = 0;
    string word;
    while(inputfile >> word)
    {
    text[index] = word;
    index++;
    }

}

bool enter_filename(ifstream& inputfile, char filename[MAX_CHARACTERS])
{
    //                
    assert( true );
    //                 
    char c;
    int index = 0;
    bool enter = true;
    while(index < MAX_CHARACTERS && enter == true)
    {

        cin.get(c);
        if(c == '\n')
        {
            c = '\0';
            filename[index] = c;
            enter = false;

        }
        else
        {
            filename[index] = c;
        }
        index++;
    }

}

int count_words(istream& inputfile, int words)
{
    //                
    assert(inputfile);
    //                 
    char c;
    while(inputfile)
        {

            inputfile.get(c);
            if(c == ' ')
            {
                words++;
            }
        }
    words++;
    words_in_text = words;
    return words;
}

int open_file(ifstream& inputfile, int words, string choice)
{
    //                
    assert( choice == "enter" );
    //                 
    enter_filename(inputfile, filename);

    inputfile.open(filename);

    if(inputfile)
    {
        words = count_words(inputfile,words);
        cout << "The number of words: " << words << "\n \n";
        inputfile.close();
        inputfile.open(filename);
    }
    else
    {
        cout << "Couldn't open file \n";
    }
    put_text_in_array(inputfile, filename);
    return words;
}

void content_text(int words)
{
    //                
    assert(words > 0);
    //                                                    
    for(int i = 0;i < words; i++)
    {
        cout << text[i] << " ";
    }
}

bool what_command (char filename [MAX_CHARACTERS])
{
    //                
    assert( true );
    //                                                                                 

    string choice;
    ifstream inputfile;

    cout << "Enter a command: ";
    cin >> choice;

    char c;
    cin.get(c);

    if(choice == "enter") {words = open_file(inputfile, words, choice);}
    else
    {
        string line;
        getline(cin, line);

        string args[line.length()], arg;
        int argslength = 0;

        for (char c : line) {
            if (c != ' ') {
                arg += c;
            } else if (arg.length() > 0) {
                args[argslength++] = arg;
                arg = "";
            }
        }
        if (arg.length() > 0)
            args[argslength++] = arg;

        if(choice == "content") {content_text(count_words(inputfile, words));}

        else if(choice == "stop") { return false;}

        else if(choice == "count") {
            int count = 0;
                for (int i = 0; i <= words; i++)
                {
                    bool same = true;
                    for (int j = 0; j < argslength; j++) {
                        if (text[i + j - 1] != args[j]) {
                            same = false;
                        }
                    }
                    if (same)
                    {
                        ++count;
                    }
                }
                cout << "Found sequince " << count << " times in " << words << " this is " << (double) count / words * 100 << "% \n";
        }
        else if(choice == "where")
        {
            int count = 0;

            cout << "Index positions: ";
            for (int i = 0; i <= words - argslength + 1; ++i) {
                bool same = true;
                for (int j = 0; j < argslength; ++j) {
                    if (text[i + j - 1] != args[j]) {
                        same = false;
                    }
                }
                if (same) {
                    ++count;
                    cout << i + 1 << ", ";
                }
            }
            cout << "number of found occurrences: " << count << "\n";
        }
        else if(choice == "context")
        {
            int m;
            int count = 0;
            m = std::stoi(args[0]);
            cout << m;

            for (int i = 0; i <= words - argslength; ++i) {
                bool same = true;
                for (int j = 0; j < argslength - 1; ++j) {
                    if (text[i + j - 1] != args[j+1]) {
                        same = false;
                    }
                }
                if (same)
                {
                    ++count;
                    int min = i - m - 1;
                    int max = i + argslength - 2 + m;

                    for(int index = min; index < max; index++)
                    {
                        if(index >= 0 && index < words)
                        {
                        cout << " " << text[index];
                        }
                    }
                    cout << ", ";
                }
            }

        cout << "\nnumber of found occurrences:  " << count << "\n";
        }

            else {cout << "Wrong command\n";}
    }
    return true;
}

int main()
{

    while(again)
    {
        again = what_command(filename);
    }
}

