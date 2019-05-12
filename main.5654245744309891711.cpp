#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_INPUT_LENGTH = 100;
bool run = true;
string words [100000];
ifstream infile;

string only_lower(string s)
{
    assert (s.length() > 0);
    string w="";
    char c;
    for (int i=0; i<s.length(); i++)
    {
        c = tolower(s[i]);
        if (c >= 'a' && c <= 'z')
            w += c;
    }
    return w;
    //                                                                                         
}

void get_word(char input[MAX_INPUT_LENGTH], string &output, int &pos)
{
    assert(pos >= 0 && pos < MAX_INPUT_LENGTH);
    char c;
    output = "";
    c = input[pos];
    while (c != ' ' && c != '\n' && c != '\0')
    {
        output += c;
        pos++;
        c = input [pos];
    }
    //                                                                      
}

void enter(char input[MAX_INPUT_LENGTH])
{
    assert(true);
    if (infile.is_open())
        infile.close();
    string w, filename = "";
    int i = 5; //                          
    while (input[i] != '\0' && input[i] != '\n')
    {
        i++;
        get_word(input, w, i);
        filename = filename + w + " ";
    }
    infile.open(filename);
    if (infile)
        cout << "opening of file is successful.\n";
    else
        cout << "ERROR: opening of file failed.\n";
    i = 0;
    infile >> w;
    while (infile)
    {
        words[i] = w;
        i++;
        infile >> w;
    }
    words[i+1] = "\0";
    //                                                                        
}

void content()
{
    assert(true);
    int i = 0;
    while (words[i].length() > 0)
    {
        cout << words[i] << endl;
        i++;
    }
    //                                                                             
}

void count_seq(char input[MAX_INPUT_LENGTH])
{
    assert(true);
    int no_words = 0, no_seqWords = 0, no_occ = 0,
    last_occ = -MAX_INPUT_LENGTH, no_occWords = 0, i = 5, j = 0;
    string w, seq[MAX_INPUT_LENGTH-6];
    while (input[i] != '\0' && input[i] != '\n')
    {
        i++;
        get_word(input, w, i);
        seq[j] = w;
        j++;
    }
    i = 0;
    no_seqWords = j;
    while (words[i] != "\0")
    {
        j = 0;
        while (seq[j] == only_lower(words[i+j]) && j < no_seqWords)
            j++;
        if (j == no_seqWords)
        {
            no_occ++;
            no_occWords += min(no_seqWords, i - last_occ);
            last_occ = i;
        }
        i++;
    }
    no_words = i;
    cout << "no_found: " << no_occ << "\ntotal words: " << no_words
    << "\n%seq/total: " << ((no_occWords*100)/max(1,no_words)) << endl;
    /*                                                                     
                                                   
                                                                       
    */
}

void find_seq(char input[MAX_INPUT_LENGTH])
{
    assert (true);
    int i = 5, j = 0, no_seqWords, no_occ = 0;
    string w, seq[MAX_INPUT_LENGTH-6];
    while (input[i] != '\0' && input[i] != '\n')
    {
        i++;
        get_word(input, w, i);
        seq[j] = w;
        j++;
    }
    no_seqWords = j;
    i = 0;
    while (words[i] != "\0")
    {
        j = 0;
        while (seq[j] == only_lower(words[i+j]) && j < no_seqWords)
            j++;
        if (j == no_seqWords)
        {
            cout << i << ", ";
            no_occ++;
        }
        i++;
    }
    cout << "#found: " << no_occ << endl;
    //                                                                                                   
}

void context(char input[MAX_INPUT_LENGTH])
{
    assert (true);
    int i = 8, j = 0, m, no_seqWords, no_occ = 0;
    string w, seq[MAX_INPUT_LENGTH-6];
    get_word(input, w, i);
    if (w[0] >= '0' && w[0] <= '9')
        m = stoi(w);
    while (input[i] != '\0' && input[i] != '\n')
    {
        i++;
        get_word(input, w, i);
        seq[j] = w;
        j++;
    }
    no_seqWords = j;
    i = 0;
    while (words[i] != "\0")
    {
        j = 0;
        while (seq[j] == only_lower(words[i+j]) && j < no_seqWords)
            j++;
        if (j == no_seqWords)
        {
            for (int c = max(i-m,0); c < i + j + m; c++)
                cout << words[c] << " ";
            cout << endl;
            no_occ++;
        }
        i++;
    }
    cout << "#found: " << no_occ << endl;
    //                                                 
}

void read_and_parse_input()
{
    assert(true);
    char input[MAX_INPUT_LENGTH];
    int pos = 0;
    string w;
    cin.getline(input, MAX_INPUT_LENGTH);
    get_word(input, w, pos);
    if (w == "enter")
        enter(input);
    if (w == "content")
        content();
    if (w == "stop")
        run = false;
    if (w == "count")
        count_seq(input);
    if (w == "where")
        find_seq(input);
    if (w == "context")
        context(input);
    //                                                                                     
}

int main()
{
    while (run)
        read_and_parse_input();
    return 0;
}

