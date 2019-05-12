#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <math.h>
using namespace std;

//                     

void split_up(char input[80], char command[20][20])
{
    //                                            
        assert(input && command);
        /*                                                                      
                                                                   
                                   
         */
    int i = 0;
    int j = 0;
    int k = 0;
    while (input[i])
    {
        if (input[i] == ' ')
        {
            command[j][k] = '\0';
            j++;
            k = -1;
        }
        else
        {
            command[j][k] = input[i];
        }
        i++;
        k++;
        command[j][k] = '\0';
    }
}

bool open_filename(char command[20][20], ifstream& inputfile)
{
    //                                                                                
        assert(true);
        /*                                                                 
                                                   
         */
    string filename;
    int i = 1;
    int j = 0;
    while(command[i][j])
    {
        while(command[i][j])
        {
                filename += command[i][j];
                j++;
        }
        filename += ' ';
        i++;
        j = 0;
    }
    filename += '\0';
    inputfile.open(filename.c_str());
    return inputfile.is_open();
}

int words_to_array(ifstream& inputfile, char words[50000][20])
{
    //                                                                                
        assert(inputfile);
        /*                                                                                 
                                         
         */
    int i = 0;
    while(inputfile)
    {
        inputfile >> words[i];
        i++;
    }
    cout << "\nThere are " << i << " words in this file.\n";
    return i;
}

void show_content(char words[50000][20])
{
    //                                                                                
        assert(true);
        /*                                                               
         */
    int i = 0;
    int j = 0;
    while(words[i][j])
    {
        while(words[i][j])
        {
            cout << words[i][j];
            j++;
        }
        cout << " ";
        i++;
        j=0;
    }
    cout << "\n";
}

void count_words(char command[20][20], char words[50000][20], int total_words)
{
    //                                                                                                              
        assert(true);
        /*                                                                       
                                                                                
                       
         */
    string commandstring;
    int i = 1;
    int j = 0;
    while(command[i][j]) //                                     
    {
        while(command[i][j])
        {
            commandstring += command[i][j];
            j++;
        }
        commandstring += ' ';
        j=0;
        i++;
    }
    string wordsstring;
    int k = 0;
    int l = 0;
    while(words[k][l]) //                                       
    {
        while(words[k][l])
        {
            wordsstring += words[k][l];
            l++;
        }
        wordsstring += ' ';
        l = 0;
        k++;
    }
    int q = 0;
    int r = 0;
    int p = 0;
    double counter = 0;
    while(wordsstring[q])
    {
        p = q;
        while(commandstring[r] && commandstring[r] == wordsstring[p]) //                                                                                         
        {
            p++;
            r++;
        }
        if(!commandstring[r]) //                                                                                
        {
            counter++;
        }
        r = 0;
        q++;
    }
    cout << "The string '" << commandstring << "' occurs " << counter << " times in this file"<< "\nThere are " << total_words << " in this file, that means that '" << commandstring << "' makes up " << (counter / total_words)*100 <<"% of the total words.\n";

}

void where_words(char command[20][20], char words[50000][20])
{
    //                                                                                
        assert(true);
        /*                                                                         
                                                                        
         */
    string commandstring; //                                                          
    int i = 1;
    int j = 0;
    while(command[i][j])
    {
        while(command[i][j])
        {
            commandstring += command[i][j];
            j++;
        }
        commandstring += ' ';
        j=0;
        i++;
    }
    string wordsstring;
    int k = 0;
    int l = 0;
    while(words[k][l])
    {
        while(words[k][l])
        {
            wordsstring += words[k][l];
            l++;
        }
        wordsstring += ' ';
        l = 0;
        k++;
    }
    int q = 0;
    int r = 0;
    int p = 0;
    double space_counter = 1; //                                                                                           
    double counter = 0;
    cout << "The string '" << commandstring << "' is found on the following location(s):\n";
    while(wordsstring[q])
    {
        p = q;
        if(wordsstring[q] == ' ')
        {
            space_counter += 1;
        }
        while(commandstring[r] && commandstring[r] == wordsstring[p])
        {
            p++;
            r++;
        }
        if(!commandstring[r])
        {
            cout << space_counter << "\n"; //                                                                                                  
            counter++;
        }
        r = 0;
        q++;
    }
    cout << "The string is found a total of " << counter << " times.\n";
}

