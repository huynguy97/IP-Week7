#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
//        
//         
using namespace std;
typedef string Command;
typedef string Filename;
typedef string Word;
const int MAX_WORDS = 30000;
const int MAX_FREQS = 30000;
string words[MAX_WORDS] = {};
string wordseq[MAX_WORDS] = {};
string freqs[MAX_FREQS] = {};
enum CommandEnum {enter, content, countw, where, context, stop};

Word read_word(ifstream& infile) {
    //               
    assert(infile.is_open());
    //               
    //                         
    Word word = "";
    infile >> word;
    return word;
}

bool read_file(ifstream& infile) {
    //              
    assert(true);
    //               
    //                                                        
    return infile.is_open();
}

CommandEnum command_to_enum(Command command) {
    if(command == "enter") return enter;
    if(command == "content") return content;
    if(command == "count") return countw;
    if(command == "where") return where;
    if(command == "context") return context;
    if(command == "stop") return stop;
}

int enter_comm(Filename fn, ifstream& infile, string words[MAX_WORDS]) {
    int i = 0;
    getline(cin, fn);
    infile.open(fn.c_str());
    if(read_file(infile)) {
        while(infile && i < MAX_WORDS) {
            if(i < MAX_WORDS)
                words[i] = read_word(infile);
            i++;
        }
    }
    else {
        cout << "Error. Failed to read file." << endl;
        return -1;
    }
    infile.close();
    return i-1;
}

void content_comm(string words[MAX_WORDS], int len) {
    //               
    assert(len >= 0);
    //                
    //                            
    if(len == 0)
        cout << endl;
    for(int i = 0; i < len; i++)
        cout << words[i] << endl;
}

int find_occurrence(string words[MAX_WORDS], string wordseq[MAX_WORDS], int wlength, int seqlength, int start) {
    assert (wlength>seqlength);
    for(int i = start; i < wlength-seqlength; i++) {
        int j = 0;
        while(words[i+j]==wordseq[j])
            if (j<seqlength-1)
                j++;
            else
                return i;
        }
    return -1;
}

void count_comm(string words[MAX_WORDS], string wordseq[MAX_WORDS], int wlength, int seqlength){
    bool not_finished=true;
    int start_at=0;
    double frequency=0;
    while (not_finished){
        if (find_occurrence(words, wordseq, wlength, seqlength, start_at)!=-1){
            frequency++;
            start_at=find_occurrence(words, wordseq, wlength, seqlength, start_at)+1;
        }
        else
            not_finished=false;
    }
    cout << "The number of found occurrences is " << frequency << endl;
    cout << "The total number of words in the document was " << wlength << endl;
    cout << "This is " << ((frequency/wlength)*100) << "%" << endl;
}

void where_comm(string words[MAX_WORDS], string wordseq[MAX_WORDS], int wlength, int seqlength) {
    int start_at=0;
    int frequency=0;
    bool not_finished=true;
    while (not_finished){
        if (find_occurrence(words, wordseq, wlength, seqlength, start_at)!=-1){
            cout << "found occurrence at index position: " << find_occurrence(words, wordseq, wlength, seqlength, start_at) << endl;
            frequency++;
            start_at=find_occurrence(words, wordseq, wlength, seqlength, start_at)+1;
        }
        else
            not_finished=false;
    }
    cout << "The number of found occurrences is " << frequency << endl;
}

void context_comm(string words[MAX_WORDS], string wordseq[MAX_WORDS], int wlength, int seqlength, int m){
    int start_at=0;
    int frequency=0;
    bool not_finished=true;
    while (not_finished){
        if (find_occurrence(words, wordseq, wlength, seqlength, start_at)!=-1){
            for (int i=find_occurrence(words, wordseq, wlength, seqlength, start_at)-m; i<find_occurrence(words, wordseq, wlength, seqlength, start_at)+m; i++)
                cout << words[i];
            cout << endl;
            frequency++;
            start_at=find_occurrence(words, wordseq, wlength, seqlength, start_at)+1;
        }
        else
            not_finished=false;
    }
    cout << "The number of found occurrences is " << frequency << endl;
}

void stop_comm() {
    cout << "program terminated" << endl;
}

void input_command() {
    //               
    assert(true);
    //                
    //                                                                            
    Command comm = "";
    Filename fn = "";
    ifstream infile;
    int currword = 0;
    int numwords = 0;
    int m = 0;
    char c = 'c';
    while(comm != "stop") {
        cout << "command: ";
        cin >> comm;
        CommandEnum commenum = command_to_enum(comm);
        switch(commenum) {
        case enter:
            getline(cin, fn, ' ');
            numwords = enter_comm(fn, infile, words);
            if(numwords >= 0)
                cout << "Read " << numwords << " words" << endl;
            break;
        case content:
            content_comm(words, numwords);
            break;
        case countw:
            cin.get(c);
            while(c != '\n') {
                cin >> wordseq[currword];
                cin.get(c);
                currword++;
            }
            cout << "numwords: " << numwords << endl;
            cout  << "currword: " << currword << endl;
            count_comm(words, wordseq, numwords, currword);
            break;
        case where:
            where_comm(words, wordseq, numwords, currword);
            break;
        case context:
            /*           
                    
                                   
                                                
                        
                                       
                        
                                  
                    
             
                       
                              
                                         
                           
                           
             
                                                                
                  */
        case stop:
            stop_comm();
            break;
        default:
            cout << "Unknown command. Valid commands are enter, content, count, where, context and stop." << endl;
        }
    }
}

int main()
{
    input_command();
}

