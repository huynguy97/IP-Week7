#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//                          
//                          
//                                                                                

const int MAX_WORDS = 30000 ;
const int MAX_CHARS = 60 ;

bool open_text_file (ifstream& input_file)
{
    //              
    assert ( !input_file.is_open ());
    /*                
                                                               
    */
    cout<< "Please enter file name with the extension: ";
    char filename[80] ;
    cin.getline( filename, 80, '\n') ;
    input_file.open(filename) ;
    return input_file.is_open() ;
}

bool read_word (ifstream& input_file, char word[MAX_CHARS])
{
    //               
    assert (input_file.is_open ());
    /*                
                                                                      
    */
    input_file >> word;
    cout << word << endl;
    return input_file ;
}

/*
                                
                                                                        
 
                   
                                  
                    
                           
                  
                      
                        
                                
                                                                
     
                   
     
                    
 

              
 
                                         
                              
                
                
                     
                                  
                                                           
           
 

                                                                                                          
 
                    
                                        
                     
                                                                                                                                
                                                                                   
                                                    
                   
     
                      
                    
     
                              
     
                                     
                        
             
                    
     
                 
 

                                                                                            
 
                    
                                         
                      
                                                                                                     
                           
                                  
     
                                                       
     
 
*/

//                                             
//                                                                         
//                                                                     

//                                                                                                  
//                                                                                                        
//

void count_words (ifstream& input_file, char word [MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS])
{
    //              
    assert ( input_file.is_open ());
    /*                
                                                                                                     
    */
    int no = 0;
    char next [MAX_CHARS];
    while (read_word (input_file,next) && no < MAX_WORDS);
    //                                                                                       
}

int main()
{
    ifstream file;

    if (open_text_file (file))
    {
        cout << "The file has successfully opened" << endl;
        char words [MAX_WORDS][MAX_CHARS];
        int freqs [MAX_WORDS];
        //                                          
        //                                       
        int i = 0;
        while (read_word (file, words[i++]))
        {

        }

        return 0;
    }
    else
    {
        cout << "The file has not been opened" << endl;
        return 1;
    }
    return 0;
//                                                                                                     
//               
}

