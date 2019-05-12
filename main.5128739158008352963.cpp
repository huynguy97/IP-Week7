#include <iostream>
#include <fstream>
#include <string.h>
#include <cassert>

using namespace std;

const int MAX_INPUT_LENGTH = 100,MAX_WORD_LENGTH = 20,MAX_WORDS = 50000, MAX_WORDS_SEARCH = 200, MAX_SEARCH_LENGTH = 2000,MAX_FILENAME_LENGTH = 80;

bool read_word(ifstream& infile, char word[MAX_WORD_LENGTH])
{
    infile >> word;
    return infile;
}

void enter(ifstream& file, char words[MAX_WORDS][MAX_WORD_LENGTH])
{
    assert(file.is_open());

    //                                        

    char word[MAX_WORD_LENGTH];
    int i = 0;
    while(read_word(file, word))
    {
        for(int j = 0; j < MAX_WORD_LENGTH; j++)
        {

            if(word[j] > 64 && word[j] < 91)
                word[j] += 97-65; //                                 
            if((word[j] <= 96 || word[j] >= 123) && word[j] != '\'')
                word[j] = '\0'; //                                                                                       
            words[i][j] = word[j];
        }
        i++;
    }
}

int splitwords(char line[MAX_WORDS_SEARCH], char words[MAX_WORDS][MAX_WORD_LENGTH])
{
    int wordno=0,letterno=0;
    for(int i=0; i < strlen(line);i++)
    {
        if(line[i] != ' ')
            words[wordno][letterno] = line[i];
        else
        {
            words[wordno][letterno] = '\0';
            wordno++;
            letterno = 0;
        }
        letterno++;
    }
    return wordno;
}

void countwords(char words[MAX_WORDS][MAX_WORD_LENGTH])
{
    char line[MAX_SEARCH_LENGTH], searchwords[MAX_WORDS_SEARCH][MAX_WORD_LENGTH];
    cout<< "Enter a word sequence:"<< endl;
    cin.getline(line,MAX_SEARCH_LENGTH);
    int amount=0, wordno,i=0,j;

    wordno = splitwords(line,searchwords);
    while( i<MAX_WORDS)
    {
        j=0;
        if(strcmp(words[i],searchwords[j]) == 0)
        {
            i++;
            j++;
            bool same = true;
            while(same && j<wordno && i < MAX_WORDS)
            {
                if(strcmp(words[i],searchwords[j]) != 0)
                    same = false;
                i++;
                j++;
            }
            if (same)
                amount++;
        }
    }

    cout << amount<< endl;
}

bool open_text_file(ifstream& file, char filename[MAX_FILENAME_LENGTH])
{
    file.open(filename);
    if(file.is_open())
        return true;
    else
    {
        cout << "Can't open file: " << filename << endl;
        return false;
    }
}

bool getinput(char command[7],char input2[MAX_INPUT_LENGTH-7])
{
    for(int i=0; i<7; i++)
        command[i] = '\0';
    char input[MAX_INPUT_LENGTH];
    cin.getline(input, MAX_INPUT_LENGTH);
    int inputlen = strlen(input);
    bool firstspace = false;
    int i=0,j=0;

    while(i<inputlen)
    {
        if(input[i] != ' ' && !firstspace)
        {
                command[i] = input[i];
                i++;
        }
        else if (input[i] == ' ' && !firstspace)
        {
            firstspace = true;
            command[i] = '\0';
            i++;
        }
        else
        {
            input2[j] = input[i];
            i++;
            j++;
        }
    }
    return true;

}

int where(char seq[MAX_WORDS][MAX_WORD_LENGTH], char words[MAX_WORDS][MAX_WORD_LENGTH])
{
    char seek[MAX_WORDS][MAX_WORD_LENTGH];
    splitwords(seq, seek);
    bool found = true;
    int index;
    for(int i = 0; i < MAX_WORDS; i++)
    {
        if(strcmp(words[i], seek[0]) == 0)
        {
            for(int j = i+1; j < MAX_WORDS && found; j++)
            {
                if(strcmp(words[j], seek[0]) != 0)
                    found = false;
            }
        }
    }
    if(found)
    {
        cout i+1 << endl;
        return i+1;
    }
    else return 0;

}

int main()
{

    char command[7], input2[MAX_INPUT_LENGTH-7];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    bool running = true;

    while(running)
    {
        getinput(command,input2);
        if(strcmp("enter",command) == 0)
        {
            ifstream file;
            open_text_file(file, input2);
            enter(file, words);
        }

       //                                        
            //          
        else if(strcmp("stop",command) == 0)
            running = false;
        else if(strcmp("count",command) == 0)
            countwords(words);
        else if(strcmp("where",command) == 0)
            where("rose is",words);
       //                                        
            //          
        else
            cout<< "Command unknown, please enter a valid command." << endl;

    }

    return 0;
}

