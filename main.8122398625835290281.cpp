#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;

//                                      
//                                

const int MAX_FILENAME_LENGTH = 200;
const int MAX_AMOUNT_WORDS = 20000;
const int MAX_LENGTH = 20;

string get_command_and_open_file(ifstream& infile)
{
//                
assert(true);
//                                                                              
    char dummy;
    cout<< "enter a command and filename " << endl << "enter, content, stop, count, where, context" << endl;
    string command;
    char filename[MAX_FILENAME_LENGTH];
    cin>>command;
    cin.get(dummy);
    cin.getline(filename, MAX_FILENAME_LENGTH, '\n');
    infile.open(filename);
    if (infile.is_open())
        cout<< " file is open" << endl;
    else
        cout<< " file is not open" << endl;
    return command;
}

int sequential_search (string data[], int from, int to, string search_value)
{
//               
assert(0<=from && 0 <=to);
//                                                   
//                                                                                         
//                                                                                                                                            
if (from > to)
    return to+1;
int position = from;
while(position <= to && data[position] != search_value)
    position++;
return position;
}

int count_sequence(string words[MAX_AMOUNT_WORDS], int words_in_file)
{
//               
assert(true);
//                                                                                       
//                                      
//                                                                                                        
    string sequence;
    char search_words[MAX_AMOUNT_WORDS][MAX_LENGTH];
    cout<< " give sequence" << endl;
    getline(cin, sequence,'\n');
   int word_number = 0;
   int seq_position = 0;
   while (seq_position < (sequence.size()))
        {
            int search_position = 0;
            while ((sequence[seq_position] != ' ') && (seq_position < (sequence.size() )))
            {
                search_words[word_number][search_position] = sequence[seq_position];
                search_position++;
                seq_position++;
            }
            seq_position++;
            word_number++;
        }
    int position = 0;
    double counter;
    while (position < MAX_AMOUNT_WORDS)
        {
            position = sequential_search (words, position, MAX_AMOUNT_WORDS, search_words[0]);
            for (int i = 1; i <= word_number;i++)
                {
                if ((words[position+i] == search_words[i]) && (position<MAX_AMOUNT_WORDS));
                    cout << position<< endl;
                    counter++;
                }
            position++;
        }
cout <<" this sequence occurs " <<  counter-1 << " times" << endl;
cout << " the text contains " << words_in_file << " words" << endl;
double percentage = 0;
percentage = (((counter-1)*word_number)/words_in_file)*100;
cout << " the sequence is " << percentage << " percent of the text" << endl;

}

int main()
{
string command;
ifstream infile;
string words [MAX_AMOUNT_WORDS] = {};
int words_in_file = 0;
command = get_command_and_open_file(infile);
char filename[MAX_FILENAME_LENGTH];
string unique_words[MAX_AMOUNT_WORDS];
 for (words_in_file = 0; infile ; words_in_file++)
            {
                infile >> words[words_in_file];
                if (!infile);
            }
   if (command == "enter")
                cout << "Amount of words in file: " << words_in_file << endl;
    else if (command == "content")
    {
        for(int i=0; i<words_in_file; i++)
            cout<< words[i] << " " << endl;
    }
    else if (command == "stop")
    {
        return 0;
    }
    else if (command == "count")
    {
    count_sequence(words, words_in_file);

    }

}

