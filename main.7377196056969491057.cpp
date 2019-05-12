//                                                           

#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>
#include <bits/stdc++.h>

const int MAX_WORDS = 400000; //                                                                                     
const int MAX_WORD_SEQ = 350; //                                               
bool file_read = false; //                                    
int total_words = 0; //                                   
int sequence_length = 0; //                                                   

using namespace std;

/*
                                       
*/
bool read_contents(ifstream& infile, string words[])
{
    assert(infile.is_open() && !file_read);

    string word;

    while(!infile.eof()) {
        infile >> word;
        if (word.find(".", 0) != -1)
            word = word.substr(0, word.length()-1);
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words[total_words] = word;
        total_words++;
    }
    cout << "Number of words: " << total_words << endl;
}

/*
                                               
*/
bool open_file(string filename, string words[])
{
    assert(filename.length() > 0);

    ifstream infile(filename.c_str());
    if (!infile){
        cout << "File doesn't exist" << endl;
        return false;
    }
    read_contents(infile, words);
    file_read = true;
    return true;
}

/*
                                                      
*/
void content(string words[])
{
    assert(MAX_WORDS > 0);

    for (int i = 0; i < MAX_WORDS; i++) {
        if (words[i] == "") {
            if (!file_read)
                cout << "No file read yet" << endl;
            break;
        }
        cout << words[i] << " ";
    }
    cout << endl;
}

/*
                                                            
*/
void word_sequence(string sequence[], string all_words)
{
    assert (MAX_WORDS > 0 && MAX_WORD_SEQ > 0);

    int counter = 0;
    int start_pos = 0;
    int end_pos = 0;
    while (start_pos < all_words.length()) {
        end_pos = all_words.find(" ", start_pos);
        if (end_pos == -1)
            end_pos = all_words.length();
        string word = all_words.substr(start_pos, end_pos-start_pos);
        sequence[counter] = word;
        start_pos = end_pos+1;
        counter++;
    }
    sequence_length = counter;
}

/*
                                                                             
                                                
*/
int find_occurrence(string sequence[], string words[], bool where)
{
    assert(MAX_WORDS > 0 && MAX_WORD_SEQ > 0);

    int encounters = 0;
    int counter = 0;
    int seq_counter = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        if (words[i] == sequence[0]){
            counter = i;
            seq_counter = 0;
            bool encounter = true;
            while (sequence[seq_counter] != "") {
                if (sequence[seq_counter] != words[counter])
                    encounter = false;
                counter++;
                seq_counter++;
            }
            if (encounter) {
                encounters++;
                if (where) {
                    for (int j = 0; j < MAX_WORD_SEQ; j++) {
                        if (sequence[j] == "")
                            break;
                        cout << "Word: " << sequence[j] << "\tIndex: " << i+j << endl;
                    }
                }
            }
        }
    }
    return encounters;
}

/*
                                                                                        
                                     
*/
void word_count(string words[], string all_words)
{
    assert(MAX_WORDS > 0);

    string sequence[MAX_WORD_SEQ];
    bool where = false;
    word_sequence(sequence, all_words);
    int encounters = find_occurrence(sequence, words, where);

    cout << "Number of occurrences: \t" << encounters << endl;
    cout << "Total number of words: \t" << total_words << endl;
    cout << "Percentage of occurrences: \t" << (100/total_words)*encounters << "%" << endl;
}

/*
                                                                              
                                                                              
*/
int context_occurrence(string sequence[], string words[])
{
    assert(MAX_WORDS > 0 && MAX_WORD_SEQ > 0);

    int encounters = 0;
    int counter = 0;
    int seq_counter = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        if (words[i] == sequence[1]) {
            counter = i;
            seq_counter = 1;
            bool encounter = true;
            while (sequence[seq_counter] != "") {
                if (sequence[seq_counter] != words[counter])
                    encounter = false;
                counter++;
                seq_counter++;
            }
            if (encounter) {
                encounters++;
                int precede =  atoi(sequence[0].c_str());
                for (int j = i-precede; j < MAX_WORDS && j > 0; j++) {
                    if (precede > 0) {
                        if (words[j] == "")
                            break;
                        cout << words[j] << " ";
                    }
                    precede--;
                }
                for (int j = 1; j < MAX_WORD_SEQ; j++) {
                    if (sequence[j] == "")
                        break;
                    cout << sequence[j] << " ";
                }
                int succeed =  atoi(sequence[0].c_str());
                int next = 0;
                for (int j = i+1; j < MAX_WORDS; j++) {
                    if (next < succeed) {
                        if (words[j] == "")
                            break;
                        cout << words[j] << " ";
                    }
                    next++;
                }
            }
            cout << endl;
        }
    }
    return encounters;
}

void word_position(string words[], string all_words)
{
    assert(MAX_WORDS > 0);

    string sequence[MAX_WORD_SEQ];
    bool where = true;
    word_sequence(sequence, all_words);
    int encounters = find_occurrence(sequence, words, where);

    cout << "Number of occurrences: \t" << encounters << endl;
}

void word_context(string words[], string all_words)
{
    assert(MAX_WORDS > 0);

    string sequence[MAX_WORD_SEQ];
    bool where = false;
    word_sequence(sequence, all_words);
    int encounters = context_occurrence(sequence, words);

    cout << "Number of occurrences: \t" << encounters << endl;
}

void commands(string words[])
{
    assert(MAX_WORDS > 0);

    string command;
    do {
        getline(cin, command);
        if (command.substr(0, 5) == "enter") {
            string filename = command.substr(6, command.length());
            open_file(filename, words);
        } if (command.substr(0, 7) == "content")
            content(words);
        if (command.substr(0, 5) == "count") {
            string all_words = command.substr(6, command.length());
            word_count(words, all_words);
        }
        if (command.substr(0, 5) == "where") {
            string all_words = command.substr(6, command.length());
            word_position(words, all_words);
        }
        if (command.substr(0, 7) == "context") {
            string all_words = command.substr(8, command.length());
            word_context(words, all_words);
        }
    } while (command != "stop");
}

int main()
{
    string words [MAX_WORDS];
    commands(words);
    return 0;
}

