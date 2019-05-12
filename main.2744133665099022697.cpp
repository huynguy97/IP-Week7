#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

//                                                           
//                                                                                                                                             
//                                                                      

const int MAX_WORDS = 30000;

bool open_file(ifstream& infile, string filename){
    assert(!infile.is_open());

    //                           
    infile.open(filename.c_str());
    cout << filename << endl;
    return infile.is_open();
}

string read_word(ifstream& infile){
    assert(infile.is_open());

    //                                               
    string word;
    infile >> word;
    return word;
}

int sequential(string words[MAX_WORDS], int from, int to, string word){
    assert(true);

    //                                                                                                                                                           
    if(from > to){
        return (to + 1);
    }
    int  pos = from ;

    while(pos <= to && words[pos] != word){
        pos++ ;
    }
    return pos;
}

bool tally_word(string word, string words[MAX_WORDS], int freq[MAX_WORDS], int& no){
    assert(no >= 0);
    //                                                                            

    int pos = sequential(words, 0, no - 1, word);
    if(pos < no){
        freq[pos] ++;
        return true;
    }else if(pos < MAX_WORDS){
        words[pos] = word;
        freq[pos] = 1;
        no++;
        return true;
    }
    return false;
}

bool store_file(ifstream& infile, string words[MAX_WORDS], int freq[MAX_WORDS], int& no, int& read){
    assert(infile.is_open());

    //                                                                                     

    while(infile){
        tally_word(read_word(infile), words, freq, no);
        read ++;
    }
    cout << "The amount of read words is: " << read << endl;
    return infile.is_open();
}

void enter_filename(string& filename, string words[MAX_WORDS], int freq[MAX_WORDS], ifstream& infile, int& no, int& read){
    assert(true);
    //                                                                                                   

    cin.ignore(1);
    getline(cin, filename, '\n');
    if(open_file(infile, filename)){
        if(store_file(infile, words, freq, no, read)){
            no --;//                                                                                                                                                                                     
            cout << "File opened and stored in an array" << endl;
        }else{
            cout << "The file was not stored succesfully" << endl;
        }
    }else{
       cout << "everything went to shit" << endl;
    }
    infile.clear();
    infile.close();
}

void print_lists(string words[MAX_WORDS], int freq[MAX_WORDS], int& no){
    assert(no >= 0);
    //                                                       
    for(int i = 0; i < no; i++){
        cout << words[i] << " : " << freq[i] << endl;
    }
}

int count_sequence(string& filename, ifstream& infile, string& word_sequence, string word, string first_word, string possible_sequence, int sequence_length, int& sequence_amount){
    assert(true);
    //             

   infile.open(filename.c_str());
   while(infile){
        word = read_word(infile);
        if(word == first_word){
            possible_sequence += word;
            for(int j= 1; j<= sequence_length; j++){
                if(j <= sequence_length){
                    possible_sequence += ' ';
                }
                word = read_word(infile);
                possible_sequence += word;
            }
            if(possible_sequence == word_sequence){
                sequence_amount ++;
            }
            possible_sequence = "";
        }
    }
    infile.clear();
    infile.close();

   return sequence_amount;
}

int get_sequence(string& word_sequence, string& first_word, int sequence_length){
    char c;
    cin.ignore(1);
    getline(cin, word_sequence, '\n');

    for(int i = 0; i< word_sequence.length(); i++){
        c = word_sequence.at(i);
        if(c == ' '){
            sequence_length ++;
        }
        if(sequence_length == 0){
            first_word += c;
        }
    }
    return sequence_length;
}

void counting(string& filename, ifstream& infile, int& read){
    assert(true);
    //                                                                                     
    //                                                                                                                                       

    string word_sequence;
    string first_word;
    string word;
    string possible_sequence;
    int sequence_length = 0;
    int sequence_amount = 0;

    sequence_length = get_sequence(word_sequence, first_word, sequence_length);
    sequence_amount = count_sequence(filename, infile,word_sequence, word, first_word, possible_sequence, sequence_length, sequence_amount);
    cout << sequence_amount << ", " << read << ", " << "percentage = " <<sequence_amount << " * " << sequence_length + 1 << " / " << read << " * 100 = " << ((sequence_amount * sequence_length + 1)/read)*100 << endl;
    //                                                                                                                                                                                

}

void sequence_positions(int arr[MAX_WORDS], int& arr_length, string word_sequence, string& filename, ifstream& infile, string first_word, int sequence_length){
    assert(arr_length >= 0);
    //                                                                                         

    string word;
    string possible_sequence;
    int index = 0;
    int i = 0;
    infile.open(filename.c_str());

    //                                                                                                                                        
    infile.clear();

    while(infile){
        word = read_word(infile);
        index ++;
        if(word == first_word){
            possible_sequence += word;
            for(int j= 1; j<= sequence_length; j++){
                if(j <= sequence_length){
                    possible_sequence += ' ';
                }
                word = read_word(infile);
                possible_sequence += word;

            }
            if(possible_sequence == word_sequence){
                arr[i] = index;
                arr_length ++;
                i++;
            }
            possible_sequence = "";
        }
    }
    infile.clear();
    infile.close();
}

void where(ifstream& infile, string filename){
    assert(filename != "");

    //                                                                                                                                        

    int arr[MAX_WORDS];
    infile.open(filename.c_str());
    string word_sequence;
    string first_word;
    int sequence_length = 0;
    int arr_length = 0;

    sequence_length = get_sequence(word_sequence, first_word, sequence_length);
    sequence_positions(arr, arr_length, word_sequence, filename, infile, first_word, sequence_length);
    for(int i = 0; i < arr_length; i++){
        cout << "index: " << arr[i] << ", ";
    }
    cout << arr_length << " ocurrences" << endl;
}

void take_commands(string& filename, string command, string words[MAX_WORDS], int freq[MAX_WORDS], ifstream& infile, int& no, bool& stop, int& read){
    assert(true);

    //                                                                                 
    bool wrong = false;
    if(command == "stop"){
        stop = true;
    }else if(command == "enter"){
        enter_filename(filename, words, freq, infile, no, read);
    }else if(command == "content"){
        print_lists(words, freq, no);
    }else if(command == "count"){
        counting(filename, infile, read);
    }else if(command == "where"){
        where(infile, filename);
    }else if(command == "context"){
        cout << "Not yet implemented due to the constant crashes of CodeBlocks, sorry for that" << endl;
    }else{
        cout << "Please give a proper command" << endl;
        wrong = true;
    }
    if(!stop && !wrong){
        cout << "Please give another command" << endl;
    }
    wrong = false;
}

void give_command(string& filename, string words[MAX_WORDS], int freq[MAX_WORDS], string command, ifstream& infile, int& no, bool& stop, int& read){
    assert(true);

    //                                                                                        
    cout << "Please give a command" << endl;
    while(!stop){
        cin >> command;
        take_commands(filename, command, words, freq, infile, no, stop, read);
    }
}

void init(){
    assert(true);
    /*                                                                                                
                                                                                                               
                                                                                                                             
    */

    ifstream infile;
    string words[MAX_WORDS];
    string command;
    string filename;
    int freq[MAX_WORDS];
    int no = 0;
    int read = 0;
    bool stop = false;
    give_command(filename, words, freq, command, infile, no, stop, read);
}

int main()
{
    init();
    return 0;
}

