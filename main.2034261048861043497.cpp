//            
//                            
//                          

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

typedef int Length;
typedef int Amount;

const int MAX_CHARS = 1000;
const int MAX_WORDS = 100;
const int MAX_WORD_LENGTH = 100;
const int MAX_FILE_WORDS = 1000000;

int TOTAL_WORDS = 0;

string file [MAX_FILE_WORDS];

void string_to_array(string message [MAX_WORDS], string msg)
{
	//               
	assert(true);
	//                
	//                                            

	string word = "";
	int count = 0;
	const int length = msg.length();
	for(int i = 0; i < length; i++)
	{
		if(msg[i] == ' ')
		{
			message [count] = word;
			count++;
			word = "";
		}
		else if(i == (length - 1))
		{
			word += msg[i];
			message [count] = word;
			count++;
			word = "";
		}
		else
		{
			word += msg[i];
		}
	}
}

string array_to_filename(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                               
	string result = "";
	for(int i = 1; i < MAX_WORDS; i++)
	{
		result = result + message [i];
		if(i != MAX_WORDS)
		{
			result = result + " ";
		}
	}
	cout << result << endl;
	return result;
}

bool open_file(ifstream& infile, string filename)
{
	//               
	assert(true);
	//                
	//                                                             
	infile = (ifstream) filename.c_str();
	if(infile.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool read_word(ifstream& infile, char word [MAX_WORD_LENGTH])
{
	//               
	assert(infile.is_open());
	//                
	//                                       

	infile >> word;
	return !!infile;
}

void file_to_array(ifstream& infile)
{
	//               
	assert(infile.is_open());
	//                
	//                                                               

	char next_word [MAX_WORD_LENGTH];
	int count = 0;
	while(read_word(infile, next_word))
	{
		string word = next_word;
		file [count] = word;
		count++;
	}
	TOTAL_WORDS = count;
	cout << count << " words were retrieved!" << endl;
}

void enter_command(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                                          

	string filename = array_to_filename(message);

	ifstream infile;
	if(!open_file(infile, filename))
	{
		cout << "Could not open the file. Please try again." << endl;
		return;
	}

	file_to_array(infile);
}

void display_file_words()
{
	//               
	assert(true);
	//                
	//                                                              

	for(int i = 0; i < TOTAL_WORDS; i++)
	{
		cout << i << ": " << file [i] << endl;
	}
}

Length array_length(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                                          

	int count = 0;
	for(int i = 0; i < MAX_WORDS; i++)
	{
		if(message [i] == "")
		{
			return count;
		}
		else
		{
			count++;
		}
	}
	return count;
}

Amount count_sequence(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                                   

	int count = 0;
	int length = array_length(message);
	for(int i = 0; i < TOTAL_WORDS; i++)
	{
		int count1 = i;
		for(int i1 = 1; i1 < length; i1++)
		{
			if(file [count1] == message [i1])
			{
				count1++;
			}
			if((count1 - i) == (length - 1))
			{
				count++;
			}
		}
	}
	return count;
}

void count_command(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                                                       

	double amount_of_occurences = count_sequence(message);
	double amount_of_words = TOTAL_WORDS;
	double percentage = amount_of_occurences / amount_of_words * 100;
	cout << "Amount of occurences: " << amount_of_occurences << endl;
	cout << "Amount of words: " << amount_of_words << endl;
	cout << "Percentage: " << percentage << "%" << endl;
}

void count_sequence2(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                              

	cout << "The sequence occurs at the following positions:" << endl;
	int count = 0;
	int length = array_length(message);
	for(int i = 0; i < TOTAL_WORDS; i++)
	{
		int count1 = i;
		for(int i1 = 1; i1 < length; i1++)
		{
			if(file [count1] == message [i1])
			{
				count1++;
			}
			if((count1 - i) == (length - 1))
			{
				count++;
				cout << (i + 1) << endl;
			}
		}
	}
	cout << "The sequence was found " << count << " times!" << endl;
}

void count_sequence3(string message [MAX_WORDS])
{
	//               
	assert(true);
	//                
	//                                            

	int count = 0;
	int length = array_length(message);
	int amount = atoi((message [1]).c_str());
	for(int i = 0; i < TOTAL_WORDS; i++)
	{
		int count1 = i;
		for(int i1 = 2; i1 < length; i1++)
		{
			if(file [count1] == message [i1])
			{
				count1++;
			}
			if((count1 - i) == (length - 2))
			{
				for(int i3 = 0; i3 < amount; i3++)
				{
					cout << file[i - amount + i3] << " ";
				}
				for(int i3 = 2; i3 < length; i3++)
				{
					cout << message [i3] << " ";
				}
				for(int i3 = 0; i3 < amount; i3++)
				{
					cout << file[i + length - 2 + i3] << " ";
				}
				count++;
				cout << endl;
			}
		}
	}
	cout << "\nNumber of occurences: " << count << endl;
}

int main ()
{
	while(true)
	{
		cout << "\nChoose one of the following commands:" << endl;
		cout << "enter [filename]\t\t - opens the given file" << endl;
		cout << "content \t\t\t - shows the words in the file" << endl;
		cout << "count [word sequence]\t\t - count the occurences of the given word sequence" << endl;
		cout << "where [word sequence]\t\t - show the locations of the occurences of the given word sequence" << endl;
		cout << "context [amount] [word sequence] - show the countext arount the given word sequence" << endl;
		cout << "stop \t\t\t\t - terminates program" << endl;

		char msg [MAX_CHARS];
		cin.getline(msg, MAX_CHARS);

		string message = msg;
		string mess [MAX_WORDS];
		string_to_array(mess, message);

		if(mess [0] == "enter")
		{
			enter_command(mess);
		}
		else if(mess[0] == "content")
		{
			display_file_words();
		}
		else if(mess[0] == "count")
		{
			count_command(mess);
		}
		else if(mess[0] == "where")
		{
			count_sequence2(mess);
		}
		else if(mess[0] == "context")
		{
			count_sequence3(mess);
		}
		else if(mess[0] == "stop")
		{
			return 0;
		}
		else
		{
			cout << "Invalid command, please try again." << endl;
		}
	}
}

