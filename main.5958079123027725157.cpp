#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <search.h>
#include <cstring>
#include <string.h>

//                                                                         
//                                              
using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

void Name_file (ifstream& input_file) {
    string Command;
    string Element;
    cout << "What would you like to do? commands: Enter, quit." << "\n" << ">";
    cin >> Command;
    if( Command == "Enter" ) {
        cin.ignore(1);
        getline(cin, Element);
        cout << "Filename is '" << Element << "'" << endl;
        input_file.open(Element);
    }
    else{
        cout << "wrong input!" << endl;
    }

}

void show_read_words(ifstream& input_file, char words[MAX_WORDS][MAX_CHARS]){
    assert(input_file.is_open());

    int i = 0;
    while(input_file >> words[i]){

        i++;
    }

}

void read_word (ifstream& input_file, char word[MAX_CHARS]){
    assert(input_file.is_open());
    //                                               
    int i = 0;

    do {
        i++;
    }
    while(input_file >> word);
    cout << "Number of total words in text is: "<< i-1 << "\n"<< endl;

    input_file.clear();
    input_file.seekg(0, ios::beg);

}
int count_word (ifstream& input_file, char word [MAX_CHARS]){
    assert(input_file.is_open());
    //                                               
    int i = 0;

    do {
        i++;
    }
    while(input_file >> word);
    input_file.clear();
    input_file.seekg(0, ios::beg);
    return i;
}

int main() {

    ifstream input_file;
    Name_file(input_file);
    if(input_file.is_open()) {
        char words [MAX_WORDS][MAX_CHARS];
        char word [MAX_CHARS];

        read_word(input_file, word);
        show_read_words(input_file, words);
        cout << "What would you like to do next? (Commands: Content, Count, Where, Context, Exit) \n" << ">";
        string answer;
        cin >> answer;
        cout << "\n";
        if(answer == "Content") {
            cout << "Content is: " << "\n" << endl;
            for (int i = 0; i <= count_word(input_file, word); ++i)
            {
                for (int j = 0; j < MAX_CHARS; ++j)
                {
                    cout << words[i][j] ;
                }
                cout << endl;
            }
        }
        else if(answer == "Exit"){
            return 0;
        }
        else if(answer == "Count"){
            cout << "Please enter a word you want to see the frequency of: "<< endl;
            string sequence;
            cin >> sequence;
            int counter =0;
            for (int i = 0; i <= count_word(input_file, word); ++i)
            {
                    string element = (words[i]);
                    if (sequence == element){
                        counter++;
                    }

            }
            cout << "The word you entered appeared " << counter << " amount of times."<< endl;
            read_word(input_file, word);
            double a = count_word(input_file, word) -1;
            double p = ((counter / a) * 100);
            cout << "So the percentage of the inputted word in text is: "<< p << "%" << endl;

        }
        else if(answer == "Where") {
            return 0;
        }
        }
    return 0;
}