int context_counter(char command[20][20])
{
    //                                                                                
        assert(true);
        /*                                                     
        */
    int i = 0;
    while(command[1][i])
    {
        i++;
    }
    int number = 0;
    int j = 0;
    while(command[1][j])
    {
        number += (command[1][j]-'0')*pow(10,i-1);
        i--;
        j++;
    }
    return number;
}

void context_words(char command[20][20], char words[50000][20])
{
    //                                                                                
        assert(true);
        /*                                                                                       
                                                                              
         */
    string commandstring; //                                                                                                                 
    int i = 2;
    int j = 0;
    int commandspaces = 0;
    while(command[i][j])
    {
        while(command[i][j])
        {
            commandstring += command[i][j];
            j++;
        }
        commandstring += ' ';
        commandspaces +=1;
        j=0;
        i++;
    }
    string wordsstring;
    int k = 0;
    int l = 0;
    while(words[k][l])
    {
        while(words[k][l])
        {
            wordsstring += words[k][l];
            l++;
        }
        wordsstring += ' ';
        l = 0;
        k++;
    }
    //                                                                                  
    int context = context_counter(command);
    int q = 0;
    int r = 0;
    int p = 0;
    double counter = 0;
    int space_counter = 1;
    cout << "The string '" << commandstring <<"' was found in the following contexts:\n";
    while(wordsstring[q])
    {
        p = q;
        if(wordsstring[q] == ' ')
        {
            space_counter += 1;
        }
        while(commandstring[r] && commandstring[r] == wordsstring[p])
        {
            p++;
            r++;
        }
        if(!commandstring[r]) //                                                                                                                                          
        {
            int z = 0;
            int y = 0;
            counter ++;
            while(wordsstring[z])
            {
                if(wordsstring[z] == ' ')
                {
                    y++;
                }
                if(y >= space_counter - context -1 && y <= space_counter + commandspaces + context - 2)
                {
                    cout << wordsstring[z];
                }
                z++;
            }
            cout << "\n";
        }
        r = 0;
        q++;
    }
    cout << "The string '" << commandstring <<"' was found a total of " << counter << " times\n";
}

bool choose_action(char command[20][20], ifstream& inputfile, char words [50000][20], bool& isopen, int& counter)
{
    //                                                                      
        assert(command && words);
        /*                                                                                   
                                                                                                       
         */
    string operation;
    int i = 0;
    while(command[0][i]) //                                                                                     
    {
        operation += command[0][i];
        i++;
    }
    if (operation == "enter") //                                                             
    {
        isopen = open_filename(command, inputfile);
        counter = words_to_array(inputfile, words);
        return true;
    }
    else if (operation == "content")
    {
        if(isopen)
        {
           show_content(words);
        }
        else
        {
            cout << "Please open a file first\n";
        }
        return true;
    }
    else if (operation == "count")
    {
        if(isopen)
        {
           count_words(command, words, counter);
        }
        else
        {
            cout << "Please open a file first\n";
        }
        return true;
    }
    else if (operation == "where")
    {
        if(isopen)
        {
           where_words(command, words);
        }
        else
        {
            cout << "Please open a file first\n";
        }
        return true;
    }
    else if (operation == "context")
    {
        if(isopen)
        {
           context_words(command, words);
        }
        else
        {
            cout << "Please open a file first\n";
        }
        return true;
    }
    else if (operation == "stop")
    {
        cout << "The programme will now terminate";
        return false;
    }
    else
    {
        cout << "Unknown command\n";
        return true;
    }
}

void clear_array(char command[20][20])
{
    //                                            
        assert(command);
        /*                                                
         */
    int i = 0;
    int j = 0;
    while(command[i][j])
    {
        while(command[i][j])
        {
            command[i][j] = '\0';
            j++;
        }
        j=0;
        i++;
    }
}

int main()
{
    char input[80]; //                                   
    char command[20][20];
    char words[50000][20];
    bool stop = true;
    bool isopen = false;
    int counter = 0;
    ifstream inputfile;
    while(stop) //                                       
    {
        cout << "Please use one of the following commands: \n1.enter [filename]\n2.content\n4.count [word1] ... [wordn]\n5.where [word1] ... [wordn]\n6.context m [word1] ... [wordn]\n7.stop\n";
        cin.getline(input, 80);
        cin.sync();
        split_up(input, command);
        stop = choose_action(command, inputfile, words, isopen, counter);
        clear_array(command); //                              
    }
    return 1;
}

