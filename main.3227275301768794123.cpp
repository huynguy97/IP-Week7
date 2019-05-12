#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

//                                                     
//                                                                                               
//                                                     
using namespace std;

const int MAX_WORDS=50000;
const int MAX_CHARS=50;
char words[MAX_WORDS][MAX_CHARS];

bool open_file(ifstream& infile)
{
    //             
    assert(!infile.is_open());
    //                                                     
    cout<<"Enter file name"<<endl;
    char filename[100];
    cin.getline(filename,100,'\n');
    infile.open(filename);
    return infile.is_open();
}

void content(ifstream& infile)
{   //             
    assert(infile.is_open());
    //                                             

    char word[MAX_WORDS] ;
    infile>>word;
    cout <<word;
    while(infile)
    {

        cout<<","<<word;
        infile>>word;

    }

}

int sequential_search (char data[MAX_WORDS][MAX_CHARS], int  from, int to, char search_value[MAX_CHARS])
{
    //            
    assert(0<=from&&0<=to);
    //                                                                                      
    if(from>to)
        return to++;
    int position = from;
    while(position <= to&&data [position] != search_value)
        position++;
    return position;

}

bool read_word(ifstream& infile, char word[MAX_CHARS])
{
    //            
    assert(infile.is_open());
    //                                                                                        
    infile>>word;
    return static_cast<bool>(infile);
}

bool tally_word(char word[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS],int freqs[MAX_WORDS], int& no)
{
    //            
    assert(  no   >= 0 && no < MAX_WORDS);
    //                                                                                                                                                                   
    int pos = sequential_search(words, 0, no, word);
    if(pos<no)
    {   freqs[pos]++;
        return true;
    }
    else if (pos < MAX_WORDS)
    {   strcpy (words[pos], word);
        freqs[pos] = 1;
        no++;
        return true;
    }
    return false;

}

int count_words (ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS])
{
    //            
    assert(infile.is_open());
    //                                                                                         
    int no=0;
    char next [MAX_CHARS];
    while(read_word(infile, next)&& tally_word(next, words, freqs, no)&& no<MAX_WORDS);
    return no;

}

void display_frequencies(char words[MAX_WORDS][MAX_CHARS],int freqs[MAX_WORDS], int no)
{
    //             
    assert(  no >=0 && no   <  MAX_WORDS);
    //                                                                              
    for (int i=0; i<no; i++)
    {
        cout<<words [i]<<"\t"<<freqs[i]<<"\n";
    }

}

int main()
{
    cout<<"What would you like to do with the text ?"<<endl;
    cout<<"If you would like to see a content, press 0"<<endl;
    cout<<"If you want to see counted words, press 1"<<endl;
    int a;
    cin>>a;
    ifstream file;
    if (a=0)
    {
        if(open_file(file))
        {
            content(file);
            file.close();
        }
    }
    else
    {

        if(open_file(file))
        {

            int freqs[MAX_WORDS];
            int nr = count_words(file,words,freqs);
            display_frequencies(words,freqs,nr);
            file.close();
            return 0;

        }
        else return 1;
    }

        return 0;
}

