//                                                 
//                                            

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_FILENAME_LENGTH = 50 ;              //                                                                                   
ifstream infile;
char filename[MAX_FILENAME_LENGTH];
string searchwords[MAX_FILENAME_LENGTH];
string word;
string wordcount[31000];
int no_of_words;
int counter;

bool enter_filename (char filename [MAX_FILENAME_LENGTH], ifstream& infile)
{
    //              
    assert (!infile.is_open ());
    //               
    //                                                                                             
    //                                                                         

    bool break_out = false;

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH && !break_out)
    {
        cin.get (C);
        if (C == ' ' && c < 2)
        {
            cin.get (C);
        }
        if (C == '\n')
        {
            break_out = true;
            filename[c] = '\0';
            cout << filename;
            cout << "\nFilename successfully entered" << endl;
            infile.open(filename);
            if (infile.is_open())
                cout << "File successfully opened." << endl;
            return break_out;
        }
        else
        {
           filename[c] = C;
        }

        c++;
    }
        cout << "Error. Filename not entered successfully" << endl;
        return break_out;
}

void action_enter(ifstream& infile)
{
    //             
    assert (infile.is_open());

    //              
    //                                                                              

    for  (no_of_words=0; !infile.eof(); no_of_words++)
    {
       infile >> word;
       wordcount[no_of_words] = word;
    }

    cout << "Number of words: " << no_of_words << endl;
}

void action_content(ifstream& infile)
{
    //             
    assert (infile.is_open());

    //              
    //                               

    int a;

    for  (a = 0; !infile.eof(); a++)
    {
       infile >> word;
       wordcount[a] = word;
    }

    for (int i = 0; i < a; i++)
    {
        cout << wordcount[i] << " ";
    }

}

int amount_words()
{
    //              
    assert (true);

    //               
    //                                                               
    int c = 0;
    char C;
    int space = 1;
    while (c < 50)
    {
        cin.get(C);

        if (C == ' ')
        {
            cin.get (C);
            space++;
        }
    }
    return space;
}

void action_count(string searchwords [MAX_FILENAME_LENGTH])
{
    //              
    assert (true);

    //               
    //                                                                                                            
    //                                                      

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH)
    {
        cin >> searchwords[c];
        cin.get (C);
        if (C == ' ')
        {
            cin.get (C);
        }
        else if (C == '\n')
        {
            c = MAX_FILENAME_LENGTH;
        }

        c++;
    }

    counter = 0;
    int amount_of_words = amount_words();

    for (int i = 0; i < no_of_words; i++)
    {
        bool found = true;
            for (int k = 0; k < amount_of_words; k++)
            {
                if (searchwords[k] != wordcount[i+k])
                {
                    found = false;
                }

            }
        if (found){
            counter++;
        }
    }

    cout << counter << "-" << no_of_words << "-" << (counter/no_of_words)*100 << "%" << endl;

}

void action_context(int m)
{
    //              
    assert (true);

    //               
    //                                                                                                                    
    //                                                              

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH)
    {
        cin >> searchwords[c];
        cin.get (C);
        if (C == ' ')
        {
            cin.get (C);
        }
        else if (C == '\n')
        {
            c = MAX_FILENAME_LENGTH;
        }

        c++;
    }
    int k;
    counter = 0;
    int amount_of_words = amount_words();

    for (int i = 0; i < no_of_words; i++)
    {
        bool found = true;
            for (k = 0; k < amount_of_words; k++)
            {
                if (searchwords[k] != wordcount[i+k])
                {
                    found = false;
                }

            }
        if (found){
            cout << searchwords[k-m] << " " << searchwords[k] << " " << searchwords[k+m] << ", " << endl;
            counter++;
        }
    }
}

void action_where()
{
    //             
    assert (true);

    //               
    //                                                                                                                                     

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH)
    {
        cin >> searchwords[c];
        cin.get (C);
        if (C == ' ')
        {
            cin.get (C);
        }
        else if (C == '\n')
        {
            c = MAX_FILENAME_LENGTH;
        }

        c++;
    }
    int k;
    counter = 0;
    int amount_of_words = amount_words();

    for (int i = 0; i < no_of_words; i++)
    {
        bool found = true;
            for (k = 0; k < amount_of_words; k++)
            {
                if (searchwords[k] != wordcount[i+k])
                {
                    found = false;
                }

            }
        if (found){
            cout << k << ", ";
            counter++;
        }
    }
}

void user_input ()
{
    //              
    assert (true);

    //              
    //                                                                 
    cout << "\nPlease enter your choice: " << endl;
    string answer;
    cin >> answer;

    if (answer == "content" || answer == "Content")
    {
        cout << "You chose the action 'content'." << endl;
        enter_filename(filename, infile);
        action_content(infile);
    }

    if (answer == "context" || answer == "Context")
    {
        cout << "You chose the action 'context'." << endl;
        cout << "Please give a value for m" << endl;
        int value_m;
        cin >> value_m;
        action_context(value_m);
    }

    if (answer == "count" || answer == "Count")
    {
        cout << "You chose the action 'count'." << endl;
        action_count(searchwords);
        cout << counter << "-" << no_of_words << "-" << (counter/no_of_words)*100 << "%" << endl;

    }

    if (answer == "enter" || answer == "Enter")
    {
        cout << "You chose the action 'enter'." << endl;
        enter_filename(filename, infile);
        action_enter(infile);
    }

    if (answer == "where" || answer == "Where")
    {
        cout << "You chose the action 'where'." << endl;
        action_where();
    }

    if (answer == "stop" || answer == "Stop")
    {
        cout << "You terminated the program." << endl;
        return;
    }

}

int main()
{
    cout << "\nYou may choose the following options: content, context, count, enter, where, or stop" << endl;
    cout << "- Content: displays all the stored words in their order of appearance." << endl;
    cout << "- Context: displays all occurrences of the word sequence and the number of found occurrences." << endl;
    cout << "- Count: displays the number of occurrences of the word, the total number of words and the number of words as percentage terms" << endl;
    cout << "- Enter: opens a file and displays the number of words read." << endl;
    cout << "- Where: displays all index-positions of the occurrences of the word sequence and the number of found occurrences." << endl;
    cout << "- Stop: the program terminates." << endl;

    int run = 0;

    while (run < 10)
    {
        user_input();
        run++;
    }

    return 0;
}

