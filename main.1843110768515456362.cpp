#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000 ;

bool open_text_file ( ifstream& infile)
{
    cout << "Please enter file name: " ;
    char filename [80] ;
    cin.getline(filename, 80, '\n') ;
    infile.open(filename) ;
    return infile.is_open() ;
}

bool read_word ( ifstream& infile, char word [MAX_CHARS] )
{
    infile >> word ;
    return infile ;
}

int sequential_search ( char data [MAX_WORDS][MAX_CHARS], int from, int to, char search_value [MAX_CHARS] )
{//               
    assert ( 0 <= from && 0 <= to ) ;
    //                
    //                                  
    //                                                             
    //
    //                   
    //           
    //                                                    
    //
    //                                      
    //
    //                                 
    if ( from > to )return to + 1 ;
    int position = from ;
    while (position < to && strcmp(data[position], search_value) != 0) position++ ;
    return position ;
}

void display_frequencies( char words [MAX_WORDS][MAX_CHARS],int freqs [MAX_WORDS], int no ){

    for ( int i = 0; i < no ; i++ ){
        cout << words [i] << "\t" << freqs [i] << "\n" ;
    }
}

bool tally_word (char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS],int freqs [MAX_WORDS], int& no )
{
    int pos = sequential_search( words, 0, no, word ) ;
    if ( pos < no ){
        freqs [pos]++ ;
        return true ;
    } else if ( pos < MAX_WORDS ){
        strcpy ( words [pos], word ) ;
        freqs [pos] = 1 ;
        no++ ;
        return true ;
    }
    return false ;
}

void show_content(ifstream& infile, char words [MAX_WORDS][MAX_CHARS]){
    char word [MAX_CHARS];
    int i = 0;
    while(infile){
        read_word(infile, word);
        strcpy(words[i], word);
        i++;
    }
    for(int y = 0; y<=i; y++){
        cout << words[y] << endl;
    }
    cout << "\n" << "End of Content." << endl;

}

int count_words ( ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS] )
{
    assert(infile);
    int no = 0 ;
    char next [MAX_CHARS];
    while ( read_word (infile, next) && tally_word (next, words, freqs, no) &&  no < MAX_WORDS);
    return no ;
}

//                                                                    
void count_word_seq(ifstream& infile, char words [MAX_WORDS][MAX_CHARS], char word[MAX_CHARS]){
    int i = 0;
    while(infile){
        read_word(infile, word);
        strcpy(words[i], word);
        i++;
    }
    int occurences = 0;
    for(int y = 0; y < MAX_WORDS; y++){
        if(strcmp(words[y], word) == 0){
            occurences++;
        }
    }

    cout << "Sequence " << word << " occurs " << occurences << " times in " << i << " words, or " << (occurences/i)*100 << " percent." << endl;

}

void show_indexes( int occurences, int indexes[MAX_WORDS]){
    for(int x = 1; x<occurences;x++){
        cout << indexes[x] << "\t";
    }
}

void find_indexes_of_seq(ifstream& infile, char words [MAX_WORDS][MAX_CHARS], char word[MAX_CHARS]){
    int i = 0;
    int indexes[MAX_WORDS];
    while(infile){
        read_word(infile, word);
        strcpy(words[i], word);
        i++;
    }
    int occurences = 0;
    for(int y = 0; y < MAX_WORDS; y++){
        if(strcmp(words[y], word) == 0){
            occurences++;
            indexes[occurences] = y;
        }
    }
    cout << "Sequence " << word << " occurs " << occurences << " times" << " on indexes: " << endl;
    show_indexes(occurences, indexes);
}

int UI(ifstream& infile, char words [MAX_WORDS][MAX_CHARS]){
    cout << "Enter command. 0 for file reading and display(content), 1 for file word tally and display(tally), 2 to count word sequence occurence, 3 to find all indexes of a sequence, 4 for context of a word and 5 for program exit(stop)." << endl;
    int y = -1;
    cin >> y;
    while(y<0 || y>4){
        cout << y << endl;
        cout << "Incorrect command. Enter int between 0 and 4." << endl;
        cin >> y;
    }
    switch(y){
        case 0: if(open_text_file(infile)){
                    show_content(infile, words);
                    infile.close();
                }
                break;
        case 1: if (open_text_file (infile)){
                    int freqs [MAX_WORDS] ;
                    int nr = count_words(infile, words, freqs) ;
                    display_frequencies( words, freqs, nr) ;
                    infile.close () ;
                }
                break;
        case 2: if (open_text_file (infile)){
                    cout << "Enter word to find occurences of: " << endl;
                    char word [MAX_CHARS];
                    cin >> word;
                    count_word_seq(infile, words, word);
                    infile.close();
                }
                break;
        case 3: if (open_text_file (infile)){
                    cout << "Enter sequence to find occurences of: " << endl;
                    char word [MAX_CHARS];
                    cin >> word;
                    find_indexes_of_seq(infile, words, word);
                    infile.close();
                }
                break;
        case 5: return 0;
                break;

    }

}

int main()
{
    ifstream infile;
    char words [MAX_WORDS][MAX_CHARS] ;
    UI(infile, words);
}

