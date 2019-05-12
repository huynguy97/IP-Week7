/*                                                                    
                                                                      
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;
const int MAX_FILENAME_LENGTH = 80;
string saved_words[MAX_WORDS];
enum inString { Sfilename, Scontent, Sstop, Scount, Swhere, Scontext, Sfalse}; //                          

/*                                                               
 */
inString hash_input (string const& input) {
    if (input == "filename"|| input == "Filename") return Sfilename;
    if (input == "content" || input == "Content")  return Scontent;
    if (input == "stop"    || input == "Stop")     return Sstop;
    if (input == "count"   || input == "Count")    return Scount;
    if (input == "where"   || input == "Where")    return Swhere;
    if (input == "context" || input == "Context")  return Scontext;
    else return Sfalse;
}

int read_words(ifstream& in) {
//              
    assert(in.is_open());

/*               
                                           
 */

    int count = 0;
    string word;

    while (in >> word) {
        saved_words[count] = word;
        ++count;
    }

    return count;
}

int filename(ifstream& infile) {
//              
    assert(!infile.is_open());

/*               
                                           
 */

    char filename[MAX_FILENAME_LENGTH] = "";
    cout << "What is your filename called?" << endl;
    cin.get();
    cin.getline(filename, MAX_FILENAME_LENGTH);
    infile.open(filename);

    if (infile.is_open()) {
        int words = read_words(infile);
        cout << "Number of words read: " << words << '\n';
        infile.close();
        return words;
    } else {
        cout << "Failed to open file" << '\n';
        return 0;
    }
}

void content(int number) {
//              
    assert(number >= 0 && number < MAX_WORDS);

/*               
                                           
 */
    for (int i = 0; i < number; i++) {
        cout << saved_words[i] << '\n';
    }
}

void count(ifstream& infile) {
//              
    assert(infile.is_open());

/*               
                                      
 */
    int iterate = 0;
    int yterate = 0;
    char sentence[MAX_WORDS];
    char counted_words[MAX_WORDS][MAX_CHARS];
    cout << "What is the word sequence you want to count?" << '\n';
    cin.get();
    cin.getline(sentence, 80);
    int counter = strlen(sentence);

    for (int i = 0; i < counter; i++) {
        if (sentence[i] == ' ') {
            yterate++;
            iterate = 0;
        } else {
            counted_words[yterate][iterate] = sentence[i];
            iterate++;
        }
    }
    for (int i = 0; i < yterate; i++) {
        for (int j = 0; j < iterate; j++) {
            cout << counted_words[i][j] << '\n';
        }
    }
}

void where(ifstream& infile) {
    cout << "Coming soon" << '\n';
}

void context(ifstream& infile) {
    cout << "Coming soon" << '\n';
}

/*                           
 */
void inputMenu() {
    ifstream infile;
    string words [MAX_WORDS];
    string input = "";
    int number = 0;
    while (input != "stop" && input != "Stop") {
        cout << "What is your command" << endl;
        cin >> input;
        switch (hash_input(input)) {
            case Sfilename  : number = filename(infile) ; break;
            case Scontent   : content(number)           ; break;
            case Sstop      :                           ; break;
            case Scount     : count(infile)             ; break;
            case Swhere     : where(infile)             ; break;
            case Scontext   : context(infile)           ; break;
            case Sfalse     : cout << input << " is not a valid input" << endl; break;
        }
    }
    infile.clear();
    infile.close();
}

int main() {
    inputMenu();
    //                                                             
}

