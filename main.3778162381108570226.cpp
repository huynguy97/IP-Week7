//                         
//                            

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

const int MAX_CHARS = 50;
const int MAX_WORDS = 30000;

//                           
const int MAX_CMD = 80;

//                              
typedef char COMMAND[MAX_CMD];

//                           
const COMMAND ENTER_COMMAND = {'e','n','t','e','r',0};
const COMMAND CONTENT_COMMAND = {'c','o','n','t','e','n','t',0};
const COMMAND STOP_COMMAND = {'s','t','o','p',0};
const COMMAND COUNT_COMMAND = {'c','o','u','n','t',0};
const COMMAND WHERE_COMMAND = {'w','h','e','r','e',0};
const COMMAND CONTEXT_COMMAND = {'c','o','n','t','e','x','t',0};

//                                 
bool cmp_str(const char str1[],const char str2[]){
    //                
    assert(true);
    //                 
    //                                                                       
    int c = 0;
    while(str1[c] == str2[c] && str1[c] != 0 && str2[c++] != 0);
    if(str1[c] == str2[c])
    {
        return true;
    }
    return false;
}

//                                           
void show_words(char words[MAX_WORDS][MAX_CHARS], int no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                 
    for(int i = 0; i < no_of_words;i++)
    {
        int c = 0;
        while(c < MAX_CHARS && words[i][c] != 0){
            cout << words[i][c++];
        }
        cout << ' ';
    }
    cout << '\n';
}

//                      
void show_word(char word[MAX_CHARS]) {
    //                
    assert(true);
    //                 
    //                              
    int c = 0;
    while(c < MAX_CHARS && word[c] != 0){
        cout << word[c++];
    }
}

//                                                            
int find_word(char data[MAX_WORDS][MAX_CHARS], char word[MAX_CHARS],int start, int stop) {
    //                
    assert(start >= 0 && start < stop && stop < MAX_WORDS);
    //                 
    //                                                       
    for(int i = start;i < stop + 1; i++)
    {
        int c = 0;
        while(data[i][c] == word[c] && data[i][c] != 0)
            c++;
        if(data[i][c] == word[c])
        {
            return i;
        }
    }
    return stop;
}

//                                  
bool append_element(char data[MAX_WORDS][MAX_CHARS], int& no_of_words, char new_word[MAX_CHARS]) {
    //               
    assert(no_of_words != 0);
    //                 
    //                                                                             
    if(no_of_words < MAX_WORDS)
    {
        for (int i = 0; i < MAX_CHARS; i++)
            data[no_of_words][i] = new_word[i];

        no_of_words++;
        return true;
    }
    return false;
}

//                                             
bool read_word(ifstream& infile, char word[MAX_CHARS]){
    //                
    assert(infile.is_open());
    //                 
    //                                                    
    infile >> word;
    return infile;
}

//                                                              
int read_words (ifstream& infile,char words[MAX_WORDS][MAX_CHARS]){
    //                
    assert(infile.is_open());
    //                 
    //                                                              
    int no_of_words = 0;
    char next_word [MAX_CHARS];
    while(read_word(infile,next_word) &&
        append_element(words,no_of_words,next_word) &&
        no_of_words < MAX_WORDS);
    return no_of_words;
}

//                                                                                          
//                                                   
bool PROCESS_command(COMMAND command, char argument[]){
    //                
    assert(true);
    //                 
    //                                        
    int c = 0;
    while (c < MAX_CMD && command[c] != ' ' && command[c] != 0){
        argument[c] = command[c];
        c++;
    }
    argument[c] = 0;

    if(command[c] == ' '){
        c++;
    }

    const int pos = c;

    while (c < MAX_CMD){
        command[c - pos] = command[c];
        c++;
    }
    return true;
}

//                                                     
void show_commands(int no_of_words)
{
    //                
    assert(no_of_words != 0);
    //                 
    //                                                       
    if(no_of_words == 0){
        cout << "LIST OF COMMANDS:" << endl;
        cout << "Please use the enter command to load a file" << endl;
        cout << "enter [filename]" << endl;
        cout << "stop" << endl;
    }
    else{
        cout << "LIST OF COMMANDS:" << endl;
        cout << "enter [filename]" << endl;
        cout << "content" << endl;
        cout << "stop" << endl;
        cout << "count [word1] [word2] ... [word n]" << endl;
        cout << "where [word1] [word2] ... [word n]" << endl;
        cout << "context [m] [word1] [word2] ... [word n]" << endl;
    }
}

//                                                                         
int count_words (COMMAND command){
    //                
    assert(true);
    //                 
    //                                                 
    if(command[0] == 0)
        return 0;

    int c = 0;
    int cnt = 0;
    while (c < MAX_CMD && command[c] != 0){
        if (command[c] == ' '){
            cnt++;
        }
        c++;
    }
    return cnt + 1;
}

//                                               
bool open_file (ifstream &infile,char filename[MAX_CMD]){
    //                
    assert(!infile.is_open())
    //                 
    //                     
    infile.open(filename);
    return infile.is_open();
}

