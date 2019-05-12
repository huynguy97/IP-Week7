#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>

using namespace std;

string filename = "";
int gno_words = 0;

bool open_input_file(ifstream& infile)
{
	//                
	assert(true); //                                                                     
                  //                                                             

	//                 
	/*                        
	                                        
	                                            
	                         */

	cout << "Please enter a file name:  $  ";
	string input_filename = "";
	cin >> input_filename;

	infile.open(input_filename.c_str());
	if(!infile)
	{
        cout << "Failed to open file " << input_filename << endl;
        return false;
	}
    filename = input_filename.c_str();
	return true;
}

bool reopen(ifstream& infile)
{
    infile.close();
    infile.open(filename);
    if(!infile)
    {
        cout << "Failed to open file " << filename << endl;
        return false;
    }
    return true;
}

int count_words(ifstream& infile)
{
    //           
    assert(infile.is_open());
    //            
    /*                                        
                                
     
    */
    char c = 0;
    infile.get(c);
    int i = 0;
    bool last_space = false;
    while(infile)
    {
        if((c == ' ' || c == '\n') && last_space)
        {
            last_space = true;
        }
        else if((c == ' ' || c == '\n') && !last_space)
        {
            i++;
            last_space = true;
        }
        else
        {
            last_space = false;
        }

        infile.get(c);
    }

    return i;
}

void store_words(string* words, istream& infile)
{
    char c = 0;
    infile.get(c);
    int i = 0;
    bool last_space = false;

    string current_words = "";
    while(infile)
    {
        if((c == ' ' || c == '\n') && last_space)
        {
            last_space = true;
        }
        else if((c == ' ' || c == '\n') && !last_space)
        {
            i++;
            words[i] = current_words;
            current_words = "";
            last_space = true;
        }
        else
        {
            current_words = current_words + c;
            last_space = false;
        }

        infile.get(c);
    }
}

void explode_char_arr(char* input, string* output)
{
    int k = 0;

    for(int i = 0; i < 150; i++)
    {

        switch(input[i])
        {
            case ' ':
                k++;
                break;
            default:
                output[k] = output[k] + input[i];
                break;
        }
    }
}

void clean_array(char* input, int i)
{
    for(int k = -1; (k + i) < 150; k++)
    {
        input[k + i] = (char) 0;
    }
}

void print_context_f(string* words, int i, int m)
{
    for(int p = 0; p < m; p++)
    {
        cout << words[(i - m) + p] << " ";
    }
    for(int p = 0; p < m; p++)
    {
        cout << words[i + p] << " ";
    }
    cout << endl << endl;
}

int cmd_count (string *cmd_arg, string *words, int no_words, bool print_index = false, bool print_context = false, int m = 0)
{
    string sequence[150];
    int i = 0;//                   
    while(cmd_arg[i + 1] != "")
    {
        sequence[i] = cmd_arg[i + 1];
        i++;
    }
    i--;

    int y = 0;
    for(int p; p < no_words; p++)
    {
        if(words[p] == sequence[0])
        {
            bool holds = true;
            for(int q = 0; q < i; q++)
            {
                if(words[p + q] != sequence[q])
                {
                    holds = false;
                }
            }

            if(holds)
            {
                y++;
                if(print_index)
                {
                    cout << "Index: " << p << endl;
                }
                if(print_context)
                {
                    print_context_f(words, p, m);
                }
            }
        }

    }

    return y;

}

int catch_m (string *cmd_arg)
{
     int m = stoi(cmd_arg[1]);
     for(int i = 1; i < 150; i++)
     {
        cmd_arg[i - 1] = cmd_arg[i];
     }
     return m;
}

void exec_cmd(string *words)
{
    char cmd[150];

    char c = 32;
    int i = 0;
    cin.ignore(1);
    while(c != '\n')
    {
        c = cin.get();
        cmd[i] = c;
        i++;
    }

    clean_array(cmd, i);

    string cmd_arg[150];
    explode_char_arr(cmd, cmd_arg);

    while(true) {
    //                                       
        if(cmd_arg[0] == "--help")
        {
            cout << "Help menu";
        }
        else if(cmd_arg[0] == "count")
        {
            int occ = cmd_count(cmd_arg, words, gno_words);
            double perc = ( (double) occ * 100)/gno_words;
            cout << "This sequence occurs " << occ << " times of " << gno_words << " words, which is " << perc << " percent.";
        }
        else if(cmd_arg[0] == "where")
        {
            int occ = cmd_count(cmd_arg, words, gno_words, true);
            cout << "This sequence occurs " << occ << " times";
        }
        else if(cmd_arg[0] == "context")
        {
            int m = catch_m(cmd_arg);
            int occ = cmd_count(cmd_arg, words, gno_words, false, true, m);
            cout << "This sequence occurs " << occ << " times";
        }
        else
        {
            cout << "Please retry, this command was not valid. Type --help for help. \n";
        }
        cin.ignore(1500);
    }

}

int main()
{
    ifstream infile;
    if(open_input_file(infile))
    {
        //                                                                          
        int no_words = 0;
        no_words = gno_words = count_words(infile);
        //                                                                                                    
        //                         
        reopen(infile);
        //                                                                                                
        //                                                              
        string words[no_words];
        store_words(words, infile);

        cout << "This document has " << no_words << " words. \nPlease enter a command. Type --help for information.  " << endl;

        //                                                                                                              

        exec_cmd(words);
    }
    return 0;
}

