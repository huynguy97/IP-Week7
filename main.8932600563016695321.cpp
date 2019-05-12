#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

//                         
//                           

using namespace std;

const int MAX_WORDS = 300;

bool enter_filename (ifstream& infile)
{
    //               
    assert (!infile.is_open());
    //                
    //                                   
    string filename;
    //                  
    getline(cin, filename);
    cout << filename << "!";
    infile.open(filename.c_str());
    return infile.is_open();
}

bool read_words (ifstream& infile, string& words)
{
    //              
    assert (infile.is_open());
    //              
    //                                                       
    infile >> words;
    if (infile)
    {
        cout << "read";
        return infile;
    }
    else
    {
        cout << "Error";
        return infile;
    }
    return infile;
}

int sequential_search(string word [MAX_WORDS], int from, int to, string search_word)
{
    //             
    //         
    //              
    //                                                                      
    if (from > to)
        return to+1;
    int i = from;
    while (i <= to && word [i] != search_word)
        i++;
    return i;
}

bool tally_words (string words, string word [MAX_WORDS], int freqs [MAX_WORDS], int& word_nr)
{
    //             
    //        
    //              
    //                                                                                       
    //                                                                        
    int position = sequential_search(word, 0, word_nr, words);
    if (position < word_nr)
    {
        freqs[position]++;
        return true;
    }
    else if (position < MAX_WORDS)
    {
        word[position] = words;
        freqs [position] = 1;
        word_nr++;
        return true;
    }
    return false;

}

int count_words(ifstream& infile, string word [MAX_WORDS], int freqs[MAX_WORDS])
{
    //             
    assert(infile.is_open());
    //              
    //                                                                                 
    int word_nr = 0;
    string words;
    while (read_words(infile, words))
        tally_words(words, word, freqs, word_nr);
    return word_nr;
}

void display_frequencies (string word[MAX_WORDS], int freqs [MAX_WORDS], int nr)
{
    //             
    assert(nr >= 0 && nr < MAX_WORDS);
    //              
    //                                                                                     
    for (int i =0; i <nr; i++)
    {
        cout << word [i] << "\t" << freqs [i] << "\n";
    }
}

void enter_command()
{
    //             
    assert(true);
    //              
    //                                   
    string command;
    cin >> command;
    if (command == "enter")
        enter_filename(filename1);
    else if (command == "content")
        while(read_words(infile, words))
            cout << words;
    else if (command == "stop")
    }
         inputfile.close();
         cout << "EINDE";
    }
    else if (command == "count")
        display_frequencies(word, freqs, nr);
    else if (command == "where")
        while (read_words(infile, words))
            tally_words(words, word, freqs, word_nr);
    else if (command == "context")

    else cout << "ERROR!";
}

int main()
{
    ifstream filename1;
    enter_command();
    /*                             
     
                                
                              
                                                     
                   
                                             
     */
}

