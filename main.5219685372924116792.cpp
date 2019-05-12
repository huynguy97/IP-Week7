//                 
//                          
//                                                                                          

#include <iostream>
#include <string>
#include <fstream> //             
#include <cassert> //              

using namespace std;

const int MAX_WORDS = 30000;

bool open_file(ifstream& infile, string filename, string words [MAX_WORDS], int& nr_words){
    //                   
    assert(!infile.is_open());
    //                    
    //                                                             
    int i = 0;
    infile.open(filename);
    if (infile.is_open()){
        cout << "\nThe file is open\n";
        while (infile && i < MAX_WORDS){
            infile >> words[i];
            i++;
        }
        nr_words = i - 1;
    }
}

void show_array (string words[MAX_WORDS], int& nr_words) {
    //             
    assert(true);
    //              
    //                                      
    for (int i = 0; i < nr_words; i++) {
    cout << words[i] << ' ';
    }
}

int count_words (string words[MAX_WORDS], int& nr_words, string& word, string& capital_word){
    //             
    assert(true);
    //              
    //                                                                                                               
    //                                    
    int counter = 0;
    for (int i = 0; i <= nr_words; i++){
        if (words[i] == word || words[i] == word + '.' || words[i] == capital_word){
            counter++;
        }
    }
    double percentage = (static_cast<double>(counter)/nr_words)*100;
    cout << "\nThe word " << word << " occurs " << counter << " times in the text \n";
    cout << "wich is " << percentage << "% of the total words in the file.\n";
    cout << "The file has " << nr_words << " words.\n";

    return counter;
}

void where_word (string words[MAX_WORDS], int& nr_words, string& word, string& capital_word) {
    //             
    assert(true);
    //              
    //                                        
    int counter = 0;
    int counter_array[MAX_WORDS];
    for (int i = 0; i <= nr_words; i++) {
        if (words[i] == word || words[i] == word + '.'|| words[i] == capital_word) {
            counter_array[counter] = i + 1;
            counter++;
        }
    }
    cout << "\nThe word " << word << " occurs on places: ";
    for (int i = 0; i <= counter - 1; i++){
        cout << counter_array[i] << ' ';
    }
    cout << "\n";
}

void context_word (string words[MAX_WORDS], int& nr_words, string& word, string& capital_word) {
    //             
    assert(true);
    //              
    //                                                
    cout << "\n" << word << " occurs in the following context: \n";
    for (int i = 0; i <= nr_words; i++) {
        if (words[i] == word || words[i] == word + '.'|| words[i] == capital_word) {
            if (i >= 1){
                cout << words[i-1] << ' ' << word << ' ' << words[i+1] << '\n';
            }
            else if (i < 1){
                cout << words[i] << ' ' << words[i+1] << '\n' ;
            }
        }
    }
}

void enter_command (ifstream& infile, string words[MAX_WORDS], int& nr_words, bool& stop){
    //             
    assert(true);
    //              
    //                                                                                  
    cout << "please enter a command: \n";
    cout << "(enter filename, content, count word, where word, context word, stop)\n";
    string command;
    string filename;
    string word;
    cin >> command;

    if (command == "enter"){
        cin.ignore(1);
        getline(cin, filename, '\n');
        open_file(infile, filename, words, nr_words);
        if (infile.is_open()){
        cout << nr_words << " words have been read\n";
        }
        else cout << "the file could not be opened\n";
    }
    else if (command == "content"){
        cout << "\nthe content of  the file: \n";
        show_array(words, nr_words);
        cout << "\n";
        }
    else if (command == "count" || command == "where" || command == "context" ){
        cin.ignore(1);
        getline(cin, word, '\n');
        string capital_word = word;
        capital_word[0]= toupper(capital_word[0]);
        if (command == "count") {
            count_words(words, nr_words, word, capital_word);
        }
        else if (command == "where") {
            where_word(words, nr_words, word, capital_word);
        }
        else if (command == "context") {
            context_word(words, nr_words, word, capital_word);
        }
    }
    else if (command == "stop"){
        stop = true;
    }
    else cout << "\nunknown command\n";
}

int main() {
    ifstream infile;
    string words[MAX_WORDS];
    bool stop = false;
    int nr_words = 0;
    while (!stop) {
        enter_command(infile, words, nr_words, stop);
        cout << "\n";
    }
    return 0;
}
