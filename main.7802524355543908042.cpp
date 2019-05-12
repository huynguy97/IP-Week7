#include <iostream>
#include <fstream>
#include <cassert>

//                                                    

using namespace std;

const int MAX_WORDS = 3000;
const int MAX_CHARS = 60;

bool open_file (ifstream& infile)
{
    cout << "Enter name of file to open" <<endl;
    char filename[100];
    infile.open (filename);
    cin.getline (filename, 100);
    return infile.is_open ();
}

int words_list (ifstream &infile, char words [MAX_WORDS][MAX_CHARS])
{
    assert (infile.is_open ());//             
    int i = 0;
    while(i<MAX_WORDS && infile)
    {
        infile >> words[i]; //                                               
        i++;
    }

    return i;
}

int count_wordseq(char words [MAX_WORDS][MAX_CHARS], char seq [MAX_WORDS][MAX_CHARS])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int number = 1;
    int percentage;
    bool found;
    char sequence_of_words[MAX_CHARS];
    cout << "Enter the sequence you want to search"<<endl;
    cin >> sequence_of_words;
    while(i<MAX_WORDS && sequence_of_words) //                                     
    {
        sequence_of_words >> seq[i];
        i++;
    }
    for(j < MAX_WORDS && words[j])
    {
        if(words[j] == seq[0]) //                                                
        {
            for(k <= i)
            {
                if(words[j+k] == seq[k]) //                                            
                    found=true;
                else
                    found=false;
            }
            if(found) //                                                        
            {
                number++;
            }

        }

    }
    percentage = number / word_list(infile); //                     
    cout << number << word_list(infile) << percentage <<endl;
}
int where_wordseq(char words [MAX_WORDS][MAX_CHARS], char seq [MAX_WORDS][MAX_CHARS])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int number = 1;
    bool found;
    char sequence_of_words;
    cout << "Enter the sequence you want to search"<<endl;
    cin >> sequence_of_words;
    while(i<MAX_WORDS && sequence_of_words) //                                     
    {
        sequence_of_words >> seq[i];
        i++;
    }
    for(j < MAX_WORDS && words[j])
    {
        if(words[j] == seq[0]) //                                                
        {
            for(k <= i)
            {
                if(words[j+k] == seq[k]) //                                            
                    found=true;
                else
                    found=false;
            }
            if(found)
            {
                number++; //                                                        
                return j+1; //                     
            }

        }

    }
    return number;
}

int context_wordseq(char words [MAX_WORDS][MAX_CHARS], char seq [MAX_WORDS][MAX_CHARS], int m)
{
    int m;
    int i = 0;
    int j = 0;
    int k = 0;
    int number = 1;
    bool found;
    char sequence_of_words;
    int l = 0;
    char preceding [MAX_WORDS][MAX_CHARS];
    char following [MAX_WORDS][MAX_CHARS];
    cout << "Enter the sequence you want to examine"<<endl;
    cin >> sequence of words;
    cout << "Enter the amount of surrounding words"<<endl;
    cin >> m;
    while(i<MAX_WORDS && sequence_of_words)
    {
        sequence_of_words >> seq[i]; //                                     
        i++;
    }
    for(j < MAX_WORDS && words[j])
    {
        if(words[j] == seq[0]) //                                                
        {
            for(k <= i)
            {
                if(words[j+k] == seq[k]) //                                            
                    found=true;
                else
                    found=false;
            }
            if(found)
            {
                number++; //                                                        
                i = 0;
                while(j-m < l < j)
                     preceding[l] == words[l]; //                             
                while(j < l < j+m)
                    following[l] == words[l]; //                             
            }

    cout >> preceding >> seq >> following >>endl; //                                                                     
    return number;`
}

int main()
{
    ifstream infile;
    char words[MAX_WORDS][MAX_CHARS];
    char seq[MAX_WORDS][MAX_CHARS];
    count_wordseq();
    where_wordseq();
    context_wordseq();
    file.close();
    return 0;
}

