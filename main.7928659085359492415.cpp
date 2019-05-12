#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <bitset>
#include <sstream>
#include <stdlib.h>

using namespace std;

//                             
//                          

bool cmp_str(const char str1[], const char str2[]) //                                                                                
{
    int k = 0 ;
    while (str1[k] == str2[k] && str1[k] != 0) //                                                                                                                                                                                                                                      
        k++ ;
    if(str1[k] == str2[k])
    {
        return true ;
    }
    return false ; //                                    
}

//   
bool enter_filename (ifstream& infile, char words [30000][60], int& counter)
{
    assert(infile && !infile.is_open()); //                                        
    //                                                                                   
    char filename [80]; //                                                       
    cout << "Please enter a filename. \n" ;
    cin.getline(filename, 99999) ; //                                                                                          
    infile.open(filename) ;
    if (!infile.is_open()) //                             
    {
        cout << "Your file couldn't be opened." ;
        return infile.is_open() ; //          
    }
    else
    {
        //                       
        //               
        counter = 0 ;
        while (infile)
        {
            infile >> words[counter] ; //                                       
            counter++ ;
        }
        //                                                          
        cout << "Your file was successfully opened, read and stored in an array. " << counter << " words are read. \n" ;
        return infile.is_open() ; //         
    }
}

//   
void content(char words [30000][60], int counter)
{
    for (int j = 0; j < counter ; j++)
    {
        cout << words[j] << " ";
    }
    cout << "\n" ;
}

//   
/*                                                          
 
                                                                                  
                                                             
                                  
               
                                           
     
                          
                                                                         
                        
                 
           
                                                          
     
                                                                                                     
                    
     
                                                                                     
                  
 */

int count (char words [30000][60], char **sentence_array , int word_counter, int letter_counter, int counter, int times) //                                          
{
    char sentence[10000] ; //                                                           
    cout << "Please enter a sequence of words/sentence. \n" ;
    cin.getline(sentence, 99999) ;
    word_counter = 0 ; //                        
    letter_counter = 0 ;
    while(sentence[letter_counter]) //                                                                              
    {
        //                                  
        //             
        if (sentence[letter_counter] != ' ')
            sentence_array[word_counter][letter_counter] = sentence[letter_counter] ;
        else //                          
            word_counter++;
        letter_counter++ ;
    }
    cout << sentence_array[0] ;
    //                      
    times = 0 ;
    int word_in_sentence ;
    for (int position = 0; position < counter; position++)
    {
        for (int word_in_sentence = 0; word_in_sentence < word_counter; word_in_sentence++)
        {
            if (cmp_str(words[position], sentence_array[word_in_sentence])) //                                                   
                {
                times++ ;
                position++ ;
                }
        }
    }
    cout << "The sentence '" << sentence << "' was found " << times << " times. \n" ;
    return times ;
}

int main()
{
    char words [30000][60] ;
    ifstream infile ;
    int counter ;
    enter_filename(infile, words, counter) ;
    content(words, counter) ;
    int word_counter ;
    int letter_counter ;
    //                                 
    char *sentence_array [10000]; //          
    for(int i = 0; i<10000; i++) //          
        sentence_array[i] = (char *) malloc(60); //          
    int times ;
    count (words, sentence_array, word_counter, letter_counter, counter, times) ;
}

