#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

//                                    

//                         

using namespace std;

const int STRINGCOMMAND_SIZE = 7;
const int WORD_AMOUNT = 30000;

enum Command { Count, Content, Where, Context, Stop, Enter, Fail };

string enter_filename() {
	assert(true);
	//                                                                 

	string input;
	cout << "Enter a file name s'il vous plaisait" << endl;
	getline(cin, input);
	return input;
}

void read_file(ifstream& input, string Words[], int& wordcount) {

	//                            
	assert(input.is_open());
	//                                                                         

	input.clear();
	input.seekg(0, ios::beg);

	string s;
	int counter = 0;
	while (input && !input.eof()) {
		input >> s;
		Words[counter] = s;
		counter++;
	}
	wordcount = counter;
}

void print_words(string Words[], int word_count) {
	for (int i = 0; i < word_count; i++) {
		cout << Words[i] << " ";
	}
	cout << '\n';
}

string wordarray_to_string(string Words[], int word_count) {
	string result = "";
	for (int i = 0; i < word_count; i++) {
		result += Words[i] + " ";
	}
	return result;
}

void count(string Words[], int word_count, string paramaters) {
	string all_words = wordarray_to_string(Words, word_count);
	int pos = 0;
	int counter = 0;
	for (counter; (pos = all_words.find(paramaters)) != -1; counter++)
	{
		all_words = all_words.substr(++pos);
	}
	cout << "Found that " << counter << " times" << endl;
	cout << word_count << " is the amount of words in the text" << endl;
	double percentage = (((double)counter / (double)word_count) * 100);
	cout << percentage << " is the percentage" << endl;
}

void where(string Words[], int word_count, string paramaters,int occuracearray[WORD_AMOUNT],int& occurencespass) {
	string all_words = wordarray_to_string(Words, word_count);
	int pos = 0;
	int currentpos = 0;
	int occurences = 0;
	for (int counter = 0; (pos = all_words.find(paramaters)) != -1; counter++)
	{
		all_words = all_words.substr(++pos);
		currentpos = currentpos + pos;
		cout << currentpos << " is the " << counter+1 << " indice" << endl;
		occuracearray[counter] = currentpos;
		occurences++;
	}
	occurencespass = occurences;
	cout << "found " << occurences << " occurences" << endl;
}

void context(string Words[], int word_count, string paramaters,int intparamaters,int occurencearray[WORD_AMOUNT],int& occurencepass) {
	string all_words = wordarray_to_string(Words, word_count);
	int spacecounter1 = 0;
	int spacecounter2 = 0;
	int subcounter1 = 0;
	for (int i = 0; i < occurencepass; i++) {
		int j = occurencearray[i];
		for (j; j > 0 || spacecounter1 < intparamaters; j--) {
			if (all_words[j] == ' ') spacecounter1++;
		}
		int h = occurencearray[i];
		for (h; i < all_words.length() || spacecounter2 < intparamaters ; h++) {
			if (all_words[j] == ' ') spacecounter2++;
		}
		cout << all_words.substr(j, h);
	}
	
}

Command string_to_command(string s) {

	string stringcommand[STRINGCOMMAND_SIZE] = { "count","content","when","context","stop","enter_file" };
	for (int i = 0; i < STRINGCOMMAND_SIZE; i++) {
		if (s == stringcommand[i]) {
			return (Command)i;
		}
	}
}

Command get_user_input(ifstream& infile,string& parameters, int& intparamaters) {

	if (!infile.is_open()) {
		string filename = enter_filename();
		infile.open(filename.c_str());
	}
	//                                           
	assert(infile.is_open());
	//                                                        

	cout << "Enter a command (content,count, where, context, enter_file) or stop to quit" << endl;
	string command;
	cin >> command;

	while (string_to_command(command) > 6) {
		cout << "Please enter a valid command" << endl;
		cin >> command;
	}

	if (command == "context") {
		cin >> intparamaters;
		cin.ignore();
		getline(cin, parameters);
	}else if (command != "content") {
		cin.ignore();
		getline(cin, parameters);
	}
	return string_to_command(command);
}

void procces_commands(Command command, string Words[], int word_count,string paramaters, int intparamaters) {
	int occuracearray[WORD_AMOUNT];
	int occurancespass;
	switch (command) {
	case(Content):  print_words(Words, word_count); break;
	case(Count): count(Words, word_count, paramaters); break;
	case(Where): where(Words, word_count, paramaters, occuracearray, occurancespass); break;
	case(Context): context(Words, word_count, paramaters, intparamaters, occuracearray, occurancespass); break;
	case(Enter):  break;
	}
}

int main() {
	//                        
	string Words[WORD_AMOUNT];
	int word_count = 0;
	//           
	ifstream infile;
	string paramaters ="";
	int intparamaters = 0;
	//                              
	Command currentcommand;
	do {
		currentcommand = get_user_input(infile,paramaters, intparamaters);
		read_file(infile, Words, word_count);
		procces_commands(currentcommand, Words, word_count,paramaters, intparamaters);
	} while (currentcommand != Stop);

	return 0;
}
