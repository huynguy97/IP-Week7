#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <cstring>

using namespace std;

//                            
//                          

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   
const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000 ;

char text [MAX_WORDS][MAX_CHARS];
char words [MAX_WORDS][MAX_CHARS];
int freqs [MAX_WORDS];

bool open_text_file( ifstream& infile)
{
//                
    assert (!infile.is_open());
//                 
//                                         

    char filename[80] ;
    cin.getline(filename, 80, '\n');
    infile.open(filename) ;
    return infile.is_open();
}

bool read_seq(char input [MAX_WORDS], int& no_of_words)
{
//                
    assert ( no_of_words >= 0 && no_of_words <= MAX_WORDS);
//                 
//                                                                            

    char seq[MAX_CHARS];
    cin.getline(seq, MAX_CHARS, '\n');
    for (int i = 0; i < MAX_CHARS; i++)
    {
        if (seq[i] == ' ')
            no_of_words++;
    }
    return true;
}

int sequential_search(char data[MAX_WORDS][MAX_CHARS], int from, int to , char search_value[MAX_CHARS])
{//               
    assert( 0 <= from && 0 <= to  ) ;
//                 
//                                    
//                                                                   
//                    
//                                                                       
//                                            
//                                     

    if (from > to)
        return to + 1;
    int position = from;
    bool result = false;
    while(position < to && result == false)
    {
        position++;
        if (strcmp(data[position], search_value) == 0)
        {
            result = true;
        }
    }
    return position;
}

bool tally(char word [MAX_CHARS], char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int& no)
{
//                
    assert(no >= 0 && no < MAX_WORDS);
//                 
//                         
//                                                             
//                                                                     

    int pos = sequential_search (words,  0, no, word) ;
    if (pos < no)
    {
        freqs[pos]++ ;
        return true;
    }else if(pos < MAX_WORDS)
    {
        strcpy(words[pos], word) ;
        freqs[pos] = 1 ;
        no++ ;
        return true;
    }

    return false;
}

bool read(ifstream& infile, char word[MAX_CHARS])
{
//                
    assert (infile.is_open());
//                 
//                                                                           

    infile >> word;

    return infile;
}

void sort (char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int no)
{
//                
    assert (no >= 0 && no <= MAX_WORDS);
//                 
//                                                                  

        for(int x = 0; x < no; x++)
        {
                for(int y = 0;y < no - 1; y++)
                {
                        if(freqs[y] < freqs[y+1])
                        {
                                swap(freqs[y], freqs[y+1]);
                                swap(words[y], words[y+1]);
                        }
                }
        }
}

bool cpy_array(char word [MAX_CHARS], char text [MAX_WORDS][MAX_CHARS])
{
//                
    assert ( true);
//                 
//                                                                                     

    int index = 0;
    for (int i = 0; i < MAX_CHARS; i++)
    {
        text[index][i] = word[i];
    }

    index++;

    return true;
}

int count_words (ifstream& infile, char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS])
{
//                
    assert (infile.is_open());
//                 
//                                                                           

    int no = 0;
    char next [MAX_CHARS];

    while (read(infile, next) && cpy_array(next, text) && tally(next, words, freqs, no) && no < MAX_WORDS );
    sort(words, freqs, no);
    return no;
}

void display_frequencies(char words[MAX_WORDS][MAX_CHARS], int freqs[MAX_WORDS], int no)
{
//                
    assert (no >= 0 && no < MAX_WORDS);
//                 
//                                                                  

    for(int i = 0; i < no; i++)
    {
        cout << words[i] << "\t" << freqs[i] << "\n";
    }
}

int seq_search (char data[MAX_WORDS][MAX_CHARS], int from, int to , char search_value[MAX_WORDS][MAX_CHARS], int no_of_words)
{//               
    assert( 0 <= from && 0 <= to  ) ;
//                 
//                                    
//                                                                   
//                    
//                                                                       
//                                            
//                                     

    if (from > to)
        return to + 1;
    int position = from;
    bool result = false;
    while(position < to && result == false)
    {
        position++;
        for (int index = 0; index < no_of_words; index++)
        {
            if (strcmp(data[position+index], search_value[index]) == 0)
                result = true;
        }
    }
    return position;
}

bool tally_seq (char text [MAX_WORDS][MAX_CHARS], char seq [MAX_WORDS][MAX_CHARS], int& no_of_words, int& no_of_occur)
{
//                
    assert( no_of_words >= 0 && no_of_words < MAX_WORDS);
//                 
//                         
//                                                             
//                                                                     

    int pos = seq_search(text, 0, MAX_WORDS, seq, no_of_words);
    if(pos < MAX_WORDS)
    {
        no_of_occur++;
        return true;
    }

    return false;
}

int count_seq (char text [MAX_WORDS][MAX_CHARS])
{
//                
    assert (true);
//                 
//                                                                               

    int no;
    int no_of_words = 0;
    int no_of_occur = 0;
    char next [MAX_CHARS];
    char seq [MAX_WORDS][MAX_CHARS];

    while(read_seq(next, no_of_words) && cpy_array(next, seq) && tally_seq(text, seq, no_of_words, no_of_occur) && no < MAX_WORDS);

    return no_of_occur;
}

int main()
{
    char c;
    int nr, seq;
    ifstream inputfile;
    string command;

    cout << "Enter command: ";
    cin >> command;

    while (command != "stop")
    {
        if(command == "enter")
        {
            cin.get(c);
            open_text_file(inputfile);
            if(!inputfile.is_open())
            {
                cout << "\nThe file couldn't be opened." << endl;
                return -1;
            }
            nr = count_words(inputfile, words, freqs);
            cout << "\nThere are " << nr << " unique words in the text." << endl;

        } else if (command == "content")
        {
            display_frequencies(words, freqs, nr);
        } else if (command == "count")
        {
            cin.get(c);
            seq = count_seq(text);
            cout << "The given sequence occurs " << seq << " times." << endl;
        } else if (command == "where")
        {
            cin.get(c);
        } else if (command == "context")
        {
            cin.get(c);
        } else
        {
            cout << "The input is not valid, choose from: {enter, content, stop, count, where, context}" << endl;
        }
        cout << "Enter command: ";
        cin >> command;
    }
    if (command == "stop")
    {
        cout << "\nThe program terminates";
        inputfile.clear () ;
        inputfile.close () ;

        if (!inputfile)
        {
            cout << "\nNot all files were closed successfully. The output might be incorrect." << endl ;
            return -1 ;
        }
        return 0;
    }

    return 0;
}

