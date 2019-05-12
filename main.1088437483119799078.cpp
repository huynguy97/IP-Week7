#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include <cmath>

//                   
//                     
//                      

using namespace std;

const int SIZE = 10000;

void read_file(ifstream& infile, string filename) {
    //              
    assert(filename.length() <= 80 && filename.length() > 0);
    //                                  
    infile.open(filename.c_str());
}

void store_content(ifstream& infile, string& storage) {
    //              
    assert( infile.is_open() );
    //                                                                     
    storage = "";
    string word;
    infile >> word;
    storage += word;
    while(infile) {
        infile >> word;
        storage += ' ' + word;
    }
    infile.close();
}

int word_occurances(string& storage, string remainder, int locations [SIZE]){
    //              
    assert(true);
    //                                               
    int previous = 0;
    int counter = 0;
    while(previous < storage.length()){
        previous = storage.find(remainder, previous + 1);
        if(previous < storage.length()){
            locations[counter] = previous;
            counter++;
        }
    }
    return counter;
}

void word_counter(int where[SIZE], int words[SIZE], string& storage){
    //              
    assert(true);
    //                                                       
    int word_location [SIZE];
    int slice = 0;
    for(int i = 0; i < SIZE; i++){
        if(words[i] > where[slice]){
            word_location[slice] = i + 1;
            slice++;
            if (where[slice] == 0) {
                cout << "Word index of each occurance: " << word_location[0];
                for(int i = 1; i < slice; i++) {
                    cout << "," << word_location[i];
                }
                cout << endl;
                return;
            }
        }
    }
}

void context(int where[SIZE], int words[SIZE], string& storage, int m, int n) {
    //              
    assert(true);
    //                                                      
    int word_location [SIZE];
    int slice = 0;
    for(int i = 0; i < SIZE; i++){
        if(words[i] > where[slice]) {
            word_location[slice] = i + 1;
            //                                                                         
            if (storage.substr(words[i - 1 - m], 1) == " ") { //                                            
                cout << storage.substr(words[i - 1 - m] + 1, words[i - 1 + m + n] - words[i - 1 - m] - 1) << endl;
            } else {
                cout << storage.substr(words[i - 1 - m], words[i - 1 + m + n] - words[i - 1 - m]) << endl;
            }
            slice++;
            if (where[slice] == 0) {
                return;
            }
        }
    }
}

int parse_command(string command){
    //              
    assert(true);
    //                                                               
    for (int i = 0; i < command.size(); i++) {
        if (command.substr(i, 1) == " ") {
            return i;
        }
    }
}

int find_m(int m_length, string m_string) {
    //              
    assert(true);
    //                                     
    int m = 0;
    for(int i = 0; i<m_length; i++) { //                                                             
        m += (m_string.c_str()[i] - '0') * pow(10, m_length - i - 1);
    }
    return m;
}

void enter_command(ifstream& infile, string& storage) {
    //              
    assert(true);
    //                                          
    string command;
    cout << "Enter command:";
    getline(cin, command, '\n');
    if(command.substr(0,4) == "stop") {
        return;
    } else if(command.substr(0,5) == "enter") {
        read_file( infile, command.substr(6,75) );
        if( infile.is_open() ) {
            store_content(infile, storage);
        } else {
            cout << "Could not open file \'" << command.substr(6,75) << "\'" << endl;
        }
    } else if(command.substr(0,7) == "content") {
        cout << storage << endl;
    } else if(command.substr(0,5) == "count") {
        int locations [SIZE];
        int occurances = word_occurances(storage, command.substr(5, 75) + " ", locations);
        int total = word_occurances(storage, " ", locations);
        cout << "Occurances: " << occurances << endl;
        cout << "Total words: " << total << endl;
        if(total > 0) {
            cout << "Percentage: " << static_cast<double>(occurances) / total * 100 << "%" << endl;
        } else {
            cout << "Percentage: N/A" << endl;
        }
    } else if(command.substr(0,5) == "where") {
        int where [SIZE] = {0};
        int words [SIZE] = {0};
        int n_occurances = word_occurances(storage, command.substr(5, 75) + " ", where);
        word_occurances(storage, " ", words);
        if(n_occurances > 0) {
            word_counter(where, words, storage);
        }
        cout << "Total number of occurances: " << n_occurances << endl;
    } else if(command.substr(0,7) == "context") {
        int where [SIZE] = {0};
        int words [SIZE] = {0};
        int m_length = parse_command(command.substr(8, 75));
        int n_occurances = word_occurances(storage, command.substr(8 + m_length, 75) + " ", where);
        word_occurances(storage, " ", words);
        if(n_occurances > 0) {
            cout << "Context: " << endl;
            int n [SIZE] = {0};
            string comm = command.substr(9 + m_length, 75);
            context(where, words, storage, find_m(m_length, command.substr(8, m_length)), word_occurances(comm, " ", n) + 1);
        }
        cout << "Total number of occurances: " << n_occurances << endl;
    }
    enter_command(infile, storage);
}

int main()
{
    string storage = "";
    ifstream infile;
    enter_command(infile, storage);
}

