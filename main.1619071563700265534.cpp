#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cassert>

//                           
//                      

using namespace std;
const int MAX_OF_WORDS = 100;
const int MAX_CHAR = 100;
enum Commands {enter, content, stop};
char commands [3][8]={"enter","content","stop"};

void getting_filename(char filename[MAX_OF_WORDS])
{
    assert(MAX_OF_WORDS>=0);
    //                                                         
    cin.getline(filename, MAX_OF_WORDS);

}

bool read_word(ifstream& infile, string& word)//                       
{
    assert(infile.is_open());
    //                                                                                             
    infile >> word;
    return infile;
}

int save_words(ifstream& infile, string word, string words[MAX_OF_WORDS])
{
    assert (MAX_OF_WORDS>=0&&infile.is_open());
    //                                                             
    int w = 0;
    for(int i=0;i<MAX_OF_WORDS;i++)
    {
        words[i]="";//                                                                            
    }
    while(read_word(infile, word)&&w<MAX_OF_WORDS)//                                
    {
            words[w]= word;//                
            w++;
    }
    return w;
}

void display_content(string words[MAX_OF_WORDS])
{
    assert(MAX_OF_WORDS>=0);
    //                                                            
    int i = 0;
    while(words[i]!="")//                              
    {
        cout << words[i] << endl;//               
        i++;
    }
}

bool same_words(string words [MAX_OF_WORDS], string input_words[MAX_OF_WORDS], int i, int n)
{
    assert(MAX_OF_WORDS>=0);
    //                                                                       
    if(words[i]==input_words[n])//                                                                
    {
        return true;//          
    }
    else
        return false;//                     
}

void get_words_from_userinput(string input_words[MAX_OF_WORDS])
{
    assert(MAX_OF_WORDS>=0);
    //                                                                          
    int i = 0;
    string input;
    char c = 'c';
    for(int x=0;x<MAX_OF_WORDS;x++)
    {
        input_words[x]="";//                                                                           
    }
    while(c != '\n')//                                              
    {
        cin >> input;//                  
        input_words[i]= input;//                         
        i++;
        cin.get(c);//                                                                                         
    }
}

int compare_sequence(string words[MAX_OF_WORDS], string input_words[MAX_OF_WORDS],bool where, bool context, int m)
{
    assert(MAX_OF_WORDS>=0);
    //                                                                       
    int n = 0;
    int i = 0;
    int number = 0;
    int index = 0;
    while(words[i]!="")//                                                       
    {
        if(same_words(words, input_words, i, n))//                             
        {
            i++;
            n++;
            index = i;//                      
            while(same_words(words, input_words, i, n)&&input_words[n]!="")//                                     
            {
                i++;
                n++;
            }
            if(input_words[n]=="")//                          
            {
                if(where)//                                         
                {
                    cout<< index << ",";
                }
                if(context)//                                               
                {
                    int x = (index-m-1);//                                             
                    while(x!=(i+m))//                                
                    {
                        string word = words[x];
                        cout << word << " ";
                        x++;
                    }
                    cout << ", ";
                }
                number++;//                                 
            }
            n = 0;
            i--;//                      
        }
        i++;

    }
    return number;
}

int main()
{
    char filename[MAX_OF_WORDS];
    ifstream infile;
    string words [MAX_OF_WORDS];
    string input_words[MAX_OF_WORDS];
    string word;
    string userinput;
    double whole_text = 0;

    cout << "Please terminate any input with an enter"<<endl;
    cout << "If you type 'enter', then a space and a filename (including .txt) it will open that file save the words in an array" << endl;
    cout << "If you type 'content' the current words saved in the array of words will be displayed" << endl;
    cout << "If you type 'count' and then a space and a word sequence the programme will count how often that occurs."<< endl;
    cout << "If you type in 'where' and a words sequence it shows you the indices of where the word sequence starts"<< endl;
    cout << "If you type in 'context' and integer and a words sequence it shows you the words before and after every word sequence"<< endl;
    cout << "If you type 'stop' the program will terminate"<< endl;
    cin >> userinput;
    while(userinput != "stop")
    {
        if(userinput == "enter")
        {
            cin.ignore(1);
            getting_filename(filename);
            infile.open(filename);
            //                         
            cout << "The programme saved ";
            whole_text = save_words(infile, word, words);
            cout << whole_text;
            cout << " words."<< endl;
            infile.close();
            //                       
        }
        if(userinput=="content")
        {
            display_content(words);
        }
        if(userinput =="count")
        {
            get_words_from_userinput(input_words);
            double amount = compare_sequence(words, input_words, false, false, 0);
            cout <<"This sequence occures "<<amount<<" times."<<endl;
            cout << "The whole text has "<< whole_text <<" words." << endl;
            cout << "The sequence makes up " << amount/whole_text*100 << "% of the whole text."<< endl;
        }
        if(userinput == "where")
        {
            get_words_from_userinput(input_words);
            int amount = compare_sequence(words, input_words, true, false, 0);
            cout << amount << endl;
        }
        if(userinput=="context")
        {
            int m = 1;
            cin >> m;
            get_words_from_userinput(input_words);
            int amount = compare_sequence(words, input_words, false, true, m);
            cout << amount << endl;
        }
        cout << "Please type in the next command"<<endl;
        cin >> userinput;
    }
    if(userinput=="stop")
    {
        cout << "Good Bye and thanks for using this programme :D"<< endl;
        return 0;
    }
    return 0;
}

