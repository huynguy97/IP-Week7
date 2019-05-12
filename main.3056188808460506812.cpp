#include <iostream>
#include <fstream>

/*

                                         
                                         

*/
using namespace std;

const int MAX_WORDS = 30000;
const int MAX_QUERY_WORDS = 50;

void check_word(string word, string words[MAX_WORDS], int freq[MAX_WORDS])
{

    int i = 0;
    bool contains_word = false;
    while(words[i]!="" && !contains_word)
    {
        if(word==words[i])
        {
            freq[i]++;
            contains_word = true;
        }
        i++;
    }
    if(!contains_word)
    {
        words[i] = word;
        freq[i] = 1;
    }
}

void count_words(ifstream& infile, string words[MAX_WORDS], int freq[MAX_WORDS])
{

    //                                 
    for(int n=0; n<MAX_WORDS; n++)
    {
        words[n] = "";
        freq[n] = 0;
    }

    //                                                                                          
    int current_word = 0;
    string word;
    while(infile)
    {
        infile >> word;
        //                                                 
        check_word(word, words, freq);
        current_word++;
    }

    //                       
    int i = 0;
    while(freq[i]!=0)
    {
        i++;
    }
    freq[i-1]--;

    cout << "File opened correctly: read " << current_word-1 << " words." << endl;
}

void display_frequencies(string words[MAX_WORDS], int freq[MAX_WORDS])
{

    int i = 0;

    cout << "Word: \tFreq:" << endl;
    while(freq[i]!=0)
    {
        cout << words[i] << "\t" << freq[i] << endl;
        i++;
    }
}

bool open_text_file(ifstream& infile)
{
    char filename[80];
    cin.getline(filename, 80, '\n');
    infile.open(filename);
    return infile.is_open();
}

void read_inputwords(string inputwords[MAX_QUERY_WORDS]){
    int i = 0;
    while(i<5){
        cin >> inputwords[i];
        cin.ignore(1);
        i++;
    }

    for(int n =0; n < 5; n++){
        cout << inputwords[n];
    }
}

void query_user(string words[MAX_WORDS], int freq[MAX_WORDS])
{

    cout << "Enter one of the following commands: " << endl;
    cout << "enter [filename] : " << "Opens file [filename] and reads all words." << endl;
    cout << "content \t : " << "Display all stored words in order of their appearance." << endl;
    cout << "stop \t\t : " << "Stops the program." << endl;

    string inputwords[MAX_QUERY_WORDS];
    string command;
    bool query = true;
    while (query)
    {
        cin >> command;
        if(command == "enter")
        {
            ifstream infile;
            cin.ignore(1);
            if(open_text_file(infile))
            {
                count_words(infile, words, freq);
                infile.close();

            }
            else
            {
                cout << "Please enter a valid filename." << endl;
            }

        }
        else if(command == "content")
        {
            display_frequencies(words, freq);
        }
        else if(command == "stop")
        {
            query = false;
        }
        else if(command == "count"){
            cin.ignore(1);
            read_inputwords(inputwords);

        }
        else
        {
            cout << "Please enter a valid command." << endl;
        }
    }

}

int main()
{
    string words[MAX_WORDS];
    int freq[MAX_WORDS];

    query_user(words, freq);

    return 0;
}

