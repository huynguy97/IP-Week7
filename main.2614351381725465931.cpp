//                                   

#include <iostream>
#include <fstream>
#include <cassert>
#include <math.h>
#include <string>
using namespace std;

string extract_command(string s)
{
    int pos = s.find(' ');
    string command = s.substr(0, pos);
    return command;
}

string extract_filename(string s)
{
    int pos = s.find(' ');
    string filename = s.substr(pos+1, sizeof(s));
    return filename;
}

double count_words(ifstream& ifs, string s)
{
    ifs.open( s.c_str());
    if(ifs.is_open())
    {
       double words = 0.0;
        string pointless ;
        while(!ifs.eof())
        {
            ifs >> pointless;
            words ++;
        }
        //                                                        
        ifs.close();
        return words;
    }
    else
    {
        cout << "Error opening file\n";
        ifs.close();
        return -1;
    }
}

void open_file(ifstream& ifs, string fn, int wc, string w[])
{
    ifs.open( fn.c_str());
    if(ifs.is_open())
    {
        for(int x=0; x < wc; x++)
        {
            ifs >> w[x];
        }
    }
    else{
        cout << "Error!\n";
    }
    ifs.close();
}

string combine_str(string w[], int wc)
{
    string res;

    for(int x=0; x < wc; x++)
    {
        res.append(w[x] + " ");
    }
    return res;
}

void show_content(int wc, string w[])
{
    for(int i=0; i<wc; i++)
    {
         cout << w[i] << " ";
    }
    cout << endl;
}

int count_substr(string str,  string sub)
{
    if (sub.length() == 0) return 0;
    int c = 0;
    for (int o = str.find(sub); o != string::npos; o = str.find(sub, o + sub.length()))
    {
        ++c;
    }
    return c;
}

void search_indices(string str, string sub, int occ, int idx[])
{
    int pos = 0;

    for(int i = 0; i < occ; i++)
    {
        int index = str.find(sub);
        pos += index;
        idx[i] = pos;
    }

}

//                                                               
//                                                                 
//                                                                     
//                                                    
//                                                     
//                               
//                                             
//                                                       
//                                                            
//                                                   
//                        
//                    
//          
//             
//             
//       
//                                                     
//                                                            

int main ()
{
    ifstream input_file;
    string input;
    cout << "Welcome to Concordance City!\nYou will first need to enter the filename.\nAfter this, you can enter all the commands you wish!\nP.S. Yes, you will still need to use the 'enter' command,\nso you will need to enter the filename twice :(\nFilename: ";

    getline(cin, input);
    int word_count = count_words(input_file, input);
    string words[word_count];
    bool is_finished = false;

    while (!is_finished)
    {
        getline(cin, input);
        string command = extract_command(input);
        string filename  = extract_filename(input);
        //                                                

        if (command == "enter")
        {
            open_file(input_file, filename, word_count, words);
        }
        else if (command == "content")
        {
            show_content(word_count, words);
        }

        else if (command == "stop")
        {
            is_finished = true;
        }

        else if (command == "count")
        {
            string text = combine_str(words, word_count);
            double c = count_substr(text, filename);
            double p = (c / (double) word_count) * 100;
            double pc = (int)(p * 10.0)/10.0;

            cout << c << " " << word_count << " " << pc << "%\n";
        }

        else if (command == "where")
        {
            string text = combine_str(words, word_count);
            int occurences = (int) count_substr(text, filename);
            int indices[occurences];
            search_indices(text, filename, occurences, indices);

            for(int i = 0; i < occurences; i++)
            {
                cout << indices[i] << " ";
            }
            cout << "Occurences: " << occurences << endl;
        }

        else if (command == "context")
        {
            cout << "Not implemented yet :(\n";
        }
    }
    return 0;
}

