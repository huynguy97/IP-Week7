#include <iostream>
#include <fstream>
#include <cassert>

/* 
                             
                        
*/

using namespace std;

const int MAX_WORD_COUNT = 40000;
const int MAX_SEQUENCE_LENGTH = 0x10;

bool read_word(ifstream& file, string& word){
    //            
    assert(file.is_open());
    //             
    //                                                                                               
    //                        

    word.clear();
    char c;

    //            
    while(file){
        file.get(c);
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            word += c;
            break;
        }
    }
    //         
    while(file){
        file.get(c);
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            word += c;
        }
        else if(c == '-'){
        file.get(c);
            if(c == '-')
                return file;
            else word += "--";
        }
        else return file;
    }
    return file;
}
void receive_sequence(string sequence[], int& sequence_length){
    //            
    assert(sequence_length >= 0);
    //             
    //                                                                                                   

    string line;
    sequence_length = 0;
    getline(cin, line, ' '); //                     
    getline(cin, line);
    for(int i = 0; i < line.length() && sequence_length < MAX_SEQUENCE_LENGTH; i++){
        if(line[i] == ' ' || line[i] == '\t'){
            sequence_length++;
        }
        else {
            sequence[sequence_length] += line[i];
        }
    }
    sequence_length++;
}
bool find_sequence(string table[], string sequence[], int index, int table_length, int seq_length){
    //             
    assert(index + seq_length < table_length && seq_length < MAX_SEQUENCE_LENGTH);
    //              
    //                                                                      
    //                         

    for(int i = 0; i < seq_length; i++){
        if(table[i + index] != sequence[i])
            return false;
    }
    return true;
}
void read_file(string table[], int& entry_count){
    //             
    assert(true);
    //              
    //                                                                                                              
    //                                
    //                               

    string file_name;

    getline(cin, file_name, ' '); //                     
    getline(cin, file_name);

    ifstream file(file_name.c_str());
    if(!file.is_open()){
        cout << "Couldn't open file.\n";
        return;
    }

    entry_count = 0;
    while(file && entry_count < MAX_WORD_COUNT){
        read_word(file, table[entry_count]);
        entry_count++;
    }
    cout << entry_count << " words were read from file.\n";
}
void print_content(string table[], int entry_count){
    //             
    assert(entry_count <= MAX_WORD_COUNT && entry_count >= 0);
    //              
    //                                                  
    for(int i = 0; i < entry_count; i++){
        cout << table[i] << endl;
    }
}
void count_sequence(string table[], int entry_count){
    //             
    assert(entry_count >= 0);
    //              
    //                                                                         
    //                                              
    //                                                                                    
    string sequence[MAX_SEQUENCE_LENGTH];
    int sequence_length = 0;

    receive_sequence(sequence, sequence_length);

    int occurrences = 0;

    for(int i = 0; i < entry_count - sequence_length; i++){
        if(find_sequence(table, sequence, i, entry_count, sequence_length))
            occurrences++;
    }

    int percentage = occurrences * 100 / entry_count;

    cout << "Number of Occurences: " << occurrences << "\nTotal word count: " << entry_count << "\nPercentage: " << percentage << "%\n";
}
void print_where(string table[], int entry_count){
    //            
    assert(entry_count >= 0);
    //             
    //                                                                                              
    string sequence[MAX_SEQUENCE_LENGTH];
    int sequence_length = 0;

    receive_sequence(sequence, sequence_length);

    int occurrences = 0;
    for(int i = 0; i < entry_count - sequence_length; i++){
        if(find_sequence(table, sequence, i, entry_count, sequence_length)){
            cout << i+1 << ", ";
            occurrences++;
        }
    }
    cout << "\nNumber of occurrences: " << occurrences << endl;
}
void print_context(string table[], int entry_count){
    //            
    assert(entry_count >= 0);
    //             
    //                                                                 
    string sequence[MAX_SEQUENCE_LENGTH];
    int sequence_length = 0;

    int context;
    cin >> context;

    receive_sequence(sequence, sequence_length);

    int occurrences = 0;
    for(int i = 0; i < entry_count - sequence_length; i++){
        if(find_sequence(table, sequence, i, entry_count, sequence_length)){
            int begin = i - context;
            int end = i + context + sequence_length;
            begin = begin < 0 ? 0 : begin;
            end = end >= entry_count ? entry_count - 1 : end;
            for(int j = begin; j < end; j++){
                cout << table[j] << ' ';
            }
            cout << endl;
            occurrences++;
        }
    }
    cout << "\nNumber of occurrences: " << occurrences << endl;
}

int main(){
    string table[MAX_WORD_COUNT];
    int word_count;

    string command;

    while(true){
        cin >> command;
        if(command == "enter")
            read_file(table, word_count);
        else if(command == "content")
            print_content(table, word_count);
        else if(command == "where")
            print_where(table, word_count);
        else if(command == "context")
            print_context(table, word_count);
        else if(command == "count")
            count_sequence(table, word_count);
        else if(command == "stop")
            break;
        else
            cout << "unknown command\n";
    }

}

