//                      
//                       
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace std;

char str[10000], strin[100000];
const int max_words = 10000;
const int max_chars = 50000;
char usertext[80];
char words [max_words][max_chars];
int freqs [max_words];
int no=0;

bool openfile_function (ifstream& infile)
{
            cout << "filename  ";
            string file_name;
            cin.getline (str ,100, '\n');
            infile.open (str);
            return  infile.is_open();
}
bool read_word ( ifstream& infile, char word[max_chars])
{
    infile >> word;
    return static_cast<bool>(infile) ;
}

int sequential_search (char data[][max_chars], int from, int to, char search_value[])
{
    if (from>to)
        return no+1;
    int position = from;

    while(position <= to && strcmp ( data [position], search_value) != 0)
        position++;
    return position;
}

bool tally_word (char word [max_chars],char words [max_words][max_chars], int freqs [max_words], int& no)
{
    int pos = sequential_search (words, 0, no, word);
    if (pos < no)
    {
        freqs [pos]++;
        return true;
    }
    else if (pos < max_words)
    {
        strcpy(words[pos],word);
        freqs [pos]=1;
        no++;
        return true ;
    }
    return false;
}

int count_words (ifstream& infile, char words [max_words][max_chars], int freqs [max_words])
{
int no = 0;
char next [max_chars];
while (read_word (infile, next) && tally_word (next, words, freqs, no) && no < max_words);
return no;
}

void display_frequencies(char words[max_words][max_chars],int freqs[max_words],int no)
{
    for( int i=0;i<no;i++)
    {
        cout << words [i] << "\t" << freqs [i] << "\n";
    }
}

int main()
{

bool a = true;
while(a)
    {
    cout << "please give a command" << endl;
    cin.getline(usertext, 80);
    string input(usertext);

        if (input.find("enter ")==0)
        {
            ifstream file;
            if (openfile_function(file))
            {

                int nr = count_words (file, words, freqs);
                display_frequencies (words, freqs, nr);
                file.close();
                return 0;
            }
            else return 1;

/*                     
                  
                                 
             
                                     
                            
             
                      
 */       }
        else if (input == "content")
        {
 //                              
        }
        else if (input == "stop")
        {
            a = false;

        }
        else if (input.find("count ")== 0)
        {
   //                             
        }
        else if (input.find("where ")== 0)
        {
     //                        
        }
        else if (input.find("context ")== 0)
        {
       //                        
        }
        else
            cout << "this is not a correct command" ;
    }
cout << "program is succesfully terminated";
}

