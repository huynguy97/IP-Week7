#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;

//                                  
//                                  

bool stop = false;
string words[4000];
int amountwords =0;

void enter_filename(char userinput [80], int& amountwords)
{
    int i =0;
    char filename[80];
    while (userinput[i] != '\0')
    {
        filename[i] = userinput[i+6];
        i++;
    }
    ifstream inputfile (filename);
    if (inputfile.is_open())
    {
        char letter;
        char charword[50];
        i =0;
        int q =0;
        while (inputfile.get(letter))
        {
            if (letter != '\n' && int(letter) >32 && letter != '.' && letter != ',')
            {
                charword[i] = letter;
                i++;
            }
            if (int(letter) <= 32 || letter == '\n')
            {
                i =0;
                if (charword[i] != '\0')
                {
                    q++;
                    string word(charword);
                    words[q] = word;
                }
                for (i; i<50; i++)
                {
                    charword[i] = '\0';
                }
                i =0;
            }
        }

        amountwords = q;
        cout <<amountwords << endl << endl;

    }
    else
    {
        cout<<"The file didn't open properly, please try again." << endl << endl;
    }
}

void content()
{
    cout << amountwords;
    for (int i =0; i<=amountwords; i++)
    {
        cout<<words[i]<<" " << endl;
    }
    cout << endl;
}

void count(char userinput[80], int amountwords, string words[4000])
{
    char findwords[50];
    string find[400];
    int i =0;
    int q =0;
    int z =0;
    while (userinput[i+6] != '\0')
    {
        if (userinput[i+6] != ' ')
        {
            findwords[z] = userinput[i + 6];
            z++;
        }
        else if (userinput[i+6] == ' ')
        {
            string findword(findwords);
            find[q] = findword;
            q++;
            for (z =0; z<50; z++)
            {
                findwords[z] = '\0';
            }
            z =0;
        }
        i++;
    }
    string findword(findwords);
    find[q] = findword;
    q++;
    cout<<q<<endl;
    for (i =0; i<=q; i++)
    {
        cout<<find[i]<<endl;
    }

    int amount =0;
    for (i =0; i<=amountwords; i++)
    {
        if (words[i] == find[0])
        {
            for(int z =1;z<q;z++)
            {
                if (words[i+z] != find[z])
                {
                    z = q;
                }
                if (z == q-1)
                {
                    amount++;
                }
            }
        }
    }
    cout<<amount<<"  "<<amountwords<<"  "<<(amount/amountwords)*100;
}

void where(char userinput[40], int amountwords, string words[4000])
{
    char findwords[50];
    string find[400];
    int i =0;
    int q =0;
    int z =0;
    while (userinput[i+6] != '\0')
    {
        if (userinput[i+6] != ' ')
        {
            findwords[z] = userinput[i + 6];
            z++;
        }
        else if (userinput[i+6] == ' ')
        {
            string findword(findwords);
            find[q] = findword;
            q++;
            for (z =0; z<50; z++)
            {
                findwords[z] = '\0';
            }
            z =0;
        }
        i++;
    }
    string findword(findwords);
    find[q] = findword;
    q++;
    cout<<q<<endl;
    for (i =0; i<=q; i++)
    {
        cout<<find[i]<<endl;
    }
    int where[400];
    int amount =0;
    int k =0;
    for (i =0; i<=amountwords; i++)
    {
        if (words[i] == find[0])
        {
            for(int z =1;z<q;z++)
            {
                if (words[i+z] != find[z])
                {
                    z = q;
                }
                if (z == q-1)
                {
                    amount++;
                    where[k] = i;
                    k++;
                }
            }
        }
    }
    for (i =0; i<=k; i++)
    {
        cout<<where[i]<<endl;
    }
    cout<<amount;
}

int main()
{

    char userinput[80];
    while (!stop)
    {
        cout << "Please give your command?" << endl;
        cin.getline(userinput, 80);
        string input(userinput);
        if (input.find("enter ") == 0)
        {
            enter_filename(userinput, amountwords);
        }

        else if (input == "content")
        {
            content();
        }

        else if (input == "stop")
        {
            cout << "Your program has been stopped." << endl;
            stop = true;
        }

        else if (input.find("count ") ==0)
        {
            count(userinput, amountwords, words);
        }

        else if (input.find("where ") == 0)
        {
            where(userinput, amountwords, words);
        }

        else if (input.find("context ") == 0)
        {

        }

        else
        {
            cout<<"This is not a correct command" << endl << endl;
        }
    }
    return 0;
}

