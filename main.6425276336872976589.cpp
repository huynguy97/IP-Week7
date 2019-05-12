#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;
/*
            
                            
                       
*/

const int MAX_WORDS = 30000;
const int MAX_CHARS = 30;

int nr_of_words;

bool open_text_file(ifstream& infile)
{
    //              
    assert(!infile.is_open());
    /*                                                                                                     
                            
    */
    string command;
    char filename[80];
    cout << "Please enter a command:\n";
    cin >> command;
    cin.ignore(1);
    if(command == "enter"){
        cin.getline(filename, 80, '\n');
        cout << filename;
        infile.open(filename);
        return infile.is_open();
    }else {
        cout << "This command could not be executed...";
    }
}

bool read_word(ifstream& infile, char word [MAX_CHARS])
{
    //               
    assert(infile.is_open());
    /*                                                            
    */
    infile >> word;
    return static_cast<bool>(infile);
}

int sequential_search(char data[MAX_WORDS][MAX_CHARS], int from, int to, char search_value[])
{
//               
    assert(0 <= from && 0 <= to);
    /*               
                       
                                                                     
                                                                                  
    */
    if (from > to)
        return to + 1;
    int position = from;
    while(position <= to && strcmp(data[position], search_value) != 0)
        position++;
    return position;
}

bool tally_word(char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int& no)
{
    //               
    assert(true);
    /*               
                           
                                            
                        
                                  
                                           
    */
    int pos = sequential_search(words, 0, no, word);
    if(pos < no){
        freqs[pos]++;
        return true;
    }else if (pos < MAX_WORDS){
        strcpy(words[pos], word);
        freqs[pos] = 1;
        no++;
        return true;
    }
    return false;
}

void make_words_and_freq_arrays(ifstream& infile, char words_freqs[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS])
{
    //              
    assert(infile.is_open());
    /*               
                              
                                                  
                                                                                                      
    */
    int no = 0;
    char next[MAX_CHARS];
    while(read_word(infile, next) && tally_word(next, words_freqs, freqs, no) && no < MAX_WORDS)
        ;
}

int count_words(ifstream& infile, char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS])
{
    //              
    assert(infile.is_open());
    /*                                                                                              
    */
    int no = 0;
    char next[MAX_CHARS];
    while(read_word(infile, next) && no < MAX_WORDS){
        strcpy(words[no], next);
        no++;
    }
    return no;
}

void content(char words[MAX_WORDS][MAX_CHARS])
{
    //              
    assert(true);
    /*                                                     
    */
    for(int word_index = 0; word_index < nr_of_words; word_index++){
                    cout << words[word_index] << "\n";
            }
}

void count_command(char words[MAX_WORDS][MAX_CHARS])
{
    //              
    assert(true);
    /*                                                                                                               
                                                                                              
    */
    char word[MAX_CHARS];
    int nr_occur = 0;
    cin.getline(word, MAX_CHARS, '\n');
    for(int i = 0; i < nr_of_words; i++){
        if(words[i] == word)
            nr_occur++;
    }
    cout << "The word " << word << " occurs " << nr_occur << " times.";
    cout << "\nThe total number of words is " << nr_of_words;
    cout << "\nThe percentage of occurences is " << (nr_occur/nr_of_words)*100 << "%.";
}

void where(char words_freq[MAX_WORDS][MAX_CHARS])
{
    //              
    assert(true);
    /*                                                                                                                 
    */
    char word[MAX_CHARS];
    int nr_occur = 0;
    cin.getline(word, MAX_CHARS, '\n');
    cout << "The index positions are: \n";
    for(int i = 0; i < nr_of_words; i++){
        if(words_freq[i] == word){
            nr_occur++;
            cout << i << ", ";
        }
    }
    cout << "\nThe number of found occurences is: " << nr_occur;
}

void context_2(char words[MAX_WORDS][MAX_CHARS])
{
    //              
    assert(true);
    /*                                                                                                      
                                                               
    */
    char word[MAX_CHARS];
    int nr_occur = 0;
    cin.getline(word, MAX_CHARS, '\n');
    for(int i = 0; i < nr_of_words; i++){
        if(words[i] == word){
            nr_occur++;
            cout << words[i-2] << " " << words[i-1] << " " << words[i] << " " << words[i+1] << " " << words[i+2];
        }
        cout << "\nThe number of found occurences is: " << nr_occur;
}
}

int main()
{
    /*                                                                                                        
                                                            
    */
    cout << "Hello world!" << endl;
    ifstream infile;
    char words[MAX_WORDS][MAX_CHARS];
    char words_freq[MAX_WORDS][MAX_CHARS];
    int freqs[MAX_WORDS];
    if(open_text_file(infile)){
        cout << "The file was opened succesfully!";
        nr_of_words = count_words(infile, words, freqs);
        cout << "\nThis file contains " << nr_of_words << " words.\n";
        }else {
            cout << "The file could not be opened...";
        }
    make_words_and_freq_arrays(infile, words_freq, freqs);
    cout << "Please enter a command:\n";
    string command;
    cin >> command;
    cin.ignore(1);
    while(command != "stop"){
        if (command == "content")
            content(words);
        else if (command == "count")
                count_command(words);
        else if (command == "where")
                where(words_freq);
        else if (command == "context")
                context_2(words);
        cout << "\nPlease enter a command:\n";
        cin >> command;
        cin.ignore(1);
    }
    return 0;
}

