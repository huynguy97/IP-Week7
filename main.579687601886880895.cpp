#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX_CHARS = 50;
const int MAX_WORDS = 50000;
int position = 0 ;

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
//     
// 

bool open_text_file (ifstream& infile) {
    cout << "Please enter file name: ";
    char filename [80] ;
    cin.getline(filename, 80, '\n');
    infile.open(filename);
    return infile.is_open();
}

bool read_word (ifstream& infile,char word [MAX_CHARS]) {
    assert (infile.is_open());

    infile >> word;
    return infile;
}

int sequential_search ( int data [], int from, int to, int search_value ) {//               
    assert ( 0 <= from && 0 <= to ) ;
    //                
    //                                 
    //                                                             
    //                    
    //                                                                
    //                                       
    //                                  
    if ( from > to )
    return to + 1 ;
    int pos = from ;
    while (pos <= to && data [ pos ] != search_value) {
    pos++ ;
    }
    char words = data [];
    return pos ;
}

bool tally_word (char word [MAX_CHARS],char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int& no) {
    assert (no >= 0 && no < MAX_WORDS);
    int pos = sequential_search(words, 0, no, word);
    if (pos < no){
        freqs [pos]++;
    return true;
    } else if (pos < MAX_WORDS) {
        strcpy (words [pos], word);
        freqs [pos] = 1;
        no++;
        return true;
    }
    return false;
}

;int count_words (ifstream& infile,char words [MAX_WORDS][MAX_CHARS],int freqs [MAX_WORDS] ) {
    assert(infile.is_open());

    int no = 0;
    char next [MAX_CHARS];
    while(read_word (infile, next) && tally_word (next, words, freqs, no) && no < MAX_WORDS);
    return no;
}

void display_frequencies(char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int no) {
    assert ( no >= 0 && no < MAX_WORDS);
    for ( int i = 0; i < no ; i++) {
            cout << words [i] << "\t" << freqs [i] << "\n" ;
    }
}

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
//                                                     
//                   
//     
//
//                            
//                     
// 

int main() {
    assert(infile.is_open())

    ifstream file;
    if (open_text_file (file)) {
        char words [MAX_WORDS][MAX_CHARS];
        int freqs [MAX_WORDS];
        int nr = count_words (file, words, freqs);
        display_frequencies (words, freqs, nr);
        file.close();
        return 0;
    }
    else return 1 ;

//                
//                     
//                         
}

