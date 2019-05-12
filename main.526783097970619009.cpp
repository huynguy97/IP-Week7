#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

const int MAX_FILENAME_SIZE = 80;
const int MAX_WORDS = 30000;
const int MAX_CHARS = 60;

char words [MAX_WORDS][MAX_CHARS];
char wordlist [MAX_WORDS][MAX_CHARS];
int freqs [MAX_WORDS];

//     
//                        
//                      

bool open_text_file(ifstream& infile)
{
    //                        
    //            
    assert(!infile.is_open());
    //             
    //                                               

    //                                   
    char filename [MAX_FILENAME_SIZE];
    cin.ignore();
    cin.getline(filename, MAX_FILENAME_SIZE, '\n');
    cout << "filename: " << filename << endl;
    infile.open(filename);

    if (infile.is_open()){
        cout << "File opend succesfully!" << endl;
    }
    else{
        cout << "Erreur: file is not open! Try again!";
    }
    return infile.is_open();
}

int read_words(ifstream& infile, char words [MAX_WORDS][MAX_CHARS])
{
    //            
    assert(infile.is_open());
    //             
    //                                           

    int counter = 0;
    while (infile && counter < MAX_WORDS){
        infile >> words[counter];
        //                                                             
        counter++;
    }
    cout << "Number of words read in: " << counter << endl;
    return counter-1;
}

int check_if_inside(char word[MAX_CHARS], char wordlist[MAX_WORDS][MAX_CHARS], int wordlist_len)
{
    //            
    assert(wordlist_len >=0);
    //             
    //                                                       

    for(int i=0; i<= wordlist_len; i++){
        //                                                      
        if(strcmp(wordlist[i],word)==0){
            return i;
        }
    }

    return -1;
}

int count_words(char words [MAX_WORDS][MAX_CHARS], char wordlist [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int no)
{
    //            
    assert(no >= 0);
    //             
    //                             

    int wordlist_len = 0;
    int x;

    for(int j =0; j<MAX_WORDS; j++){
        freqs[j]=1;
    }

    for(int i=0; i<= no; i++){
        x = check_if_inside(words[i], wordlist, wordlist_len);
        //                           
        if(x >=0){
            freqs[x]++;

        }
        else{
            wordlist_len++;
            strcpy(wordlist[wordlist_len], words[i]);
            //                                         
            //                                  
        }
        //                                                                            
    }

    return wordlist_len;
}

void print_words(char wordlist [MAX_WORDS][MAX_CHARS], int no_words)
{
    //            
    assert(no_words >= 0);
    //             
    //                          

    for(int i=0; i<= no_words; i++){
        cout << wordlist[i] << endl;
    }
}

void word_occ_counter(char wordlist [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int no_words, int no_wordlist)
{
    //            
    assert(no_words >= 0 && no_wordlist >= 0);
    //             
    //                                   

    char word[MAX_CHARS];
    int x;

    while (cin){
        cin >> word;
        x = check_if_inside(word, wordlist, no_wordlist);
        cout << "Word: " << word << "\tFreq: " << freqs[x] << "\tTotalwords: " << no_words << "\tPercentage: " << (float(freqs[x])/float(no_words))*100.0 << "%" << endl;
    }
}

int main()
{
    ifstream input_file;
    string command;

    int no_words = 0;
    int no_wordlist = 0;

    while(true){
        cout << "\nPossible commands: enter, content, count, where, context, stop." << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == "enter"){
            open_text_file(input_file);
            no_words = read_words(input_file, words);
            no_wordlist = count_words(words, wordlist, freqs, no_words);
        }
        else if(command == "content"){
            print_words(words, no_words);
        }
        else if(command == "count"){
            word_occ_counter(wordlist, freqs, no_words, no_wordlist);
        }
        else if(command == "where"){
            cout << "Sorry, not implemented yet :(" << endl;
        }
        else if(command == "context"){
            cout << "Sorry, not implemented yet :(" << endl;
        }
        else if(command == "stop"){
            cout << "Bye." << endl;
            return 0;
        }
        else{
            cout << "Invalid command, try again!" << endl;
        }

    }

    return 0;
}

