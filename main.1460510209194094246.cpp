#include <iostream>
#include <cassert>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

//                                                  

const int MAX_WORDS = 30000 ;
const int MAX_LENGTH = 15 ;

bool open_text_file (ifstream& infile)
{
    //              
    assert(!infile.is_open());
    //                                                
    cout << "Please enter file name: " ;
    char filename [80] ;
    cin.getline(filename, 80) ;
    infile.open ( filename ) ;
    return infile.is_open() ;
}

int content (ifstream& infile,  string words [MAX_WORDS])
{
    //              
    assert(infile.is_open());
    //                                                                                     
    int i = 0;
    while ( i <= MAX_WORDS - 1 && infile )
    {
        infile >> words [i] ;
        cout << words [i] << endl;
        i++ ;
    }
    cout << "Number of words: " << i-1 << endl ;
    return i;
}

void counter (ifstream& infile,  string words [MAX_WORDS], int length)
{
    //              
    assert(infile.is_open());
    //                                                                                    
    //                                                                             
    cout << "Enter word sequence: " ;
    string sequence ;
    cin >> sequence ;
    int i = 0;
    int k = 0;
    while ( i <= length -1)
    {
        if ( sequence == words [i])
        {
            k++ ;
        }
      i++;
    }
    cout << "Count: " << k << ", " << i-1 << ", " <<((double) k)/((double)i)*100 << "%" << endl ;
}

void where (ifstream& infile, string words [MAX_WORDS],int length )
{
    //              
    assert(infile.is_open());
    //                                                                                    
    //                                          
    cout << "Enter word sequence: " ;
    string sequence ;
    cin >> sequence ;
    int i=0;
    int k=0;
    while ( i <= MAX_WORDS -1 )
        {
            if ( sequence == words [i])
            {
                cout << "Index: " << i << " " ;
                k++ ;
                i++ ;
            }
            else
            {
                i++ ;
            }
        }
    cout << endl << k ;
}

void context (ifstream& infile, string words [MAX_WORDS],
              int length, string wordsequence [MAX_WORDS])
{
    //              
    assert(infile.is_open());
    //                                                                                   
    //                                                                      
    cout << "Enter word sequence: " ;
    string sequence ;
    cin >> sequence ;
    cout << "Enter m: " ;
    int m;
    cin >> m ;
    int i=0;
    int k=0;
    int p ;
    int j = 0 ;
        while ( i <= MAX_WORDS -1 )
        {
            if ( sequence == words [i])
            {
                for (int j=i-m; j<=i+m;j++)
                {
                    cout << words[j] << " " ;

                }
                cout << '\n' ;
                k++ ;
            }
            i++ ;
        }
}

int main()
{
    ifstream infile ;
    open_text_file(infile);
    string words [MAX_WORDS];
    int length = content(infile, words);
    counter(infile, words, length);
    cout << '\n' << endl ;
    where(infile, words, length);
    string wordsequence [MAX_WORDS];
    cout << '\n' << endl ;
    context(infile, words, length, wordsequence);
}

