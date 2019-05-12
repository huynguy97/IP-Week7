#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

//                                                      
//                                                  

const int MAX_WORDS = 50000;
const int MAX_WORDS_SEQUENCE = 100;

void print_command(string command, string result)
{
    cout << "Type \"" << command << "\" to " << result << "\n";
}

void ask_for_input(string& input)
{
//               
    assert(true);
/*                
                           
*/
    cout << '\n';
    print_command("enter [filename]", "read a file");
    print_command("content", "display the content of the file");
    print_command("count [word1 ... wordn]", "count the number of occurrences of this word sequence");
    print_command("where [word1 ... wordn]", "display the positions of the occurrences of this word sequence");
    print_command("context [m] [word1 ... wordn]", "display all occurrences of this word sequence including the m words preceding and the m words following it");
    print_command("stop", "terminate");
    cin >> input;
}

bool open_file(ifstream& fin)
{
//               
    assert(!fin.is_open());
/*                
                                                                               
                            
*/
    char c;
    cin >> c;
    string filename = "";
    while (c != '\n') {
        filename += c;
        cin.get(c);
    }

    fin.open(filename.c_str());

    return fin.good();
}

int read_words(ifstream& fin, string words[MAX_WORDS])
{
//               
    assert(fin.is_open());
/*                
                                                    
                                                 
*/
    int i = 0;
    do {
        fin >> words[i];
        i++;
    } while (fin);
    return i - 1;
}

void enter(string words[MAX_WORDS], int& word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                                                                  
                                   
*/
    ifstream fin;
    if (open_file(fin)) {
        word_amt = read_words(fin, words);
        cout << "There are " << word_amt << " words in the file\n";
        fin.close();
    }
    else
        cout << "The file could not be opened\n";
}

void print(string words[MAX_WORDS], int word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                      
*/
    for (int i = 0; i < word_amt; i++) {
        cout << words[i] << '\n';
    }
}

int read_word_sequence(string words[MAX_WORDS_SEQUENCE])
{
//               
    assert(true);
/*                
                                                                    
                                     
*/
    int i = 0;
    char c;
    cin.get();
    cin.get(c);
    words[0] = "";
    while (c != '\n') {
        if (c != ' ')
            words[i] += c;
        else if (words[i] != "") {
            i++;
            words[i] = "";
        }

        cin.get(c);
    }

    if (words[i] == "")
        return i;
    else
        return i + 1;
}

int count_words(string words[MAX_WORDS], int word_amt, string word_sequence[MAX_WORDS_SEQUENCE], int word_sequence_amt)
{
//               
    assert(word_amt >= 0 && word_sequence_amt >= 0);
/*                
                                                                                    
*/
    int word_count = 0;
    for (int i = 0; i < word_amt; i++) {
        if (words[i] == word_sequence[0]) {
            bool sequence = true;
            for (int j = 1; j < word_sequence_amt && sequence; j++) {
                sequence = (i + j < word_amt) && (words[i+j] == word_sequence[j]);
            }
            if (sequence)
                word_count++;
        }
    }
    return word_count;
}

void execute_count(string words[MAX_WORDS], int word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                                                           
                                                                                                 
*/
    string word_sequence[MAX_WORDS_SEQUENCE];
    int word_sequence_amt = read_word_sequence(word_sequence);
    int word_count = count_words(words, word_amt, word_sequence, word_sequence_amt);
    cout << "There are " << word_count << " occurrences of the word sequence \"" << word_sequence[0];
    for (int i = 1; i < word_sequence_amt; i++) {
        cout << ' ' << word_sequence[i];
    }
    cout << "\"\nThere are " << word_amt << " words in total\n";
    cout << "The percentage of occurrences is " << (static_cast<double>(word_sequence_amt) / word_amt) * word_count * 100 << "%\n";
}

int find_word_sequence(string words[MAX_WORDS], int from, int to, string word_sequence[MAX_WORDS_SEQUENCE], int word_sequence_amt)
{
//               
    assert(from >= 0 && to >= 0 && word_sequence_amt >= 0);
/*                
                                                                                                             
                                                   
*/
    for (int i = from; i <= to; i++) {
        if (words[i] == word_sequence[0]) {
            bool sequence = true;
            for (int j = 1; j < word_sequence_amt && sequence; j++) {
                sequence = (i + j <= to) && (words[i+j] == word_sequence[j]);
            }
            if (sequence)
                return i;
        }
    }
    return to + 1;
}

void where(string words[MAX_WORDS], int word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                                                           
                                                  
*/
    int index_count = 0;
    string word_sequence[MAX_WORDS_SEQUENCE];
    int word_sequence_amt = read_word_sequence(word_sequence);
    int index = find_word_sequence(words, 0, word_amt - 1, word_sequence, word_sequence_amt);
    if (index != word_amt) {
        cout << "The occurrences are at position " << index + 1;
        index = find_word_sequence(words, index + 1, word_amt - 1, word_sequence, word_sequence_amt);
        index_count++;
    }
    while (index < word_amt) {
        cout << ", " << index + 1;
        index = find_word_sequence(words, index + 1, word_amt - 1, word_sequence, word_sequence_amt);
        index_count++;
    }
    cout << "\nThere are " << index_count << " occurrences\n";
}

void print_with_context(string words[MAX_WORDS], int word_amt, int word_sequence_amt, int index, int m)
{
//               
    assert(word_amt >= 0 && word_sequence_amt >= 0 && index >= 0 && index < word_amt && m >= 0);
/*                
                                                                                             
*/
    for (int i = index - m; i < index + word_sequence_amt + m - 1 && i < word_amt - 1; i++) {
        if (i >= 0)
            cout << words[i] << ' ';
    }
    if (index + m + word_sequence_amt - 1 < word_amt)
        cout << words[index + m + word_sequence_amt - 1];
    else
        cout << words[word_amt - 1];
    cout << '\n';
}

void context(string words[MAX_WORDS], int word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                      
                                                                                                                                      
                                                  
*/
    int m;
    cin >> m;
    int index_count = 0;
    string word_sequence[MAX_WORDS_SEQUENCE];
    int word_sequence_amt = read_word_sequence(word_sequence);
    int index = find_word_sequence(words, 0, word_amt - 1, word_sequence, word_sequence_amt);
    if (index != word_amt) {
        cout << "The occurrences in context are:\n";
    }
    while (index < word_amt) {
        print_with_context(words, word_amt, word_sequence_amt, index, m);
        index = find_word_sequence(words, index + 1, word_amt - 1, word_sequence, word_sequence_amt);
        index_count++;
    }
    cout << "\nThere are " << index_count << " occurrences\n";
}

void proces_input(string input, string words[MAX_WORDS], int& word_amt)
{
//               
    assert(word_amt >= 0);
/*                
                                      
*/
    if (input == "enter") {
        enter(words, word_amt);
    } else if (input == "content")
        print(words, word_amt);
    else if (input == "count") {
        execute_count(words, word_amt);
    } else if (input == "where") {
        where(words, word_amt);
    } else if (input == "context") {
        context(words, word_amt);
    } else
        cout << "I don't recognize this command\n";
}

int main()
{
    string input;
    ask_for_input(input);
    string words[MAX_WORDS];
    int word_amt = 0;
    while (input != "stop") {
        proces_input(input, words, word_amt);
        ask_for_input(input);
    }

    return 0;
}

