#include <iostream>
#include <fstream>
#include <cassert>
#include<string.h>
#include <stdio.h>
//                                                        
using namespace std;

const int MAX_WORDS = 30000 ;

bool open_file (ifstream& infile)
{
    assert (!infile.is_open());

    cout << "Please enter file name: ";
    char filename [80] ;
    cin.getline ( filename, 80, '\n');
    infile.open (filename );
    return infile.is_open();
}
string* put_words_in_array(ifstream& infile, int& words) {

    char c;

    string* text = new string[words], word;
    words = 0;

    infile >> word;

    while (infile >> c) {
        if (c == '\r') {
            infile >> c;
        }
        if (c == ' ' || c == '\n') {
            text[words] = word;

            ++words;
            word = "";
        } else {
            word += c;
        }
    }
    if (word.length() > 0) {
        text[words++] = word;
    }

    return text;
}

bool read_word (ifstream& infile, char word [MAX_WORDS])
{
    assert (infile.is_open());

    if (!infile.eof()) {
        infile >> word;
        return true;
    }
    return false;
}

int count_words (string*& text, ifstream& infile, int a)
{
    a = 0;
    char next [MAX_WORDS];
    while (read_word(infile, next)){
        a++;
    }
    cout << a;
    text = put_words_in_array(infile, a);

    return a;
}

void show_words (string*& text, ifstream& infile, int a)
{
    int b;
    b = count_words(text, infile, a);
    for (int i = 0; i < b; ++i) {
        cout << (i == 0 ? "" : ", ") << text[i];
    }
}

void count_word (string*& text, ifstream& infile, int a)
{
    int b;
    b = count_words(text, infile, a);
    int count=0;
    int procent = 0;
    char ch[20],word[20];
    cout<<"Enter a word to count: ";
    gets(word);

    while(!infile.eof())
    {
        infile>>ch;
        if(strcmp(ch,word)==0)
            count++;
    }

    cout<<"Occurrence="<<count<<"\n";

    cout<<"Total number of words= "<<b<<"\n";
    procent = (b / count) * 100;
    cout<<"This is a percentage of= "<<procent<<"\n";
}

void where (ifstream& infile)
{
    int c = 1;
    int count=0;
    char ch[20],word[20];
    cout<<"Enter a word: ";
    gets(word);
    cout << "The index positions of: " << word << "are ";
    while(!infile.eof())
    {
        infile>>ch;
        c++;
        if(strcmp(ch,word)==0) {
            count++ ;
            cout << c << " ";
        }
    }
    cout<<"\n"<< "And the ";
    cout<<"Occurrence="<<count<<"\n";
}

void context (string*& text, ifstream& infile, int a, string*& args, int argsLength)
{
    int m;
    int b;
    b = count_words(text, infile, a);

    try {
        m = stoi(args[1]);
    } catch (...) {
        m = -1;
    }

    if (m >= 0) {
        int count = 0;

        cout << "Found: ";
        for (int i = 0; i <= b - argsLength + 2; ++i) {
            bool match = true;
            for (int j = 2; j < argsLength; ++j) {
                if (text[i + j - 2] != args[j]) {
                    match = false;
                }
            }
            if (match) {
                ++count;

                int from = max(i - m, 0), to = min(i + argsLength - 2 + m, b);
                for (int j = from; j < to; ++j) {
                    cout << (j == from ? "" : " ") << text[j];
                }
                cout << ", ";
            }
        }

        cout << "\n" << "found: " << count << "\n";
    } else {
        cout << "Invalid m!" << "\n";
    }
}

int main()
{
    char word[MAX_WORDS];
    int a;
    string line;
    getline(cin, line);
    string args[line.length()], arg;
    int argsLength = 0;
    for (char c : line) {
        if (c != ' ') {
            arg += c;
        } else if (arg.length() > 0) {
            args[argsLength++] = arg;
            arg = " ";
        }
    }
    if (arg.length() > 0)
        args[argsLength++] = arg;
    string* text = nullptr;
    ifstream (file);
    if (open_file(file))
    {
        string command;
        cout << "\n";
        cout << "Please choose a command: ";
        cin >> command;
        if (command == "enter")
        {
            count_words(text, file, a);
        }
        else if (command == "content")
        {
            show_words(text, file, a);
        }
        else if (command == "stop")
        {
            return 0;
        }
        else if (command == "count")
        {
            count_word(text, file, a);
        }
        else if (command == "where")
        {
            where(file);
        }
        else if (command == "context")
        {
            context(text, file, a, args, argsLength);
        }
        else
            return 0;
    }
    else
        return 0;

}

