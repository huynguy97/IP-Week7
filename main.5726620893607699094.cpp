/*
                             
*/

#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int MAX_INPUT = 80;
const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

void instruction_message(){
    //              
    assert(true);
    //             
    //                                       
    cout << "Hello, world!\n" << endl;
}

bool read_word(ifstream& infile, char word[MAX_CHARS]){
    //             
    assert(infile.is_open());
    //              
    infile >> word;
    return infile;
}

int sequential_search (char data[MAX_WORDS][MAX_CHARS], int from,
                       int to, char search_value[MAX_CHARS]){
    //               
    assert (0 <= from && 0 <= to);
    //              
    //
    if ( from > to )
        return to + 1;
    int position = from;
    while (position <= to && data [ position ] != search_value)
        position++;
    return position;
}

bool tally_word(char word[MAX_CHARS], char words[MAX_WORDS][MAX_CHARS],
        int freqs [MAX_WORDS], int& no){
    //             
    assert(no >= 0 && no < MAX_WORDS);
    //              
    int pos = sequential_search(words, 0, no, word ) ;
    if ( pos < no ){
        freqs [pos]++ ;
        return true ;
    }
    else if (pos < MAX_WORDS){
        strcpy (words [pos], word ) ;
        freqs[pos] += 1;
        no++;
        return true;
    }
    return false;
}

int count_words (ifstream& infile, char words[MAX_WORDS][MAX_CHARS],
        int freqs[MAX_WORDS]){
    //              
    assert(infile.is_open());
    //                                                    
    int no = 0;
    char next[MAX_CHARS];
    while( read_word(infile, next) &&
           tally_word(next, words, freqs, no) &&
           no < MAX_WORDS);
    return no;
}

void display_frequencies(char words [MAX_WORDS][MAX_CHARS],
        int freqs [MAX_WORDS], int no ){
    //              
    //               
    for ( int i = 0; i < no ; i++ ){
        cout << words [i] << "\t"
             << freqs [i] << "\n" ;
    }
}

void commands(string& codeword, char userinput[MAX_INPUT]){
    //             
    assert(true);
    //              
    cout << "Enter a command: ";
    cin >> codeword;
    cin.ignore();
    cin.getline ( userinput, MAX_INPUT, '\n');
}

int do_enter(char userinput[MAX_INPUT], char words[MAX_WORDS][MAX_CHARS],
           int freqs[MAX_WORDS]){
    //              
    assert(true);
    //              
    //                            
    for (int i = 0; i < MAX_INPUT; i++){
        if (userinput[i] == '\n'){
            userinput[i] == '\0';
        }
    }
    string filename(userinput);
    ifstream file (filename.c_str());

    int words_in_file = count_words(file,words,freqs);
    cout << "There are: " << words_in_file << " words in this file." << endl;

    return words_in_file;
}

void do_count(char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int no){
    //             
    assert(no >= 0 && no < MAX_WORDS);
    //               
    display_frequencies(words, freqs, no);
}

int main(){
    char words[MAX_WORDS][MAX_CHARS];
    int freqs[MAX_WORDS];
    char userinput[MAX_INPUT];
    string codeword;
    bool activated = true;
    int no = 0;

    //        
    instruction_message();

    while(activated){
        //                                         
        commands(codeword, userinput);
        //                                          
        if (codeword == "enter"){
            no = do_enter(userinput, words, freqs);
        }
        else if (codeword == "content"){
        }
        else if (codeword == "count"){
            do_count(words, freqs, no);
        }
        else if (codeword == "where"){
            cout << "Where there was not enough time." << endl;
        }
        else if (codeword == "context"){

        }
        else if (codeword == "q" || codeword == "quit" || codeword == "Q"){
            activated = false;
        }
        else {
            cout << "Code word is not recognized, please try again." << endl;
        }
    }
    cout << "Program terminated." << endl;
    return 0;
}

