#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

//                                              
//                                               

using namespace std;
const int MAX_WORD_NUMBER   = 50000 ;

int enter_filename(string filename, ifstream& infile, string words_in_text[MAX_WORD_NUMBER])
{
    //              
    assert(!infile.is_open());
    //                                                                                     
    //                                                   
    //                                                                    

    infile.open ( filename.c_str() );

    if(!infile.is_open())
    {
        cout << "Invalid filename. Try Again." << endl << endl;
        return 0;
    }

    int number_of_words=0;
    while(infile&&number_of_words<MAX_WORD_NUMBER)
    {
        infile >> words_in_text[number_of_words];
        number_of_words++;
        }

    if (number_of_words>=MAX_WORD_NUMBER)
    {
        cout << "File is too long" << endl << endl;
        for (int i=0;i<MAX_WORD_NUMBER;i++)
        {
            words_in_text[i] = "";
        }
        infile.close();
        return 0;
    }
    cout << "Number of words in the file:" << number_of_words-1 << endl << endl;
    return number_of_words-1;
}

int get_sequence(string word_sequence[20])
{
    //             
    assert(true);
    //                                                                            
    char c;
    int i = 0;

    cin.get(c);
    while(c!='\n')
    {
        cin.get(c);
        if(c=='\n')
        {
        }
        else if(c!=' ')
        {
            word_sequence[i]=word_sequence[i]+c;
        }
        else
        {
            i++;
        }
    }
    return i;
}

int count_sequence(string sequence[20], string words_in_text[MAX_WORD_NUMBER], int number_of_words, int sequence_length, int locations[MAX_WORD_NUMBER])
{
    //             
    assert(number_of_words);
    //                                                                                                                                    
    int counts=0;
    for (int i=0;i<number_of_words;i++)
    {
        if (sequence[0]==words_in_text[i])
        {
            int k=0;
            for(int j=0;j<sequence_length;j++)
            {
                if(sequence[j]==words_in_text[i+j])
                {
                    k++;
                }
            }
            if(k==sequence_length)
            {
                locations[counts]=i+1;
                counts++;
            }
        }
    }
    return counts;
}

int main()
{
    string command, filename;
    ifstream input_file;
    string words_in_text[MAX_WORD_NUMBER];
    int word_number;

    while (command!="stop")
    {
        cout << "Enter one of the following commands:" << endl
            << "- enter 'filename' " << endl
            << "- content" << endl
            << "- count 'word 1 ... word n'" << endl
            << "- where 'word 1 ... word n'" << endl
            << "- context 'm word 1 ... word n'" << endl
            << "- stop" << endl << endl;

        cin >> command;
        if (command == "enter")
        {
            char c;
            cin.get(c);
            getline(cin,filename);
            word_number = enter_filename(filename, input_file, words_in_text);
            if(word_number == 0)
            {
                cout << "Opening file failed." << endl << endl;
            }
        }

        else if (command == "content")
        {
            if (!input_file.is_open())
            {
                cout << "First enter a file" << endl << endl;
            }
            else
            {
                for (int i=0;i<word_number;i++)
                {
                    cout << words_in_text[i] << " ";
                }
                cout << endl << endl;
            }

        }

        else if (command == "count")
        {
            if (!input_file.is_open())
            {
                cout << "First enter a file" << endl << endl;
            }
            else
            {
                int locations[MAX_WORD_NUMBER];
                string sequence[20];
                int sequence_length = get_sequence(sequence);
                int counts = count_sequence(sequence,words_in_text,word_number,sequence_length,locations);
                float percentage = ((float)counts/word_number*100);
                cout << "Occurrences \t Total Words \t Percentage" << endl
                    << counts << "\t \t" << word_number << "\t \t" << percentage << endl;
            }
        }

        else if (command == "where")
        {
            if (!input_file.is_open())
            {
                cout << "First enter a file" << endl << endl;
            }
            else
            {
                int locations[MAX_WORD_NUMBER];
                string sequence[20];
                int sequence_length = get_sequence(sequence);
                int counts = count_sequence(sequence,words_in_text,word_number,sequence_length,locations);

                cout << "Locations of this sequence:" << endl;
                for(int i=0;i<counts;i++)
                {
                    cout << locations[i] << " ";
                }
                cout << endl << "Number of found occurrences: " << counts << endl;
            }
        }

        else if (command == "context")
        {
            if (!input_file.is_open())
            {
                cout << "First enter a file" << endl << endl;
            }
            else
            {
                int m;
                cin >> m;
                string sequence[20];
                //                                         
                //                                     

                int locations[MAX_WORD_NUMBER];
                int sequence_length = get_sequence(sequence);
                int counts = count_sequence(sequence,words_in_text,word_number,sequence_length,locations);

                for(int i=0;i<counts;i++)
                {
                    for(int j=max(locations[i]-m-1,0);j<locations[i]+sequence_length+m&&j<word_number;j++)
                    {
                        cout << words_in_text[j] << " ";
                    }
                    cout << endl;
                }
            }
        }

        else if (command != "stop")
        {
            cout << "Invalid command, try again" << endl << endl;
        }

    //                                                                                     

    }

    return 0;
}

