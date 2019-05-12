#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;
//                                         
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;
enum Condition {enter = 1, content, stop} Cond;

bool open_text_file(char filename[80] )
{   //              
    assert (filename >0);
    ifstream infile;
//                                     
//                                       
    infile.open(  filename) ;
    return infile.is_open()   ;

}

int sequential_search (char data[MAX_WORDS][MAX_CHARS], int from, int to, char search_value[MAX_CHARS])
{
    //              
    assert(0<=from && 0 <= to);
    //                
    //                            
    //                                                         
    //                                                                  
    //                                                   
    //                                               
    if (from > to)
        return to + 1;
    int position = from ;
    while (position <= to && data [position] != search_value)
        position++;
    return position;
}

bool read_word (ifstream& infile, char word [MAX_CHARS])
{
    //               
    assert(infile.is_open());
    //                
    //                                                
    //                       
    infile >> word ;
    return infile;
}

bool tally_word (char word[MAX_CHARS],char words [MAX_WORDS][MAX_CHARS],
                 int freqs[MAX_WORDS], int& no)
{
    //               
    assert(no>=0 && no < MAX_WORDS);
    //                
    //                                                                       
    //                                                                 
    int pos = sequential_search(words, 0, no, word) ;
    if (pos < no)
    {
        freqs [pos]++ ;
        return true ;

    } else if (pos < MAX_WORDS)
    {
        strcpy(words[pos],word);
        freqs[pos]=1;
        no++;
        return true;
    }
    return false;

}

int count_words( ifstream& infile, char words [MAX_WORDS][MAX_CHARS],
                int freqs [MAX_WORDS])
{
    //              
    assert(infile.is_open());
    //              
    const int MAX_CHARS = 60;
    const int MAX_WORDS = 30000;
    int no = 0 ;
    char next [MAX_CHARS];
    while ( read_word(infile,next)&&
           tally_word(next,words,freqs,no)&&
           no<MAX_WORDS);
    return no;
}

void display_frequencies (char words [MAX_WORDS][MAX_CHARS],
                          int freqs [MAX_WORDS], int no)
{
    //               
    assert (no>=0 && no < MAX_WORDS);
    //                
    //                                                          
    for (int i = 0 ; i < no ; i++)
    {
        cout << words [i] << "\t" << freqs [i] << "\n" ;
    }
}

void display_frequencies2 (char words [MAX_WORDS][MAX_CHARS],
                          int freqs [MAX_WORDS], int no)
{
    //               
    assert (no>=0 && no < MAX_WORDS);
    //                
    //                                                          

    for (int i = 0 ; i < no ; i++)
    {
        cout << words [i] << "\t" << freqs [i] << "\n" ;
    }
}

void open_file(ifstream& myfile)
{
    if (myfile.is_open())
    {
        cout << "success" << endl;
    }else
    {
        cout << "Fail.." << endl;
    }
}

void open_content(ifstream& myfile)
{
    //             
    assert(myfile.is_open());
    string content;
    while(myfile.good())
    {
        getline(myfile, content);
        cout << content << endl;
    }

}

int main()
{
string command;
string command2;
char filename[MAX_CHARS];
cout << "Enter command1 and file's name: ";
cin>>command;
cin.ignore(1);
cin.getline(filename,MAX_CHARS);
ifstream myfile(filename);
open_file();
if (command =="enter")
{
    char words [MAX_WORDS][MAX_CHARS] ;
    int freqs [MAX_WORDS];

    int nr=count_words(myfile,words,freqs);
    cout<<nr;
    {
         cout << "\nEnter command2";
         cin >> command2;
         string word;
         char word2[40];
        getline(cin,word);
        cout<<word;

         if (command2 =="count")
        {

            display_frequencies(words,freqs,nr);
        }
        else if (command2 =="where")
        {
            return true;
        }
        else if (command2 =="context")
        {
            return true;
        }
    }
}
else if (command =="content")
{
    open_content(myfile);
}
else if (command =="stop")
    cout<<"terminate the program";
    return false;
}

