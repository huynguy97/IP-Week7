#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

//                     
//                                                                                                   
//                                                                                                                                                                                                   

using namespace std;

const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_CHARS=20;
const int MAX_WORDS=30000;
string word;
string words[MAX_WORDS];
string occofseq[MAX_WORDS];
int sqnt = 0;
string seq [MAX_WORDS];
int b= 0;
int occ =0;

void open_file(char filename[MAX_FILENAME_LENGTH], ifstream& input)
{
    input.open(filename);

    if(input.is_open())
    {
        cout << "'" << filename << "'" " was opened succesfully." << endl;
    }
    else
    {
        cout << "'" << filename << "'" " was not opened." << endl;
    }
}

int input_and_count (ifstream& input, string word, string words[MAX_WORDS])
{
    //    
    assert (input);
    //     
    //                                                                                    
    int index=0;

    while(input)
    {
        input >> word;
        words[index] = word;
        index++;
    }
    return (index-1);
}

void print (string words[MAX_WORDS],int c)
{
int i = 0;
while(i<c)
{
    cout << words[i] << " ";
    i++;
}
}

void count_seq(string seq[MAX_WORDS])
{
    for (int i = 0; i < b; i++)
    {
        int sim = 0;
        for (int j = 0; j < sqnt-1; j++)
        {
            int k = i + j;
            string fileword = words[k];
            for (int k=0;k<sqnt;k++)
            {
                if (seq[k] == fileword)
                {
                    sim++;
                }
            }
        }
     if (sim == sqnt)
     {
         occofseq[occ++] = i+1;
     }
    }
}

int main()
{
    cout << "Select an Option:" << endl << "Enter" << endl << "Content" << endl << "Count" <<  endl << "Where" <<
    endl << "context" << endl << "Stop" << endl;
    string command;
    ifstream input;

    while (true)
    {
        cin >> command;
        cin.ignore(1);
        char filename[MAX_FILENAME_LENGTH];
        int c;
        if (command == "Enter")
        {
            cin.getline(filename, MAX_FILENAME_LENGTH);
            open_file(filename, input);
            c = input_and_count(input,word,words);
            cout << c << endl;
        }
        if (command == "Stop")
        {
            break;
        }
        if (command == "Content")
        {
            print(words, c);
        }
        if (command == "Count")
        {
            while(cin >> seq[sqnt])
            {
                sqnt++;
            }
            b =  input_and_count(input,word,words);
            count_seq(seq);
            int f;
            f = occ;
            cout << f;
        }
    }

    return 0;
}