//                     
void enter_command(char filename[MAX_CMD], char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                          
    ifstream file;
    if(open_file(file,filename)){
        no_of_words = read_words(file,words);
        file.close();
        show_words(words,no_of_words);
        cout << "There were " << no_of_words << " words read and stored" << endl;
        return;
    }
    cout << "Could not open file." << endl;
}

//                       
void content_command(char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                            
    if(no_of_words > 0 && no_of_words <= MAX_WORDS)
    {
        show_words(words,no_of_words);
        return;
    }
    cout << "No words to read, please read a file first." << endl;
    return;
}

//                     
void count_command(COMMAND command, char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                          
    int sen_size = count_words(command);
    //                            
    if(sen_size < 1){
        cout << "Invalid input, no arguments given." << endl;
        return;
    }

    char sentence [sen_size][MAX_CHARS];

    for(int i = 0; i < sen_size; i++){
        PROCESS_command(command,sentence[i]);
    }

    //                   
    int cnt = 0;

    int start = find_word(words,sentence[0],0,no_of_words);

    while(start != no_of_words){
        if(start++ + sen_size < no_of_words){
            int c = 1;

            while(c < sen_size && cmp_str(sentence[c],words[start + c - 1])){
                c++;
            }

            if(c == sen_size){
                cnt++;
            }
        }
        start = find_word(words,sentence[0],start,no_of_words);
    }

    cout << cnt << " Matches found" << endl;
    cout << "With " << no_of_words << " words in the text" << endl;
    double per = (static_cast<double>(cnt) * static_cast<double>(sen_size) * 100)/static_cast<double>(no_of_words);
    cout << "So " << per << " % contained this array of words" << endl;
}

//                 
void where_command(COMMAND command, char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                          
    int sen_size = count_words(command);
    //                               
    if(sen_size < 1){
        cout << "Invalid input, no arguments given." << endl;
        return;
    }

    char sentence [sen_size][MAX_CHARS];

    for(int i = 0; i < sen_size; i++){
        PROCESS_command(command,sentence[i]);
    }

    int start = find_word(words,sentence[0],0,no_of_words);
    cout << "Sentences found at: " << endl;

    while(start != no_of_words){
        cout << start++ << '\t';
        start = find_word(words,sentence[0],start,no_of_words);
    }
    cout << endl;
}

//                                                       
int word_to_int(const char word[]) {
    //                
    assert(true);
    //                 
    //                                               
    int word_size = 0;
    while (word[word_size++] != 0) ;
    word_size -=1;

    int value = 0;

    for (int i = 0; i < word_size;i++){
        value += ((int)word[i] - 48) * pow(10,word_size - i - 1);
    }
    if(value < 0)
        return 0;
    return value;
}

//                   
void context_command(COMMAND command, char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                            
    int sen_size = count_words(command);
    //                               
    if(sen_size < 2){
        cout << "Invalid input, no arguments given." << endl;
        return;
    }

    //             
    char m_word[MAX_CHARS];
    PROCESS_command(command,m_word);

    int m = word_to_int(m_word);

    //                
    char sentence [sen_size][MAX_CHARS];

    for(int i = 0; i < sen_size; i++){
        PROCESS_command(command,sentence[i]);
    }

    cout << "Context: " << endl;

    //                   
    int cnt = 0;

    int start = find_word(words,sentence[0],0,no_of_words);

    //                                                        
    while(start != no_of_words){
        for(int i = max(start - m,0); i < min(start + m + 1,no_of_words);i++) {
            show_word(words[i]);
            cout << '\t';
        }
        cout << endl;
        cnt++;
        start++;
        start = find_word(words,sentence[0],start,no_of_words);
    }
    cout << "And " << cnt << " such occurances found." << endl;
}

//                                         
bool GET_command(char words [MAX_WORDS][MAX_CHARS], int& no_of_words) {
    //                
    assert(no_of_words != 0);
    //                 
    //                                                        
    //                                     
    char command[MAX_CMD];
    cin.getline(command,MAX_CMD,'\n');

    //                                              
    char main_command[MAX_CMD];
    PROCESS_command(command, main_command);

    if(cmp_str(main_command,ENTER_COMMAND)) {
        enter_command(command,words,no_of_words);
        return true;
    }
    else if (no_of_words != 0){
        if(cmp_str(main_command,CONTENT_COMMAND)){
            content_command(words,no_of_words);
            return true;
        }
        else if(cmp_str(main_command,STOP_COMMAND)){
            cout << "Quitting" << endl;
            return false;
        }
        else if(cmp_str(main_command,COUNT_COMMAND)){
            count_command(command,words,no_of_words);
            return true;
        }
        else if(cmp_str(main_command,WHERE_COMMAND)){
            where_command(command,words,no_of_words);
            return true;
        }
        else if(cmp_str(main_command,CONTEXT_COMMAND)){
            context_command(command,words,no_of_words);
            return true;
        }
    }

    cout << "Command not found, try again." << endl;
    return true;
}

//         
int main()
{
    //                      
    char words[MAX_WORDS][MAX_CHARS];
    int no_of_words = 0;

    show_commands(no_of_words);
    while(GET_command(words,no_of_words))
    {
        show_commands(no_of_words);
    };

    return 0;
}

