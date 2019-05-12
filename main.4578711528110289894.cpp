#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

/*                                                                      
                                                                        

             
                                                                                                                                                      
                                                                                                                                          */

using namespace std;
const int MAX_FILENAME_LENGTH=80;
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;
const int length = 5000;
char file[MAX_WORDS][MAX_CHARS];
int amnt =0;
char text[length];

void help()
{
    cout << endl << "Command list:" << endl;
    cout << "ENTER_[filename]:                      opens file [filename]." << endl;
    cout << "CONTENT:                               displays all stored words in their order of appearance." << endl;
    cout << "COUNT_[word1]_..._[wordn]:             displays all stored words, the total amount of words in \n                                       the text and percentage of input word appearance in text." << endl;
    cout << "WHERE_[word1]_..._[wordn]:             displays all index positions of input word and amount of \n                                       times this word appears." << endl;
    cout << "CONTEXT_[index]_[word1]_..._[wordn]:   displays how many times input words appear before word \n                                       number [index], after word number [index] and in total." << endl;
    cout << "STOP:                                  the program terminates." << endl << endl;
}

bool read_word(ifstream& infile, char word[MAX_CHARS])
{
    infile >> word;
    if(!infile)
        return false;
    else
        return true;
        //                          
}

bool openfile(ifstream& infile)
{
    int counter=0;
    cin.get();
    char filename[80], word[MAX_CHARS];
    cin.getline(filename, 80, '\n');
    infile.open(filename);
    if(infile.is_open())
    {
        cout << "File " << filename << " was successfully opened." << endl;
    }
    else
    {
        cout << "File " << filename << " could not be opened." << endl;
    }
    //                             
    while (read_word(infile, word))
    {
        strcpy(file[counter],word);
        amnt++;
        counter++;
    }
    counter=0;
    char character='a';
    while (infile)
    {
        infile.get(character);
        text[counter]=character;
        counter++;
    }
    return infile.is_open();
}

bool check(ifstream& infile, char word[MAX_CHARS], char wordlist[MAX_WORDS][MAX_CHARS])
{
    int counter=0;
    while (word != wordlist[counter])
    {counter++;
    if(counter>=MAX_WORDS)
        return true;
    }
    return false;
}

void showcontent(ifstream& infile)
{
    int counter=0;
    char word[MAX_CHARS], character;
    while (counter <= amnt)
    {
        cout << file[counter];
        cout << endl;
        counter++;
    }
}

bool checkword(char word[MAX_CHARS], int wordlength, int pos)
{
    int counter=0, counter2=0;
    while(counter<=wordlength)
    {
        if(text[pos+counter]==word[counter])
            counter2++;
        counter++;
    }
    if(counter2==wordlength)
        return true;
    else
        return false;
}

void countwords(ifstream& infile)
{
    cin.get();
    int counter=0, pos=0, tally=0;;
    char word[MAX_CHARS], c=cin.get();
    while(c!='\n')
    {
        word[counter] = c;
        counter++;
        c=cin.get();
    }
    counter=0;
    while(word[counter]!=0)
        counter++;
    int wordlength=counter;
    counter=0;
    while(pos<=length)
    {
        if(checkword(word, wordlength, pos))
            tally++;
        pos++;
    }
    cout << word << " " << tally;
//                                                
}

void where(ifstream& infile)
{
/*                              
                                                                                                                                             
                                      
                                                                                              */
}

void context(ifstream& infile)
{
/*                                                                                                                                         
             
*/
}

void console()
{
    ifstream filein;
    cout << "Type HELP for help." << endl << endl;
    string command = "a";
    while (command!="STOP")
    {
        cin >> command;
        if(command == "ENTER")
            openfile(filein);
        else if (command == "CONTENT")
            showcontent(filein);
        else if (command == "HELP")
            help();
        else if (command == "COUNT")
            countwords(filein);
        else if (command == "WHERE")
            where(filein);
        else if (command == "CONTEXT")
            context(filein);
        else if (command != "STOP")
            cout << endl << "Command " << command << " is not a valid command." << endl;
    }
    filein.close();
    cout << "Program terminated." << endl;
}

int main()
{
    console();
    return 0;
}

