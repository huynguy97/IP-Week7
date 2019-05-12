#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
using namespace std;

string words[1000];
string testwords[100];
string restofinput[500];

int read_and_count_words (ifstream& infile)
{
    int c=0;
    char s[100];
    while(infile)
    {
        infile >> s;
        for (int i=0; i<strlen(s); i++)
        {

            if (!((64<s[i] && s[i]<91) || (96<s[i] && s[i]<123) || s[i]=='\n')) //                                                                      
            {
                for (int j=i; j<strlen(s); j++)
                    s[j]=s[j+1];
                i--;
            }
            if (64<s[i] && s[i]<91)
                s[i]+=32;
        }
        if (!s[0]=='\0')            //                
        {
            words[c]=s;
            c++;
        }
    }
    c--;
    words[c]='\0';
    /*                          
                               
                                                    */
    return c;
}

bool open_file (ifstream& infile) //                          
{
    char input_file[50];
    assert(!infile.is_open());
    cout << "Input file: ";
    cin.getline(input_file, 80);
    infile.open(input_file);
    if (!infile.is_open())
    {
        cout << "Input file hasn't opened." << endl;
        return 0;
    }
    else
    {
        read_and_count_words(infile);
        return 1;
    }
}

void count_words()
{
    string wordstotest[200]
    cin.getline(wordstotest, 80)
    cout << "word" << '\t' << "occurrences" << '\t' << "total number of words" << '\t' << "percentage of occurrences";
    for (int k=0; k<sizeof(restofinput);k++)
    {
        int counter=0;
        for (int q=0; q<sizeof(words); q++)
        {
            if (restofinput[k]==words[q])       //                                                               
                counter++;
        }
        cout << restofinput[k] << '\t' << counter << '\t' << sizeof(words) << '\t' << (counter/sizeof(words))*100 << endl;
    }
}
//             
void where_words()
{
    for (int k=0; k<sizeof(restofinput);k++)
    {
        int counter=0;
        for (int q=0; q<sizeof(words); q++)
        {
            if (restofinput[k]==words[q])           //                                                                                    
                cout << q+1
        }
        cout << "the total number of places is: " << sizeof(words) << endl;
    }
}

void context_words()
{
    int m = (int)restofinput[0];
    for (int k=1; k<sizeof(restofinput);k++)
    {
        int counter=0;
        for (int q=0; q<sizeof(words); q++)
        {
            if (restofinput[k]==words[q])       //                                                                           
            {
                for (int i=k-m; i<=k+m; i++)
                    cout << words[i] << " ";
                cout << '\n';
            }
        }
        cout << "the total number of occurrences is: " << sizeof(words) << endl;
    }
}

void content()
{
    for (int k=0; k<sizeof(words);k++)
    {
        cout << words[k] << ' ';            //                                                    
    }
}

int main()
{
    int c;
    string command;
    ifstream Input_File;

    while (true)
    {
        cout << "What command do you want to do?";          //                                                                                                                     
        cin >> command;
        cin.ignore(1);
        cin.getline(restofinput, 500);

        //                          

        if (command == "enter")
            open_file(Input_File);
        else if (command=="count")
            count_words();
        else if (command=="where")
            where_words();
        else if (command=="context")
            context_words();
        else if (command=="content")
            content();
        else if (command=="stop")
            return 0;
        else
            cout << "Wrong input." << endl;
    }

    /*                                                                                         
                  
                      
     
                                                                                                                       
          
         
                        
                              
                
                                  
            
                          
                        
     */
    return 0;
}

