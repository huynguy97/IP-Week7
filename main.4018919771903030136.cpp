#include <iostream>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <cassert>

using namespace std;

//                          
//                             

bool open_file (ifstream& file, char file_name [], string str_arr [], int length, int& counter) {
    assert (length >= 0);
    cout << "Opening..." << endl << endl;
    file.open(file_name);
    while (file) {
        file >> str_arr[counter];
        counter = counter + 1;
    }
    if (file.is_open()) {
        return true;
    }
    return false;
}

void show_content (string str_arr [], int& counter) {
    assert (true);
    cout << endl << "Printing content..." << endl <<endl;
    for (int i = 0; i <= counter; i++) {
        cout << str_arr[i] << " ";
    }
    cout << endl << endl;
    cout << "End of file" << endl << endl;
}

bool identify_sequence (string text [], string words [], int counter, int index) {
    assert (counter >= 0 && index >=0 && "ERROR at identify sequence");
    int occurence_counter = 0;
    int word_counter = 0;
    for (int i = index; i < counter; i ++) {
        if (text[i] == words[word_counter]) {
            occurence_counter = occurence_counter + 1;
            word_counter = word_counter + 1;
        }
    }
    if (occurence_counter = counter) {
        return true;
    }
    return false;
}

void count_words (string text [], int counter) {
    assert (counter >= 0 && "COUNTER ERROR at count_words");
    const int SEQUENCE_MAX = 100;
    string count_arr [SEQUENCE_MAX];
    char char_get = '.';
    int i = 0;
    int sequence_counter = 0;
    cin >> count_arr[i];
    cin.get(char_get);
    i++;
    while (char_get != '\n') {
        cin >> count_arr[i];
        cin.get(char_get);
        i++;
    }
    for (int j = 0; j < counter; j++) {
        if (text[j] == count_arr[0]){
            if (identify_sequence(text, count_arr, i, j)){
                sequence_counter = sequence_counter + 1;
            }
        }
    }
    cout << endl << "Your sequence has occurred " << sequence_counter << " times in the text" << endl << endl;
    cout << "The text has a total of " << counter - 1 << " words" << endl << endl;
    cout << "Your sequence comprises " << ((i*double(sequence_counter))/(counter-1))*100 << "% of the text" << endl << endl;
}

void locate_index (string text[],int counter) {
    assert (counter >= 0 && "COUNTER ERROR at locate_index");
    const int SEQUENCE_MAX = 100;
    string count_arr [SEQUENCE_MAX];
    char char_get = '.';
    int i = 0;
    int sequence_counter = 0;
    cin >> count_arr[i];
    cin.get(char_get);
    i++;
    while (char_get != '\n') {
        cin >> count_arr[i];
        cin.get(char_get);
        i++;
    }
    for (int j = 0; j < counter; j++) {
        if (text[j] == count_arr[0]){
            if (identify_sequence(text, count_arr, i, j)){
                cout << endl << "Sequence found at index " << j + 1 << endl;
                sequence_counter = sequence_counter + 1;
            }
        }
    }
    cout << endl << "Your sequence has occured " << sequence_counter << " times in the text" << endl << endl;
}

/*                                                    
              
                                 
                                    
                        
              
                             
             
                      
                              
                            
                          
            
     
                                       
                                     
                                                          
                                                        
                                 
                                                                   
                                                         
                     
                        
                                                                                        
                                                              
                         
                     
             
         
     
                                                                                                             
 */

int main(){
    ifstream text_file;
    const int CHOICE_MAX = 500;
    const int WORDS_MAX = 30000;
    char choice [CHOICE_MAX];
    int word_counter = 0;
    string cmd = " ";
    string text_arr [WORDS_MAX];
    while (cmd != "stop") {
        cout << "Enter your command: " << endl;
        cin >> cmd;
        if (cmd == "stop") {
            cout << "Stopping..." << endl;
            return 0;
        }
        cin.get();

        //                                                                
        if (cmd == "enter") {
            cin.getline (choice, CHOICE_MAX);
            if (open_file(text_file, choice, text_arr, CHOICE_MAX, word_counter)){
                cout << "File opened successfully..." << endl << endl;
            } else {
                cout << "Invalid file. Try again" << endl << endl;
            }
        }
        if (cmd == "content") {
            show_content(text_arr, word_counter);
        }
        if (cmd == "count") {
            count_words(text_arr, word_counter);
        }
        if (cmd == "where") {
            locate_index(text_arr, word_counter);
        }
       /*                        
                                                    
         */
    }

    return 0;
}

