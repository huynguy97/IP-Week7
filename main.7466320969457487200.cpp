#include <iostream>
#include <ostream>
#include <cassert>
#include <fstream>
#include <string.h>

//                              
//                            

const int MAX_LENGTH_FILENAME = 100;
const int MAX_WORDS = 10000;
using namespace std;

int enter(ifstream& file, string words[MAX_LENGTH_FILENAME]){
    assert(!file.is_open());

    //                                              
    char filename[MAX_LENGTH_FILENAME];
    cin.getline(filename, MAX_LENGTH_FILENAME);
    for(int i =0; i<MAX_LENGTH_FILENAME-1; i++){ //                                      
        filename[i] = filename[i+1];
    }
    file.open(filename);
    if(!file){
        cout << "File was NOT opened succesfully!\n";
        return 0;
    }
    int i =0;
    while(file){
        string word;
        file >> word;
        words[i] = word;
        i++;
    }

    cout << "The number of words in the file is " << i-1 << endl;
    return i-1;
}

int content(string words [MAX_LENGTH_FILENAME]){
    assert(true);

    //                                                               
    int i=0;
    while(words[i]!=""){
        cout << words[i] << " ";
        i++;
    }
    cout << endl;
    return i;
}

int number_of_chars_in_text(string words[MAX_LENGTH_FILENAME]){
    assert(true);

    //                                             
    int total=0;
    for(int i =0; i<MAX_LENGTH_FILENAME;i++){
        if(words[i]!=""){
            total+=words[i].length()+1;//                                
        }
    }
    return total-1;//                                         
}

void cnt(ifstream& file, string words[MAX_LENGTH_FILENAME], int no_of_words){
    assert(file.is_open());

    //                          
    string text;
    for(int i =0; i<no_of_words;i++){
        text+=words[i] + " ";
    }

    string input;
    getline(cin, input);
    int total=0;
    int i=0;
    while(i<text.length()){
        if(text[i]==input[0]){
            for(int j=1;j<input.length();j++){
                i++;
                if(input[j]!=text[i])break;
                if(j==input.length()-1)total++;
            }
        }
        i++;
    }
    cout << "The total number of occurances of '" << input << "' is " << total << endl;
    cout << "The total number of words in the text is " << no_of_words << endl;
    cout << "The percentage of these occurances from the total number of words is " << 1.0*no_of_words/total*10 << "%" << endl;
}

int where(string words[MAX_WORDS], int no_of_words){
    assert(true);

    //                                                
    string input;
    getline(cin, input);
    string text;
    for(int i =0; i<no_of_words;i++){
        text+=words[i] + " ";
    }
    int index =1;
    for(int i=0;i<=text.find(input);i++){
        if(text[i]==' ')index++;
    }
    cout << "The index of the occurance is " << index << endl;
    return index;
    //                                                                                   
    //                                                                         
}

void context(string words[MAX_WORDS], int no_of_words){
    int m;
    cin >> m;

    int index = where(words, no_of_words);
    for(int i=index-m-1; i<index+m; i++){
        cout << words[i] << " ";
    }
    cout<<endl;

    //                                                                                                       
}

int main()
{
    string words [MAX_WORDS];
    int no_of_words=0;
    ifstream file;
    string cmd;
    while(true){
        cout << "Enter your command: ";
        cin >> cmd;
        if(cmd == "enter")no_of_words=enter(file, words);
        if(cmd == "content")content(words);
        if(cmd == "stop") assert(false);
        if(cmd == "count")cnt(file, words, no_of_words);
        if(cmd == "where")where(words,no_of_words);
        if(cmd == "context")context(words,no_of_words);
    }
}

