#include <iostream>
#include <fstream>
#include <cassert>

//                            
//                        

using namespace std;
const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000 ;
string word[MAX_WORDS];
string unique_words[MAX_WORDS];
int freq[MAX_WORDS];
string sequence[MAX_WORDS];

bool open_input_file (ifstream& infile)
{
//                
    assert (true);
//                 
    //                                                                   
    char a;
    char filename [150] ;
    //                              
    cin.get(a);
    cin.getline ( filename, 150, '\n') ;
    infile.open ( filename ) ;
    //                     
    if ( infile.is_open())
        {
            cout << "File opened successfully. <3" << endl;
            return true;
        }
    else
        {
            cout << "Fail opening the file." <<endl ;
            return false ;
        }
}

int read_word (ifstream& infile, string word[MAX_WORDS] )
{
//              
    assert (infile.is_open());
//               
    int i=0;
    while (infile)
    {
       infile >> word[i];
       i++;
    }
    return i;
}

void frequence(string word[MAX_WORDS], string unique_words[MAX_WORDS], int freq[MAX_WORDS], int nr_of_words)
{
    for (int j = 0; j<= nr_of_words; j++)
    {
        string lala = word[j];
        //                            
        int new_unique = 0;
        for (int l = 0; l<=nr_of_words; l++)
        {
            if (lala == unique_words[l])
            {
                new_unique = 1;
            }
        }
        //                                                   
        if (new_unique == 0)
        {
            int frequency = 0;
            for (int k = 0; k<=nr_of_words; k++)
            {
                if (lala == word[k])
                {
                    frequency++;
                }
            }
            freq[j] = frequency;
            unique_words[j] = lala;
        }

    }
}

//                           

void display_content(string word [MAX_WORDS], int nr_of_words)
{
    for (int i=0; i <= nr_of_words; i++)
    {
        cout << word [i] << endl;
    }
}

void display_count(string word[MAX_WORDS], string unique_words[MAX_WORDS], int freq[MAX_WORDS], int nr_of_words, string sequence[MAX_WORDS])
{
    frequence(word, unique_words, freq, nr_of_words);
    char b;
    cin.get(b);
    int c = 0;

    while(cin)
    {
        cin >> sequence[c];
        c++;
    }
    int freq_of_sequence = 0;
    for (int m = 0; m <= nr_of_words; m++)
    {
        bool j= true;
        for (int d; d<=c ; d++)
        {
            if (sequence[d] != word[m+d])
            {
                j = false;
            }
        }
        if (j==true)
        {
            freq_of_sequence++;
        }

    }

     cout << "The number of occurances of the word sequence is " << freq_of_sequence << endl;
     cout << "The total number of words in the text is " << nr_of_words << endl;
     cout << "The percentage of the occurances of the word sequence with respect to the total number of words is " << freq_of_sequence/nr_of_words*100 << "%" << endl;

}

void display_where(string word[MAX_WORDS], string unique_words[MAX_WORDS], int freq[MAX_WORDS], int nr_of_words, string sequence[MAX_WORDS])
{
    char b;
    cin.get(b);
    int c = 0;

    while(cin)
    {
        cin >> sequence[c];
        c++;
    }
    cout << "The indexes of the occurances are " ;
    int freq_of_sequence = 0;
    for (int m = 0; m <= nr_of_words; m++)
    {
        bool j= true;
        for (int d; d<=c ; d++)
        {
            if (sequence[d] != word[m+d])
            {
                j = false;
            }
        }
        if (j==true)
        {
            freq_of_sequence++;
            cout << m << " " ;
        }

    }
    cout << endl;
    cout << "The number of occurances of the sequence is " << freq_of_sequence << endl;
}

void display_context(string word[MAX_WORDS], string unique_words[MAX_WORDS], int freq[MAX_WORDS], int nr_of_words, string sequence[MAX_WORDS])
{
    char b;
    cin.get(b);
    int c = 0;

    while(cin)
    {
        cin >> sequence[c];
        c++;
    }
    int freq_of_sequence = 0;
    for (int m = 0; m <= nr_of_words; m++)
    {
        bool j= true;
        for (int d; d<=c ; d++)
        {
            if (sequence[d] != word[m+d])
            {
                j = false;
            }
        }
        if (j==true)
        {
            freq_of_sequence++;
        }

    }
}

int main()
{
    cout << "If you want to enter the filename you need to enter the command *enter*." << endl;
    cout << "If you want to stop you need to enter the command *stop*." << endl;
    ifstream infile;

    string user_command;
    //                       
    //                                     
    cin >> user_command ;
    if (user_command == "enter")
    {
        open_input_file (infile);
        cin >> user_command;
        while (user_command != "stop")
        {
            open_input_file (infile);
            //                                 

            int nr_of_words = read_word (infile, word);
            cout << "If you want to display all stored words in their order of appearance you need to enter the command *content*." << endl;
            cout << "If you want to count the number of occurrences of the word sequence you need to enter the command *count*." << endl;
            cout << "If you want to display all index-positions of the word you need to enter the command *where*." << endl;
            cout << "If you want to display all occurrences of the word sequence you need to enter the command *context*." << endl;
            cin >> user_command;

            if (user_command == "content")
            {
                display_content(word, nr_of_words);
            }
            else if (user_command == "count")
            {
                display_count(word, unique_words, freq, nr_of_words, sequence);
            }
            else if (user_command == "where")
            {
                display_where(word, unique_words, freq, nr_of_words, sequence);
            }
            else if (user_command == "context")
            {
                display_context(word, unique_words, freq, nr_of_words, sequence);
            }
        }
    }
}

