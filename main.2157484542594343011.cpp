#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
                                      
                          
                            
 */

enum UserCommand { Stop, Enter, Content, Count, Where, Context, Skip };

string* put_words_in_array(ifstream& infile, int& words) {
    //                                                                        

    words = 0;

    char c;
    infile >> noskipws; //                                                                                         

    while (infile >> c) { //                                          
        if (c == '\r') { //                                                         
            infile >> c;
        }
        if (c == ' ' || c == '\n') {
            ++words;
        }
    }
    if (c != ' ' && c != '\n') //                                                                                      
        ++words;

    string* text = new string[words], word;

    //                                                                   
    infile.clear();
    infile.seekg(0,ios::beg);

    //                                          
    words = 0;

    infile >> noskipws; //           

    while (infile >> c) {
        if (c == '\r') {
            infile >> c;
        }
        if (c == ' ' || c == '\n') { //                                                                             
            text[words] = word;

            ++words;
            word = "";
        } else {
            word += c; //                                         
        }
    }
    if (word.length() > 0) { //                                                                                                   
        text[words++] = word;
    }

    return text;
}

void commandEnter(string*& text, int& wordCount, string*& args, int argsLength) {
    if (argsLength == 1) {
        cout << "Not enough arguments specified!" << endl;
    } else {
        string filename;
        for (int i = 1; i < argsLength; ++i) //                                              
            filename += (i == 1 ? "" : " ") + args[i];

        ifstream infile(filename);

        if (infile.is_open()) {
            delete[] text; //                            
            
            text = put_words_in_array(infile, wordCount); //                                           

            cout << "Successfully opened file. Found " << wordCount << (wordCount == 1 ? " word." : " words.") << endl;

            infile.close();
        } else {
            cout << "Could not open file!" << endl;
        }

    }
}

void commandContent(string*& text, int wordCount) {
    if (wordCount == 0) {
        cout << "No file currently open." << endl;
    } else {
        for (int i = 0; i < wordCount; ++i) {
            cout << (i == 0 ? "" : ", ") << text[i]; //                                                                   
        }
        cout << endl;
    }
}

void commandCount(string*& text, int wordCount, string*& args, int argsLength) {
    if (argsLength == 1) {
        cout << "Not enough arguments specified!" << endl;
    } else if (wordCount == 0) {
        cout << "No file currently open." << endl;
    } else {
        int count = 0;
        for (int i = 0; i <= wordCount - argsLength; ++i) {
            bool match = true;
            for (int j = 1;
                 j < argsLength; ++j) { //                                                       
                if (text[i + j - 1] != args[j]) {
                    match = false;
                }
            }
            if (match) {
                ++count;
            }
        }

        cout << "Found " << count << " occurences in " << wordCount << " words (" << (double) count / wordCount * 100 << "%)" << endl;
    }
}

void commandWhere(string*& text, int wordCount, string*& args, int argsLength) {
    if (argsLength == 1) {
        cout << "Not enough arguments specified!" << endl;
    } else if (wordCount == 0) {
        cout << "No file currently open." << endl;
    } else {
        int count = 0;

        cout << "Indices: ";
        for (int i = 0; i <= wordCount - argsLength + 1; ++i) {
            bool match = true;
            for (int j = 1; j < argsLength; ++j) { //               
                if (text[i + j - 1] != args[j]) {
                    match = false;
                }
            }
            if (match) {
                ++count;
                cout << i + 1 << ", ";
            }
        }
        cout << endl << "Total found: " << count << endl;
    }
}

void commandContext(string*& text, int wordCount, string*& args, int argsLength) {
    if (argsLength <= 2) {
        cout << "Not enough arguments specified!" << endl;
    } else if (wordCount == 0) {
        cout << "No file currently open." << endl;
    } else {
        int m;

        try {
            m = stoi(args[1]); //                  
        } catch (...) {
            m = -1; //                                                                           
        }

        if (m >= 0) {
            int count = 0;

            cout << "Found: ";
            for (int i = 0; i <= wordCount - argsLength + 2; ++i) { //                                                                                              
                bool match = true;
                for (int j = 2; j < argsLength; ++j) { //              
                    if (text[i + j - 2] != args[j]) {
                        match = false;
                    }
                }
                if (match) {
                    ++count;

                    int from = max(i - m, 0), to = min(i + argsLength - 2 + m, wordCount); //                                
                    for (int j = from; j < to; ++j) {
                        cout << (j == from ? "" : " ") << text[j];
                    }
                    cout << ", ";
                }
            }

            cout << endl << "Total found: " << count << endl;
        } else {
            cout << "Invalid m!" << endl;
        }
    }
}

UserCommand executeUserCommand(string *&text, int &wordCount, string *args, int argsLength) {
    if (argsLength == 0) {
        cout << "Not enough arguments specified!" << endl;
        return Skip; //                                                             
    }

    string command = args[0];

    //                                           
    if (command == "stop") {
        return Stop;
    } else if (command == "enter") {
        commandEnter(text, wordCount, args, argsLength);
        return Enter;
    } else if (command == "content") {
        commandContent(text, wordCount);
        return Content;
    } else if (command == "count") {
        commandCount(text, wordCount, args, argsLength);
        return Count;
    } else if (command == "where") {
        commandWhere(text, wordCount, args, argsLength);
        return Where;
    } else if (command == "context") {
        commandContext(text, wordCount, args, argsLength);
        return Context;
    }
    cout << "Invalid command!" << endl;
    return Skip;
}

int main() {
    int wordCount = 0;
    string* text = nullptr;

    UserCommand command;
    do {
        cout << "Please enter a command (stop, enter, content, count, where, context):" << endl;

        string line;
        getline(cin, line);

        //                                      
        string args[line.length()], arg;
        int argsLength = 0;

        for (char c : line) {
            if (c != ' ') {
                arg += c;
            } else if (arg.length() > 0) {
                args[argsLength++] = arg;
                arg = "";
            }
        }
        if (arg.length() > 0)
            args[argsLength++] = arg;

        command = executeUserCommand(text, wordCount, args, argsLength); //                                                                      
    } while (command != Stop); //                                                        

    delete[] text; //                             

    return 0;
}

