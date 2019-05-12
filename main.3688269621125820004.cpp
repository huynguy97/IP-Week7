//                                       
//              
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

int sequential_search ( string words[MAX_WORDS], int from, int to, string search_word )
{//              
    assert(0 <= from && 0 <= to);
    //               
    //                                  
    //                                                               
    //                   
    //                                                                
    //                                        
    //                                 
    if ( from > to )
        return to + 1 ;
    int  position = from ;
    while (position <= to && (words [position] != search_word) )
    {
        position++;
    }
    return position;
}
bool enter_file(ifstream& infile)
{
    //              
    assert(infile);
    //                                                            
    string infile_name;
    cin.clear();
    bool ask_for_input = true;

    while(ask_for_input)
    {
        cout << "Enter an name for the input file (with extension)..."<<endl;
        getline(cin,infile_name);
        cin.clear();
        infile.open( infile_name.c_str() );
        if (infile.is_open())
        {
            cout << "The file has been opened successful!"<< endl;
            ask_for_input = false;
        }
        else
        {
            cout << "The file can not be opened!"<< endl;
            ask_for_input = true;
        }
    }
    return infile.is_open();
}

int store_words (ifstream& infile, string words [MAX_WORDS], int freqs [MAX_WORDS])
{
    //              
    assert(infile && MAX_WORDS > 0);
    //                                                        
    int word_count = 0;
    string word;
    int pos;

    while(infile)
    {
        infile >> word;
        cout << word << endl;
        pos = sequential_search(words, 0, word_count, word);
        if (pos == (word_count + 1) )
        {
            words[word_count]= word;
            freqs [word_count] = 1;
            word_count++;
        }
        else
        {
            freqs[pos]++;
        }
    }

    if( word_count > MAX_WORDS)
    {
        cout << "Amount of storage exceeded..." << endl;
        return -1;

    }
    else
    {
        cout << "Amount of different words stored: " << word_count << endl;
        return word_count;
    }
}

void display_all_words(string words [MAX_WORDS], int freqs [MAX_WORDS], int word_count)
{
    //              
    assert(MAX_WORDS > 0);
    //                                                          
    for(int i = 0; i < word_count ; i++)
    {
        cout << words[i] << " " << freqs[i] << endl;
    }

}

int main()
{
    ifstream infile;
    string input;

    string words [MAX_WORDS];
    int freqs [MAX_WORDS];
    int total_words = -1;

    bool ask_for_input = true;

    while(ask_for_input)
    {
        cout << "Enter a command..."<<endl;
        cin >> input;

        if(input == "enter")
        {
            if(enter_file(infile))
                total_words = store_words(infile, words, freqs);
        }
        else if (input == "content")
        {
            if(total_words == -1)
                cout << "There are no words stored..."<<endl;
            else
                display_all_words(words,freqs,total_words);
        }
        else if (input == "stop")
            ask_for_input = false;
        else
            cout << "The command is invalid..." << endl;

    }
}

