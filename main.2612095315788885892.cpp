#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;
//                      
//                          
//                                        
//                                                                                                                  
//                                                                                      
//                                                                                           

const int MAX_WORDS = 30000 ;
const int MAX_CHARS = 60 ;

bool open_text_file (ifstream& infile)
{
    //                
    assert(!infile.is_open()) ;
    //                 
    //                                                 
    cout << "Please enter file name: " ;
    char filename [80] ;
    cin.getline(filename, 80, '\n') ;
    infile.open(filename) ;
    return infile.is_open() ;
}

bool read_word (ifstream& infile, string& word)
{
    //                
    assert(infile.is_open()) ;
    //                 
    //                                                                               
    infile >> word ;
    return infile ;
}

int sequential_search(string data[], int from, int to, string search_value)
{
    //                
    assert ( 0 <= from && 0 <= to ) ;
    //                 
    //                                    
    //                                                                
    //                      
    //                                                               
    //                                          
    //                                  
    if (from > to)
    {
        return to + 1 ;
    }
    int position = from ;
    while (position <= to && data [position] != search_value)
    {
        position++ ;
    }
    return position ;
}

bool tally_word (string word, string words [MAX_WORDS], int freqs [MAX_WORDS], int& no)
{
    //                
    assert(no >= 0 && no < MAX_WORDS) ;
    //                 
    //                            
    //                                                               
    //                                                                
    int pos = sequential_search(words, 0, no, word) ;
    if (pos <= no)
    {
        freqs [pos]++ ;
        return true ;
    }
    else if (pos < MAX_WORDS)
    {
        words [pos] = word ;
        freqs [pos] = 1 ;
        no++ ;
        return true ;
    }
    return false ;
}

int count_words (ifstream& infile, string words [MAX_WORDS], int freqs [MAX_WORDS])
{
    //                
    assert(infile.is_open()) ;
    //                 
    //                                                                               
    int no = 0 ;
    string next ;
    //                         
    //                                    
    while (read_word(infile, next) && tally_word(next, words, freqs, no) && no < MAX_WORDS)
    {
        ;
    }
    return no ;
}

void display_frequencies (string words [MAX_WORDS], int freqs [MAX_WORDS], int no)
{
    //                
    assert(no >= 0 && no < MAX_WORDS) ;
    //                 
    //                                                                   
    for ( int i = 1 ; i <= no ; i++)
    {
        string word_to_print = words[i] ;
        if (word_to_print.length() <= 7)
        {
            cout << words[i] << "\t\t\t" << freqs [i] << "\n" ;
        }
        else if (word_to_print.length() <= 16)
        {
            cout << words[i] << "\t\t" << freqs [i] << "\n" ;
        }
        else
        {
            cout << words[i] << "\t" << freqs [i] << "\n" ;
        }
    }
}

void display_all_words (ifstream& infile)
{
//            
assert(infile.is_open());
//                                                                                            
    string word ;
    infile >> word ;
    cout << word << "\n" ;
}

/*                         
 
                                   
                                         
                         
 */

void enter_command(ifstream& infile, int nr)
{
    //            
    assert(true);
    //             
    //                                                                                                                      
    open_text_file(infile) ;
    if (infile.is_open())
    {
      cout << nr;
    }
    else
    {
        cout << "The file could not be opened.";
    }
}

/*                                                                                    
 
                
                
                   
                       

                                    
             
                               
                                                            
         
                           
                     
         
        
     
 

                                
                     
                       
     
                                          
                   
     
                                               
 */

int main()
{
    ifstream file ;

    string instruction [MAX_WORDS] ;
    cout << "Enter the command: " ;
    int counter = 0;
    while (cin)
        {
       cin >> instruction [counter];
       counter++;
    }

    enum Choice {"enter", "content", "stop"} ;
    Choice entered_choice = instruction [0] ;

    if (open_text_file(file))
    {
        string words [MAX_WORDS] ;
        int freqs [MAX_WORDS] ;
        int nr = count_words(file, words, freqs) ;
        switch (entered_choice)
    {
        case "enter" : enter_command(infile, words, freqs) ; break ;
        case "content" : display_all_words(infile) ; break ;
        case "stop" : file.close() ; return 0 ;
        //              
    }
        display_frequencies(words, freqs, nr) ;
        file.close() ;
        return 0 ;
    }
    return 1 ;

}

