#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstring>

using namespace std;
//                                            
const int MAX_CHARS = 60;
const int MAX_WORDS = 100;
int index = 0;
/*
             
                       
                   

           
                               
                     
*/
bool enter_filename(ifstream& infile)
{
    //              
    assert(!infile.is_open());
    //               
    //                            

    char filename [80];

    cout << "Please enter a file name, spaces are allowed: " << endl;
    cin.getline(filename, 80, '\n');
    infile.open(filename);
    if (infile.is_open())
    {
        cout << "File '" << filename << "' has been successfully opened." << endl;
        return infile.is_open();
    }
    else
    {
        cout << "Opening file '" << filename << "' failed, please rerun the program and try again." << endl;
        return false;
    }
}

bool read_word(ifstream& infile, char word[MAX_CHARS])
{
    //             
    assert (infile.is_open());
    //               
    //                                                                                             
    infile >> word;
    for (int i = 0; i < MAX_WORDS; i++)
    {
        if (word[i] == '.')
            word[i] = '\0';
    }
    return infile;
    /*
                             
                               
                           
                                        
         
                            
         
    */
}
/*          
          
  

               
               
                     
                             

           
*/

int count_text_file(ifstream& infile, char text [MAX_WORDS][MAX_CHARS], int frequency [MAX_WORDS])
{
    //               
    assert(infile.is_open());
    //                                                                                                                 
    int index = 0;

    char word[MAX_CHARS];

    while (read_word(infile, word))
    {
        bool exist = false;
        for (int i = 0; i < MAX_WORDS; i++)
        {
            if (strcmp(word, text[i]) == 0)
            {
                exist = true;
                frequency[i]++;
                cout << "Frequency of word: '" << text[i] << "' increased to: " << frequency[i]
                     << " and is placed on index: " << index + 1 << " in the array."
                     << endl;
            }
        }
        if (exist == false)
            //                                   
        {
            strcpy(text[index],word);
            frequency[index] = 1;
            cout << "Frequency of word: '" << word << "' has been set to 1 and is placed on index: " << index + 1 << " in the array." << endl;
        }
        index++;
    }
    cout << "\nThere are in total: " << index << " words in the array." << endl;
    return index;
}

int main()
{
    char text[MAX_WORDS][MAX_CHARS];
    int frequency[MAX_WORDS];
    char word[MAX_CHARS];

    ifstream infile;
    enter_filename(infile);

    count_text_file(infile, text, frequency);

//                   
    //                      
    //                     
       //                      
    //                       
    //                               

    return 0;

}

