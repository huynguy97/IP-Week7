#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cassert>

using namespace std;

//                            
//                            

const int MAX_WORDS = 40000;

void read_file(ifstream& infile, string words [MAX_WORDS], string& filestring) {
    //              
    //            
    //                   
    //                             
    filestring = "";
    for (int i = 0; i < MAX_WORDS; i++) {
        words [i] = "";
    }
    
    char c;
    while(infile) {
        infile.get(c);
        filestring += c;
    }
    string temp_word[MAX_WORDS+1];
    int space_pos = filestring.find(' ');
    words [0] = filestring.substr(0, space_pos);
    temp_word[1] = filestring.substr(space_pos + 1);
    for(int i = 1; i < MAX_WORDS; i++) {
        space_pos = temp_word[i].find(' ');
        words [i] = temp_word[i].substr(0,space_pos);
        temp_word[i+1] = temp_word[i].substr(space_pos + 1);
        //                             
        if (temp_word[i].find(' ') == string::npos) {
            //         
            i = MAX_WORDS;
        }
    }
}

void enter_filename(ifstream& infile, string filename, string words [MAX_WORDS], string& filestring) {
    //              
    //            
    //                   
    infile.open(filename.c_str());
    if(!infile) {
        cout << "ERROR. "+ filename + " couldn't be read.\n";
    } else {
        read_file(infile, words,filestring);

        infile.clear();
        infile.close();
        //                          
        int n = 0;
        while(words [n] != "") {
            n++;
        }
        cout << n+1 << " words have been read.\n";
    }
}

void content(string words [MAX_WORDS]) {
    //              
    //            
    //                   

    for(int i = 0; i < MAX_WORDS; i++) {
        if(words [i] == "") {
            //             
            i = MAX_WORDS;
        } else {
            cout << words [i] << " ";
        }
    }
    cout << "\n";
}

void count(string sequence, string& filestring, string words [MAX_WORDS]) {
    //              
    //            
    //                   
    int count = 0;
    string sequence_string = filestring;
    while (sequence_string.find(sequence) != string::npos) {
        int sequence_pos = sequence_string.find(sequence);
        sequence_string = sequence_string.substr(sequence_pos + sequence.length());
        count++;
    }
    //                         
    int n = 0;
    while(words [n] != "") {
        n++;
    }
    double sequence_percent = (sequence.length() / n) * 100;
    cout << "The sequence appears " << count << " times. \n";
    cout << "The total number of words is: " << n << " words\n";
    cout << "The sequence makes up " << sequence_percent << "% of that." << endl;
}

void where(string sequence,string& filestring) {
    //              
    //            
    //                   
    int count = 0;
    int location[MAX_WORDS];
    string sequence_string = filestring;
    string location_string = "";
    while (sequence_string.find(sequence) != string::npos) {
        int sequence_pos = sequence_string.find(sequence) + location_string.length();
        location_string = filestring.substr(0,sequence_pos + sequence.length());
        sequence_string = sequence_string.substr(location_string.length() + sequence.length(),string::npos);
        count++;
        location[count] = sequence_pos;
    }  /*
                                                            
                                                                  
                                                                     
                
                                       
      */

    cout << "The index-positions of the sequence are: ";
    for (int i = 1; i < count; i++) {
        cout << location[i] << ", ";
    }
    cout << "\nThe number of times the sequence occurs is: " << count << endl;
}

void context(string sequence, string& filestring, string words [MAX_WORDS]) {
    //              
    //            
    //                   
    int count = 0;
    int location[MAX_WORDS];

    int m = atoi(sequence.substr(0, sequence.find_first_of(' ')).c_str());
    sequence = sequence.substr(sequence.find_first_of(' ') + 1);

    string sequence_string = filestring;
    string location_string = "";
    while (sequence_string.find(sequence) != string::npos) {
        int sequence_pos = sequence_string.find(sequence) + location_string.length();
        location_string = filestring.substr(0,sequence_pos + sequence.length());
        sequence_string = sequence_string.substr(sequence_pos - location_string.length() + sequence.length());
        count++;
        location[count] = sequence_pos;
    }
    cout << "The sequence with context is: ";
    for (int j = 1; j <= count; j++) {
        for (int i = 0; i <= sequence.length(); i++) {
            cout << filestring[location[j] + i];
        }
        cout << "\n";
    }
    cout << "\n The number of times the sequence has been found is: " << count << endl;
}

int main() {
    ifstream inputfile;
    string userInput = "";
    string userCommand = "";
    string userArg = "";
    string words [MAX_WORDS];
    string filestring = "";

    //                                           
    while(getline(cin, userInput)) {
        //                                       
        if(userInput.find(' ') != string::npos) {
            //                                            
            userCommand = userInput.substr(0, userInput.find_first_of(' '));
            userArg = userInput.substr(userInput.find_first_of(' ') + 1);
        } else {
            //                                           
            userCommand = userInput;
            userArg = "";
        }

        if(userCommand == "enter") {
            enter_filename(inputfile, userArg, words, filestring);
        } else if(userCommand == "content") {
            content(words);
        } else if(userCommand == "stop") {
            //                     
            return 0;
        } else if(userCommand == "count") {
            count(userArg, filestring, words);
        } else if(userCommand == "where") {
            where(userArg, filestring);
        } else if(userCommand == "context") {
            context(userArg,filestring,words);
        } else if(userInput == "") {
            //                                     
        } else {
            cout << "ERROR. " + userCommand + " not found\n";
        }
    }
}
