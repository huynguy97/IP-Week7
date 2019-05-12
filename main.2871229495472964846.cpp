#include <iostream>
#include <fstream>
#include <cassert>
//                              

using namespace std;

int main()
{
    //               
        assert(true);
    /*                
                  
                                                                                                           
                                                                                                            
                                        
                                                                                                                  
                                                                                                                     
                                                                                   
    */
    int no_words = 0;
    char filename[80];
    cout << "Enter the name of file you wish to open: " << endl;
    cin.getline(filename, 80);
    ifstream infile;
    infile.open(filename);

    if (!infile.is_open())
        cout << "Error! File with entered name was not found. " << endl;

    else
    {
        char word[50];
        infile >> word;
        while (infile.is_open())
        {
            if (infile.eof())
                infile.close();
            else
            {
            cout << word << " ";
            infile >> word;
            no_words++;
            }
        }
        cout << '\n' << '\n' <<"The number of words read is : " << no_words << endl;
        cout << '\n' <<"Press 1 if you want to count the number of occurrences of the word sequence."
             << '\n' <<"Press 2 if you want to stop the program." << endl;
        int command;
        cin >> command;
        switch (command)
        {
            case 1:
            {
                int no_word_seq = 0;
                cout <<"Please enter the word sequence you want to count: " << endl;
                string word_seq;
                cin >> word_seq;
                infile.open(filename);
                infile >> word;
                while (infile.is_open())
                {
                    if (infile.eof())
                        infile.close();
                    else
                    {
                        infile >> word;
                        if (word == word_seq)
                        no_word_seq++;
                    }
                }
                double a;
                double b;
                a = no_word_seq;
                b = no_words;
                double perc;
                perc = (a / b) * 100;
                cout <<"The number of word sequence is: " << no_word_seq << endl;
                cout <<"The total number of words is: " <<no_words << endl;
                cout <<"The percentage of word sequence out of total number of words is: " << perc << endl;
            }
                break;
            case 2:
                cout <<"The program terminates." << endl;
                break;
        }

    }
    return 0;
}

