#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//                           
//                      

const int MAX_ARG = 20;
const int MAX_WORDS = 100000;
string data [MAX_WORDS];
int no_of_words = 0;

int get_input(string input [MAX_ARG])
{
    //              
    assert(true);
    //               
    //                                                                                                                     
    //                                       
    //                                                                                             
    char a;
    int i = 0;

    do
    {
        cin.get(a);
        if (a == ' ')
        {
            if (input[i] != "") //                                                                                      
                i++;
        }
        else if (a != '\n')
            input[i] += a;
    }
    while (a != '\n' && i < MAX_ARG); //                                                       

    if (i == MAX_ARG)
    {
        cout << "Error: too many arguments. Maximum number of arguments is " << MAX_ARG << endl << endl;
        return -1;
    }

    return i;
}

void enter_filename()
{
    //              
    assert(true);
    //               
    //                                 
    //                                                                                  
    //                                            
    ifstream inputfile;
    string filename;
    string word;
    char a;

    do
        cin.get(a);
    while (a == ' ');

    getline (cin, filename);
    filename = a + filename;

    inputfile.open(filename);

    if (inputfile.is_open())
        cout << "File successfully opened!" << endl;
    else
        cout << "File could not be opened." << endl;

    for (no_of_words = 0; inputfile >> word && no_of_words < MAX_WORDS; no_of_words++)
    {
        data[no_of_words] = word;
    }

    inputfile.close();
}

void show_content()
{
    //              
    assert(true);
    //               
    //                                                                                         
    for (int i = 0; i < no_of_words; i++)
        cout << data[i] << ' ';
    cout << endl;
}

int frequency(int indices [MAX_WORDS], int& word_count)
{
    //              
    assert(true);
    //               
    //                                                                        
    //                                                                          
    //                                                            
    //                                                                   
    string words [MAX_ARG]
    int freq = 0;
    word_count = get_input(words) + 1;
    bool check = true;
    for (int i = 0; i <= no_of_words-word_count; i++)
    {
        check = true;
        for (int j = 0; check && j < word_count; j++)
        {
            if (data[i+j] != words[j]) //                                                        
                check = false;
        }
        if (check) //                                           
        {
            indices[freq] = i;
            freq++;
        }
    }
    return freq;
}

void word_count()
{
    //              
    assert(true);
    //               
    //                                    
    //                                                                                    
    //                                                                                                     
    int useless [MAX_WORDS]; //                             
    int useless2;
    int freq = frequency(useless, useless2);
    cout << "This sequence occurs " << freq << " time(s)" << endl;
    cout << "Total number of words equals " << no_of_words << endl;
    cout << "Percentage of sequence in text: " << 100.0 * freq / (1.0 * no_of_words) << endl;
}

void where()
{
    //              
    assert(true);
    //               
    //                                    
    //                                                                            
    //                                         
    int indices [MAX_WORDS];
    int useless;
    int freq = frequency(indices, useless);
    cout << "This sequence occurs at the following positions:" << endl;
    for (int i = 0; i < freq; i++)
    {
        cout << indices[i]+1 << endl;
    }
    cout << "This sequence occurs " << freq << " time(s)" << endl;
}

void context()
{
    //              
    assert(true);
    //               
    //                                                   
    //                                                                    
    //                                         
    int indices [MAX_WORDS];
    int m;
    cin >> m;
    int word_count;
    int freq = frequency(indices, word_count);
    for (int i = 0; i < freq; i++)
    {
        for (int j = indices[i]-m; j < indices[i]+word_count+m; j++)
            cout << data[j] << ' ';
        cout << endl;
    }
    cout << "The sequence occurs " << freq << " times" << endl;
}

void choose_command(string cmd)
{
    //              
    assert(true);
    //               
    //                                                       
    if (cmd == "enter")
        enter_filename();
    else if (cmd == "content")
        show_content();
    else if (cmd == "count")
        word_count();
    else if (cmd == "where")
        where();
    else if (cmd == "context")
        context();
    else if (cmd != "stop")
        cout << "Error: didn't recognize command. " << endl;
}

int main()
{
    cout << "Please enter your command: " << endl;
    string input [MAX_ARG];
    int arg_count;
    string cmd;
    bool valid_cmd;
    do
    {
        cin >> cmd;
        //                             
        choose_command(cmd);
    }
    while (cmd != "stop");
    return 0;
}

