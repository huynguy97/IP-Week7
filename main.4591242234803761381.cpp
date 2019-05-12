//                             
//                          

using namespace std;

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
const int MAX_FILENAME_LENGTH = 80;
const int MAX_WORDS = 30000;
const int MAX_CHARS = 60;
const int MAX_WORDS_SEQ_SEARCH = 50;
const int MAX_WORDS_SEQ_SEARCH2 = 50;

char word [MAX_CHARS];
string words [MAX_WORDS];

int count_word(ifstream& infile, char words[MAX_WORDS][MAX_CHARS])
{
    int count = 0;
    while (count < MAX_CHARS && infile >> words[MAX_WORDS][MAX_CHARS])
    {
        count++;
    }
    return count;
}
int read_word(ifstream& infile, int i, char words[MAX_WORDS][MAX_CHARS])
{
    char c;
    infile.get(c);

    if (c == '\n') {
        return false;
    }

    int k = 0;

    while (c != ' ' && c != '\n') {
        words[i][k] = c;
        k++;
    }

    words[i][k] = '\0';

    return k;
}

int read_words(ifstream& infile, char word[MAX_CHARS], string words[MAX_WORDS])
{
    assert(infile.is_open());
    int i = 0;
    /*
                                   
     
                                        
         
                
         
     */
    string word1;
    while (infile){
        infile >> word1;
        words[i] = word1;
//                                                                        
        i++;
    }
    return i;
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

bool open_file(ifstream& infile, string& filename)
{
    //                          
    char word [MAX_CHARS];
    infile.open(filename);
    if (infile.is_open())
    {
        cout << "The file " <<filename<< " is opened succesfully." << endl;

        return infile.is_open();
    }
    else
    {
        cout << "the file has not been opened" << endl;
        return false;
    }

}

void enter(string& filename, ifstream& infile, char word[MAX_CHARS])
{
    cin.ignore(1);
    getline(cin, filename, '\n');
    cout << filename <<" has been read succesfully" << endl;

}

void content(string words[MAX_WORDS], int& i)
{

    for (int n = 0; n < i-1; n++)
    {
        //                                                      
        cout << words[n] << endl;
        //                     
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

int user_interface(string& filename, ifstream& infile, string& words_context) {
    while (true) {

        cout << "please enter a command followed by a parameter" << endl;
        string command;
        int i;
        cin >> command;
        if (command == "enter") {
            enter(filename, infile, word);
            infile.open(filename);
            i = read_words(infile, word, words);
            cout << "The amount of words read is: " << i - 1 << endl;
        }
        if (command == "content") {
            content(words, i);
        }
        if (command == "stop") {
            return 1;
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

    }
}
int main() {
int k = 0;

ifstream infile;
string filename;
string words_context;
while (true)
{
    return user_interface(filename, infile, words_context);
}

    return 0;
}
