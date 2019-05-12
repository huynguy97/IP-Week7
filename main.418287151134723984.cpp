//                       
//                          

#include <iostream>
#include <fstream>
#include <string> //          
#include <cassert>

using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

bool open_file(ifstream& infile)
{
    //             
    assert(true);
    //                                                           
    char filename [MAX_CHARS];
    cout << "Enter a filename: " ;
    cin.getline(filename, MAX_CHARS);

    infile.open(filename);

    return infile.is_open();
}

int read_textfile(string allwords[MAX_WORDS], ifstream& infile)
{
    //             
    assert(infile.is_open());
    //                                                                                                                         
    int i = 0;

    string word;

    while (infile)
    {
        infile >> word;
        if (word[word.length()-1]==','|| word[word.length()-1]=='.') word.erase(word.end()-1);

        allwords[i]=word;
        i++;                            //                       
        word.clear();
    }
    i--; //                      

    return i;

}

void show_words(string words[MAX_WORDS], int numberofwords)
{
        //             
    assert(true);
    //                                                            

    for (int i=0; i<numberofwords; i++)
    {
        cout << words[i] << endl;
    }

    return;
}

int enter_word_sequence(string sequence[MAX_WORDS])
{
    //             
    assert(true);
    //                                                                                                                  

    cout << "Enter a word sequence and end with 'stop': " << endl;

    int i=0;
    string word;
    cin >> word;
    while (word.compare("stop")!=0)
    {
        sequence[i] = word;
        i++;
        word.clear();
        cin >> word;
    }

    return i;
}

int search_seq_in_txt(string sequence[MAX_WORDS], string words[MAX_WORDS], int numberseq, int numberwords, int occuranceloc[MAX_WORDS])
{
    int j=0;
    for (int wor =0 ; wor < numberwords; wor++){
        if (words[wor] == sequence[0]) {
            int keep = wor;
            keep++;
            bool match = true;
            for (int seq = 1; seq < numberseq; seq++)
            {
                if (sequence[seq]!=words[keep]) {
                    match=false;
                    seq=numberseq;
                }
                keep++;
            }
            if (match){
                occuranceloc[j] = wor;
                j++;
            }
        }
    }

    return j;
}

int main()
{
    string filewords[MAX_WORDS];
    ifstream readfile;
    int numberofwords;

    if (open_file(readfile))
    {
        numberofwords = read_textfile(filewords, readfile);
         cout << "The number of words in the file: " << numberofwords << endl;
    }
    else cout << "The file could not be opened " << endl;

    readfile.close();

    //                                     

    int option=0;
    cout << "Enter the number of the program you want to run: \n 1.count number of occurrences of a word sequence\n 2.display all index-positions of the occurrences of a word sequence\n 3.display all occurrences of the word including a number of words before and after. " << endl;
    cin >> option;
    while(option==0||option > 3)
    {
        cout << "This is not a valid option, try again: ";
        cin >> option;
    }

    string wordsequence[MAX_WORDS];
    int numberofseq = enter_word_sequence(wordsequence);
    int occuranceloc [MAX_WORDS];
    int occurances;
    occurances = search_seq_in_txt(wordsequence, filewords, numberofseq, numberofwords, occuranceloc);
    int b;
    int bb;
    switch(option){
        case 1:
            cout << "The number of occurances is: " << occurances << endl;
            cout << "The total number of words in the text: " << numberofwords << endl;
            cout << "The percentage of occurances of the words in the wordsequence: " << ((occurances*numberofseq*100)/numberofwords) << "%" << endl;

            break;
        case 2:
            cout << "The occurance locations are: ";
            for (int i=0; i<occurances; i++) cout << occuranceloc[i] << ' ';
            cout << endl << "The number of occurances is: " << occurances << endl;
            break;
        case 3:
            int m;
            cout << "Enter the context number: ";
            cin >> m;
            cout << endl;

            for (int j=0; j<occurances; j++){
                    int start = occuranceloc[j]-m;
                    if(start<0) start = 0;
                    int einde = occuranceloc[j]+numberofseq+m;
                    if (einde > numberofwords) einde=numberofwords;
                    for(int k=start; k<einde; k++) cout << filewords[k] << " ";
                    cout << endl;
            }
            cout << endl << "The number of occurances is: " << occurances << endl;

            break;
    }
}

