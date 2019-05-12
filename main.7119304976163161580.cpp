using namespace std;
#include <cassert>
#include <fstream> //             
#include <iostream>

/*                                                                   
                
                                 
                              

                                                                   */

const int MAX_WORD_AMOUNT = 10000;
const int MAX_QUERY_WORDS = 100;
string words[MAX_WORD_AMOUNT];

//                                                                             
//                                                    
void add_word(string word, string words[MAX_WORD_AMOUNT], int &max_index) {
  //               
  assert(MAX_QUERY_WORDS >= 0 && max_index >= 0);
  //                                            

  words[max_index] = word;
  max_index++;
}

void open_and_store_words(string fileName, string words[MAX_WORD_AMOUNT],
                          int &max_index) {
  //               
  assert(MAX_WORD_AMOUNT >= 0 && max_index >= 0);
  //                                                                    
  //                                              

  ifstream input_file;
  input_file.open(fileName);

  if (!input_file.is_open()) {
    cout << "Failed to open \"" << fileName << "\"." << endl;
    return;
  }
  cout << "The file \"" << fileName << "\" was successfully openened!" << endl;

  while (input_file) {
    input_file >> words[max_index];
    max_index++;
  }

  max_index--;

  cout << "The file has " << max_index << " words" << endl;
}

void read_words(string words[MAX_QUERY_WORDS], int &query_word_amount) {
  //               
  assert(MAX_QUERY_WORDS >= 0);
  //                                                                            
  query_word_amount = 0;
  char c;
  bool found_end = false;
  while (!found_end && cin.get(c)) {
    if (c == '\n') {
      found_end = true;
      query_word_amount++;
    } else {
      if (c == ' ') {
        if (words[query_word_amount].length() > 0) {
          query_word_amount++;
        }
      } else {
        words[query_word_amount] += c;
      }
    }
  }
}

void where_words(string words[MAX_WORD_AMOUNT], int max_index) {
  //               
  assert(MAX_QUERY_WORDS >= 0 && max_index >= 0);
  //                                                                         

  string query_words[MAX_QUERY_WORDS];
  int query_word_amount;
  read_words(query_words, query_word_amount);

  int matches = 0;
  for (int i = 0; i < max_index - query_word_amount; i++) {
    bool found_full_match = true;
    for (int j = 0; j < query_word_amount; j++) {
      if (words[i + j] != query_words[j]) {
        found_full_match = false;
      }
    }
    if (found_full_match) {
      cout << "Found match at index " << i << endl;
      matches++;
    }
  }
  cout << "Found occurances: " << matches << endl;
}

void count_words(string words[MAX_WORD_AMOUNT], int max_index) {
  //               
  assert(MAX_QUERY_WORDS >= 0 && max_index >= 0);
  //                                                                        
  //                                                                           

  string query_words[MAX_QUERY_WORDS];
  int query_word_amount = 0;
  read_words(query_words, query_word_amount);

  int matches = 0;
  for (int i = 0; i < max_index - query_word_amount; i++) {
    bool found_full_match = true;
    for (int j = 0; j < query_word_amount; j++) {
      if (words[i + j] != query_words[j]) {
        found_full_match = false;
      }
    }
    if (found_full_match) {
      matches++;
    }
  }
  double percentage = ((double)matches / (double)max_index) * 100;
  cout << "matches: " << matches << " total words: " << max_index
       << " percentage: " << percentage << "\%" << endl;
}

void context_words(string words[MAX_WORD_AMOUNT], int max_index) {
  //              
  assert(MAX_QUERY_WORDS >= 0 && max_index >= 0);
  //                                                                        
  //                                                                       

  string query_words[MAX_QUERY_WORDS];
  int query_word_amount = 0;
  int m;
  cin >> m;
  read_words(query_words, query_word_amount);

  int matches = 0;
  for (int i = 0; i < max_index - query_word_amount; i++) {
    bool found_full_match = true;
    for (int j = 0; j < query_word_amount; j++) {
      if (words[i + j] != query_words[j]) {
        found_full_match = false;
      }
    }
    if (found_full_match) {
      if (i - m >= 0 && i + m < max_index) {
        cout << "context:";
        for (int k = i - m; k < i + m + 1; k++) {
          cout << " " << words[k];
        }
        cout << endl;
      }
      matches++;
    }
  }
  cout << "Found occurances: " << matches << endl;
}

void show_content(string words[MAX_WORD_AMOUNT], int max_index) {
  //               
  assert(MAX_WORD_AMOUNT >= 0);
  //                                                            

  //                                                  
  for (int i = 0; i <= max_index; i++) {
    cout << words[i] << endl;
  }
}

string get_file_name() {
  //               
  assert(true);
  //                                                                 

  string file_name = "";
  char c;
  cin.get(c);
  cin.get(c);
  while (c != '\n') {
    file_name += c;
    cin.get(c);
  }
  return file_name;
}

int main() {
  string words[MAX_WORD_AMOUNT];
  int max_index = 0;

  cout << "Please enter a command or type help for a list of commands" << endl;
  while (true) {
    string command;
    cin >> command;
    bool parsed = false;
    if (command == "enter") {
      cout << "Enter a filename: ";
      open_and_store_words(get_file_name(), words, max_index);
      parsed = true;
    }
    if (command == "content") {
      show_content(words, max_index);
      parsed = true;
    }
    if (command == "stop") {
      return 0;
      parsed = true;
    }
    if (command == "count") {
      count_words(words, max_index);
      parsed = true;
    }
    if (command == "where") {
      where_words(words, max_index);
      parsed = true;
    }
    if (command == "context") {
      context_words(words, max_index);
      parsed = true;
    }

    if (command == "help") {
      cout << "possible commands are:" << endl;
      cout << "enter <filename>" << endl;
      cout << "stop" << endl;
      cout << "content" << endl;
      cout << "count <word_1> <word_2> ... <word_n>" << endl;
      cout << "where <word_1> <word_2> ... <word_n>" << endl;
      cout << "condext <word_1> <word_2> ... <word_n>" << endl;
    }
  }
}

