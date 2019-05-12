#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

const int MAX_WORDS = 10000;

//                                                                           
//                                                                           
string first_word(string& input)
{
    //              
    assert(true);
    /*               
                                                                                   
                                                                                  
                                          
    */
    string output = "";
    for(int i=0;i<input.length();i++){
        if (input[i] == ' '){
            //                                 
            input.erase(0,output.length()+1);
            return output;
        } else{
            output += input[i];
        }
    }
    //                                 
    input.erase(0,output.length()+1);
    return output;
}

//                                       
bool open_file(ifstream& input_file, string filename)
{
    //             
    assert(true);
    /*               
                                                                      
                              
    */
    input_file.open(filename.c_str());
    if(input_file.is_open()){
        return true;
    } else{
        return false;
    }
}

//                               
bool read_word(ifstream& input_file, string words[MAX_WORDS], int& words_read)
{
    //             
    assert(input_file.is_open());
    /*               
                                                                                  
                               
    */
    input_file >> words[words_read];
    return input_file;
}

//                                                              
int sequential_search(string words[MAX_WORDS], int from, int to, string search_value)
{
    //             
    assert(from>=0);
    assert(to>=0);
    assert(to>=from);
    /*               
                                                                    
                                                                          
    */
    int position = from;
    while(position <= to && words[position] != search_value){
        position++;
    }
    return position;
}

//                                                                         
int process_file(string filename, string words[MAX_WORDS])
{
    //             
    assert(true);
    /*               
                                                               
                                                          
                                         
    */
    ifstream input_file;
    if(!open_file(input_file, filename)){
        cout << "Unable to open file" << endl;
        return -1;
    }
    int words_read = 0;
    while(words_read < MAX_WORDS && read_word(input_file, words, words_read)){
        words_read++;
    }
    input_file.close();
    return words_read;
}

//                                                 
void show_words(string words[MAX_WORDS], int words_read)
{
    //             
    assert(true);
    /*               
                                                   
    */
    for(int i=0;i<words_read;i++){
        cout << words[i] << endl;
    }
}

//                                                               
//                                                                                   
void count_words(string user_input, string words[MAX_WORDS], int words_read)
{
    //             
    assert(true);
    /*               
                                                                            
                                                 
    */
    //                                                                                    
    bool match = false;
    //                                  
    int match_counter = 0;
    //                                                                           
    int counter = 0;
    //                                                                                    
    int old_position = 0;
    int position = 0;
    //                                                                
    int word_pos = 0;
    //                                                
    string word = "";
    //                                            
    while(word_pos <= words_read){
        //                                          
        position = user_input.find(" ", old_position);
        if(position == -1){
            position = user_input.length();
        }
        word = user_input.substr(old_position, position);
        //                                                                   
        //                                   
        old_position = position+1;
        //                                     
        word_pos = sequential_search(words, word_pos, words_read, word);
        //                                                       
        if(word_pos < words_read){
            match = true;
        }
        //                                        
        while(word_pos < words_read && position != user_input.length()){
            //                                                                         
            //                   
            counter++;
            //                                         
            position = user_input.find(" ", old_position);
            if(position == -1){
                position = user_input.length();
            }
            word = user_input.substr(old_position, position);
            old_position = position+1;
            //                                          
            if(words[word_pos+counter]!=word){
                match = false;
            }
        }
        //                                               
        if(match){
            match_counter++;
        }
        //                                                
        position = 0;
        old_position = 0;
        match = false;
        word_pos++;
    }
    //                                                      
    //                                                                   
    int search_length = 0;
    while(position != -1){
        position = user_input.find(" ", position + 1);
        search_length++;
    }
    //                 
    cout << "Amount of matches: " << match_counter << endl;
    cout << "Total amount of words: " << words_read << endl;
    cout << "Percentage of text that matched: " << ((double)match_counter*search_length/(double)words_read) * 100 << endl;
    return;
}

//                                                                              

//                                                         
int main()
{
    string user_input = "";
    string action = "";
    string words[MAX_WORDS];
    int words_read = 0;
    //                                             
    while(action != "stop"){
        cout << "Please enter your command (enter/content/count/stop)" << endl;
        getline(cin, user_input);
        action = first_word(user_input);
        if(action == "enter"){
            words_read = process_file(user_input, words);
            if(words_read != -1){
                cout << words_read << " words read from file." << endl;
            }
        } else if(action == "content"){
            show_words(words, words_read);
        } else if(action == "count"){
            count_words(user_input, words, words_read);
        } else if(action == "stop"){
        } else{
            cout << "Input not recognized" << endl;
        }
    }
}

