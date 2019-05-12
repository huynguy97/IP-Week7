#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <string>

using namespace std;
const int MAX_WORDS = 300000;
const int MAX_CHARS = 80;

bool open_text_file(ifstream& infile)
{
    assert(!infile.is_open());
    char filename[MAX_CHARS];
    cin.getline(filename, MAX_CHARS) ;
    infile.open(filename);
    return infile.is_open();
    //                                                         
}

bool read_words(ifstream& infile, char words[])
{
    assert(infile.is_open());
    infile >> words;
    return infile;
    //                                                
}

void show_content(char words[]){
    for(int index=0; index<MAX_WORDS; index ++){
        cout<< words[index]<< " " <<endl;
    }
    //                                      
}

bool stop(){
cout<<" You stopped the program"<<endl;
return 0;
//                                    
}

bool get_command(string choice){
    cout << ">> ";
    string word;
    cin >> word;
    if( word =//                                                          
        open_text_file();
        read_words();
    }
    else if( word == "content"){
        show_content();
    }
    else if(word == "stop"){
        stop();
    }
    else if(word == "count"){
     count_words();
    }
    return 0;
//                                                                 
}

int count_words(ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int freqs[]MAX_WORDS){
assert(infile.is_open());
int no=0;
char next [MAX_CHARS];
while(read_words(infile,next)&& no<MAX_WORDS){
    return no:

}
//                                               
}

int main()
//                                          
{
ifstream inputfile;
string choice;
get_command(choice);
char filename[MAX_CHARS];
open_text_file(filename);

}

