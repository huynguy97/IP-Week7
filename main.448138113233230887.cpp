#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>

//                  
//                       

using namespace std;

const int MAX_CHAR = 60;
const int MAX_WORDS = 3000;

bool open_file (ifstream& file) //                                    
{
    //            
    assert (!file.is_open()); //                                                 
    //                                                                                    
    string input;
    getline(cin,input);
    cout << input << endl ;
    file.open(input.c_str());
   if ( file )
    {
        string input;
        cout << "File was opened" << endl ;
        return true;
    }
    cout << "File was not opened" << endl;
    return false;
}

int read (ifstream& file ,  string words [MAX_WORDS]) //                      
{
    //             
    assert (file.is_open());
    //                                                                                               
    int i = 0 ;
    cout << "Number of words in file is:  " <<sizeof(file)/sizeof(string)  << endl;
    for ( i ; i < sizeof(file)/sizeof(string) ; i++ )
    {
        file >> words [i];
        cout << words [i] << " ";
        cout << i << endl;

    }
    return i;

}

void count_words (ifstream& file, string words [MAX_WORDS], int freqs)
{
    //             
    assert (file.is_open());
    //                                                                                                                                      

    cout << "Number of words in file is:  " <<sizeof(file)/sizeof(string)  << endl;
    cout << "Please enter word: " ;
    string word ;
    cin >> word ;
    int j = 0;

    for ( j ; j < sizeof(file)/sizeof(string) ; j++ )
    {
        file >> words [j];

        cout << words [j] << endl;
            if (word == words[j])
            {
                freqs ++;
            }
    }
    cout << word << " " << freqs  << " " << (double)freqs / (sizeof(file)/sizeof(string))*100 << "%" << endl;

}

void where (ifstream& file ,  string words [MAX_WORDS],int freqs)
{
    //             
    assert (file.is_open ());
    //                                                                                                                   
    cout << "Please enter word: " ;
    string word ;
    cin >> word ;
    int i = 1 ;
    cout << "Number of words in file is:  " <<sizeof(file)/sizeof(string)  << endl;
    for ( i ; i < sizeof(file)/sizeof(string) ; i++ )
    {
        file >> words [i];
        if ( word == words[i])
        {
            cout <<"'"<< word << "'" << " has been found on position: " << i << endl;

            freqs ++;
        }
    }
    cout << freqs << endl;

}

void context (ifstream& file ,  string words [MAX_WORDS],int freqs)
{
    //             
    assert (file.is_open ());
    //                                                                    
    //                                                                                                                                  
    cout << "Please enter word: " ;
    string word ;
    cin >> word ;
    int n = sizeof(file)/sizeof(string) - 1;
    int backwards = n ;
    string word1 ; //                  
    string word2 ; //                 

    cout << "Number of words in file is:  " <<sizeof(file)/sizeof(string)  << endl;
    for ( n ; n > 1 ; n-- )
    {
        file >> words [n];
        if ( word == words[n + 1])
        {
            word1 = words[n + 2];
            word2 = words[n];
            cout << words[n + 2] << " " << word << " " << words[n] << endl;
            for ( n; n > 0 ; n-- )
            {
                 if ( words[n] == word1 && words [n-1] == word  && words [n+2] ==  word2 )
                {
                    freqs ++;
                    cout << freqs << endl; //                   
                }
            }

        }
    }

}

void show_first_menu ()
{
    //            
    assert (true); //                                                         
    //                                                                     
    cout << "What would you like to do?" << endl;
    cout << "1. Enter" << endl;
    cout << "3. Stop" << endl;

}
void show_second_menu ( ifstream& file )
{
    //            
    assert ( file.is_open ()); //                                                                                                                   
    //                                                                
    cout << "What would you like to do?" << endl;
    cout << "2. Content" << endl;
    cout << "3. Stop" << endl;
    cout << "4. Count" << endl;
    cout << "5. Where" << endl;
    cout << "6. Context" << endl;

}

int first_selection (ifstream& file, int in )
{
    //            
    assert (true); //                                                 
    //                                                                                                                                              
    switch (in)
    {
   case 1:
        cout << "Enter filename: ";
        open_file ( file);
        break;
    case 3:
        cout <<"Stopping..." << endl;
        cout << "Please press 'Enter' to close the program." << endl;
        break;
    default :
        cout << endl << "Unknown command." << endl << endl;
    }
    return in;
}

    int second_selection (ifstream& file, int in,  string words [MAX_WORDS],int freqs)
{
    //            
    assert ( file.is_open ());  //                                                                                                                   
    //                                                                                                           

    switch (in)
    {
    case 2:

        cout << endl << "Showing Content..." << endl << endl;
        read ( file, words ) ;
        break;
    case 3:
        cout << endl << "Stopping..." << endl;
        cout << "Please press 'Enter' to close the program." << endl;
        break;
    case 4:
        cout << endl << "Counting..." << endl << endl;
        count_words ( file, words ,  freqs) ;
        break;
    case 5:
        cout << endl << "Searching..." << endl << endl;
        where (file , words , freqs);
        break;
    case 6:
        cout << endl << "Finding context..." << endl << endl;
         context ( file , words , freqs);
        break;
    default :
        cout << endl << "Unknown command." << endl << endl;
    }
    return in;
}

int main ()
{

    char filename [MAX_CHAR] ;
    int freqs = 0;
    ifstream file ;
    string words [MAX_WORDS];

    show_first_menu ();
    cout << endl << "Please choose from the menu:" ;
    int input;
    cin >> input;
    first_selection (file, input);
    if ( input == 1 )
    {
        open_file ( file);
        do
        {
            show_second_menu (file );
            cout << endl << "Please choose from the menu:" ;
            cin >> input;
            input = second_selection (file, input , words , freqs);
        } while( input != 3); //               

    }
    return 0;
}

