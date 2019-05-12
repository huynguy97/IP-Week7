/*
                                                    
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>
#include <locale>

using namespace std;

const int MAX_WORDS = 30000 ;
const int MAX_FILENAME_LENGTH = 80 ;
const int MAX_WORD_LENGTH = 80 ;

//                                                                                                                                          
bool check_valid(char text [MAX_FILENAME_LENGTH]){
    //                    
    assert(true);
    //                                                                                                 
    char illegal[8] = {'/','\\','*','\?','\"','<','>','|'}; //                                                 
    int newline = -1; //                                               
    for(unsigned int i = 0; i < MAX_FILENAME_LENGTH; i++){
        if (text[i] == '\n'){ //                                     
            newline = i; //                               
            for (unsigned int j = i; j < MAX_FILENAME_LENGTH; j++){
                text[j] = '\0'; //                                                                                  
            }
            break;
        }
    }
    if (newline == -1){ //                                                                 
        return false;
    }
    for (int i = 0; i < 8; i++){
        int j = 0;
        while (text[j] != '\n' && j <= newline){
            if (text[j] == illegal[i]){ //                                                                                                   
                return false; //                     
            }
            j++;
        }
    }
    return true; //                   
}

//                                                                                             
bool open_file (ifstream& input_file){
    //                                     
    assert(!input_file.is_open());
    //                                                                                          
    char filename [MAX_FILENAME_LENGTH];
    bool valid = false;
    while (!valid){
        int i = 0;
        cin.ignore(1);
        while (cin.get(filename[i]) && i < MAX_FILENAME_LENGTH){ //                                                                                                              
            if (filename[i] == '\n'){
                break; //                                                             
            }
            i++;
        }
        valid = check_valid(filename); //                                                                                                    
        if (!valid){ //                                                          
            cout << "Invalid filename: " << filename << endl;
            return false;
        }
    }
    input_file.open(filename);
    if (!input_file.is_open()) { //                                           
        cout << "Error: Input file " << filename << " could not be opened." << endl << endl;
        return false;
    }
    cout << "The file " << filename << " has been opened successfully." << endl << endl;
    return true; //                                
}

//                                                                                                          
//                                                                 
int check_command(string command){
    //                    
    assert(true);
    //                                                                                          
    if (command == "enter"){
        return 1;
    } else if (command == "content"){
        return 2;
    } else if (command == "stop"){
        return 3;
    } else if (command == "count"){
        return 4;
    } else if (command == "where"){
        return 5;
    } else if (command == "context"){
        return 6;
    }
    return -1;
}

//                                                        
bool is_punctuation(char a){
    //                     
    assert(true);
    //                                                                     
    return ((a >= 32 && a <= 47) || (a >= 58 && a <= 64) || (a >= 91 && a <= 96) || (a >= 123 && a <= 126) || a == '\n');
}

//                                                                                                                      
string simplify(string text){
    //                
    assert(text.length() >= 0);
    //                                                                                                                                                                              
    string output = text;
    if (output.length() == 0){ //                                            
        return output;
    }
    char first_char = output[0];
    //                                            
    while (output.length() > 1 && is_punctuation(first_char)){
        output = output.substr(1, output.length()-1); //                            
        first_char = output[0];
    }
    char last_char = output[output.length()-1];
    while (output.length() > 0 && is_punctuation(last_char)){
        output = output.substr(0, output.length()-1); //                             
        if (output.length() > 0){
            last_char = output[output.length()-1];
        }
    }
    for (unsigned int i = 0; i < output.length(); i++){
        output[i] = tolower(output[i]);
    }
    return output;
}

//                                                
int enter_command(string message){
    //                     
    assert(true);
    //                                                    
    cout << message << endl;
    string input = "";
    locale loc;
    while (!(cin >> input) || check_command(simplify(input)) == -1){ //                                                                 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input. " << message << endl;
    }
    cout << endl << "Chosen command: " << simplify(input) << endl << endl; //                                    
    return check_command(simplify(input));
}

//                                                                                                                              
void read_file (ifstream& input_file, string words [MAX_WORDS]){
    //                                   
    assert(input_file.is_open());
    //                                                                                                       
    for (int i = 0; i < MAX_WORDS; i++){
        words[i] = "";
    }
    string word = "";
    int pos = 0; //                                       
    while(input_file >> word && pos < MAX_WORDS){
        if (simplify(word) != ""){
            words[pos] = simplify(word); //                                                                                     
            pos++;
        }
    }
    if (words[0] != ""){
        cout << pos+1 << " words have been successfully extracted." << endl;
    } else {
        cout << "No words have been extracted." << endl;
    }
    input_file.clear();
    input_file.close();
    if (!input_file){ //                           
      cout << "Watch out: The input was not closed successfully." << endl << endl;
    } else {
        cout << "The input file was closed successfully." << endl << endl;
    }

}

//                                                    
void content (string words [MAX_WORDS]){
    //                     
    assert(true);
    //                                                                  
    int pos = 0;
    while (words[pos] != "" && pos < MAX_WORDS){
        cout << words[pos] << " ";
        if (pos%10 == 9){//                                          
            cout << endl;
        }
        pos++;
    }
    cout << endl << endl;
}

//                                                           
bool read_m (int& m){
    //                      
    assert(m == 0);
    //                                                                                    
    if (cin >> m){
        return true;
    }
    return false;
}

//                                                  
bool read_test_words(string test_words [MAX_WORDS], int& n){
    //                                           
    for (int i = 0; i < MAX_WORDS; i++){
        assert(test_words[i] == "");
    }
    assert(n == 0);
    //                                                                                                             
    char word [MAX_WORD_LENGTH];
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        word[i] = '\0'; //                   
    }
    char character = '\0';
    int pos = 0;
    while(cin.get(character) && n < MAX_WORDS){ //                                                                                             
        if (character != ' ' && character != '\n'){
            if (pos < MAX_WORD_LENGTH){
                word[pos] = character; //                                                                      
                pos++;
            }
        } else { //                  
            if (simplify(string(word)) != ""){ //                                           
                test_words[n] = simplify(string(word)); //                        
                n++;
            }
            pos = 0;
            for (int i = 0; i < MAX_WORD_LENGTH; i++){
                word[i] = '\0'; //                   
            }
        }
        if (character == '\n'){
            break; //                                          
        }
    }
    if (n == 0){
        cout << "No words were input." << endl << endl;
        return false;
    }
    cout << "A sequence of " << n << " words was input." << endl << endl;
    return true;
}

//                                                                                               
bool check_words(string words [MAX_WORDS], string test_words [MAX_WORDS], int i, int n){
    //                                              
    assert(i >= 0 && n > 0 && n < MAX_WORDS - i);
    //                                                     
    for (int j = 0; j < n; j++){
        if (words[i+j] != test_words[j]){
            return false; //                      
        }
    }
    return true; //                           
}

//                                                                                                                                                                                  
void count_where_context(string words [MAX_WORDS], int command){
    //                    
    assert(true);
    //                                                                                                        
    string test_words [MAX_WORDS];
    int n = 0; //                            
    int m = 0; //                                   
    int occurences = 0;
    int no_words = 0;
    int i = 0;
    bool can_proceed = true; //                                       
    if (words[0] != ""){ //                                                                                 
        while (words[no_words] != ""){
            no_words++;
        }
        no_words++;
    }
    cin.ignore(1);
    if (no_words > 0){
        if (command == 6){ //                                       
            can_proceed = read_m(m);
            if (can_proceed){ //                         
                cout << "Amount of context words requested: " << m << endl << endl;
            }
            cin.ignore(1);
        }
        if (can_proceed){ //                                              
            if (read_test_words(test_words, n)){
                switch (command){ //                                                    
                    case 4:     break;
                    case 5:     cout << "Indices: ";
                                break;
                    case 6:     cout << "Occurences:" << endl;
                                break;
                    default:    break;
                }
                while (i < no_words-n){ //                                                                                   
                    if (check_words(words, test_words, i, n)){
                        switch (command){ //                                                 
                            case 4:     break; //                                         
                            case 5:     if (occurences > 0){ //                                                    
                                            cout << ", ";
                                        }
                                        cout << i+1; //                                                
                                        break;
                            case 6:     if (i-m > 0){
                                            cout << "..."; //                                     
                                        }
                                        for (int j = max(0, i-m); j <= min(no_words-1, i+m+n-1); j++){ //                                                                       
                                            cout << words[j];
                                            if (j != min(no_words-1, i+m+n-1)){ //                                
                                                cout << " ";
                                            }
                                        }
                                        if (i+m+n-1 < no_words-1){
                                            cout << "..."; //                                   
                                        }
                                        cout << endl;
                                        break;
                            default:    break;
                        }
                        occurences++;
                    }
                    i++; //                        
                }
                if (command == 5){ //                                                                       
                    cout << endl << endl;
                } else if (command == 6){
                    cout << endl;
                }
                cout << "The sequence was found " << occurences << " times." << endl;
                if (command == 4){ //                                                 
                    cout << "There were " << no_words << " total words in the file. The sequence makes up "
                         << double(n)*double(occurences)/double(no_words)*100 << "% of the file." << endl;
                }
            }
        } else { //                             
            cout << "Cannot provide context. Amount of context words requested was not successfully read." << endl;
        }
    } else { //                                    
        cout << "Cannot count. No words have been loaded." << endl;
    }
    cout << endl; //                                            
}

//                 
int main(){
    int command = enter_command("Please enter a command (enter, content, stop, count, where, context)");
    ifstream input_file;
    string words [MAX_WORDS];
    while(command != 3){ //                                  
        switch (command){ //                                                                     
            case 1:     if (open_file (input_file)){
                            read_file(input_file, words);
                        }
                        break;
            case 2:     content(words);
                        break;
            case 4:
            case 5:
            case 6:     count_where_context(words, command);
                        break;
            default:    break;
        }
        command = enter_command("Please enter a command (enter, content, stop, count, where, context)");
    }
    cout << "Program aborted successfully." << endl;
    return 0;
}

