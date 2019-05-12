#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

//                                                        
//                                                  

const int MAX_LENGTH=10000;

bool read_word(char filename [MAX_LENGTH],ifstream& infile, string word [MAX_LENGTH],int& counter)
{
//               
    assert (true);
//                                                                                        

    cout<< "Please enter file name: ";

    char a;
    int c=6;
    cin.get(a);
    while(c!=5)
    {

        filename[counter]=a;
        counter++;
        cin.get(a);
        if(a=='.')
        {
            c=0;
        }
        c++;
    }
    string name;
    for(int i=0; i<counter; i++)
    {
        name=name+filename[i];
    }

    infile.open(name.c_str());

    char d [MAX_LENGTH];
    counter =0;
    do
    {
        infile >> d;
        word[counter]=d;
        counter++;
    }
    while(infile);
    counter--;

    if(infile.is_open())
        return true;
    else
        return false;
}

void letters_transformation (char filename [MAX_LENGTH],ifstream& infile, string word [MAX_LENGTH],int& counter)
{
    int number=0;
    if( read_word(filename,infile,word,counter))
        number=counter;
    else
        cout<<"error";
    for(int i=0; i<number; i++)
    {
        string word_1=word[i];
        char check_1= word_1[0];
        if (check_1>65 && check_1<90)
        {
            check_1=check_1+32;
            word[i]=word_1;

            word_1[0]=check_1;
            word[i]=word_1;
        }

        int length_1 =word_1.length()-1;
        char check_2 =word_1[length_1];
        if(check_2<97 || check_2>122)
        {
            word_1.erase(word_1.size()-1,1);
            word[i]=word_1;
        }
    }

}

void count_words (string word [MAX_LENGTH],string choice,char filename [MAX_LENGTH],ifstream& infile,int& counter)
{
    cout<<"Which word are you looking for";
    letters_transformation(filename,infile,word,counter);
    int no=0;
    for(int i=0; i<counter; i++)
    {
        if (word[i]==choice)
            no++;
    }
    cout<<"The word "<<choice<<" appears "<<no<<" times"<<endl;
}

void position_word (string word [MAX_LENGTH],string choice,char filename [MAX_LENGTH],ifstream& infile,int& counter)
{
    cout<<"Which words are you looking for?"
        letters_transformation(filename,infile,word,counter);
    int position[MAX_LENGTH];
    int counter_2=0;
    for(int i=0; i<counter; i++)
    {
        if (word[i]==choice)
        {
            position [counter_2]=i;
            counter_2++;
        }

    }
    for(int i=0; i<counter_2; i++)
    {
        cout<<"The word appears in position " <<position [i]<<endl;
    }
    cout<<"The word appears "<<counter<<" times "<<endl;
}

int main()
{
    ifstream infile;
    string word [MAX_LENGTH];
    char filename [MAX_LENGTH];
    string choice [MAX_LENGTH];
    int choice_nos=0;
    string cut;
    int counter=0;
    cout<<"What do you want to do?"<<endl;
    int a=0;
    getline(cin,cut);
    int pos_of_space=cut.find(' ');
    for(int i=0; pos_of_space<cut.size(); i++)
    {
        choice[i]=cut.substr(a,pos_of_space);
        choice_nos++;
        cut = cut.substr(pos_of_space+1,cut.size()-1);
        pos_of_space=cut.find(' ',pos_of_space+1);
        if(cut.find(' ')==-1)
        {
            choice[i+1]=cut;
            choice_nos++;
        }

    }
    for(int i=0; i<5; i++)
        cout<<choice[i]<<endl;
    cout<<choice_nos<<endl;

    if(choice[0]=="enter")
    {
        if (read_word(filename,infile,word,counter))
            cout<<"File was open successfully, and the number of words is: "<<counter<<endl;
        else
            cout<<"File was not open successfully."<<endl;
    }
    else if(choice[0]=="content")
    {
        if(read_word(filename,infile,word,counter))
            for(int i=0; i<counter; i++)
                cout<<word[i]<<" ";
        else
            cout<<"File was not open successfully.";
    }
    else if(choice[0]=="stop")
        return 0;
    else if(choice[0]=="count")
    {
        for(int i=1; i<choice_nos; i++)
            count_words(word,choice[1],filename,infile,counter);
    }
    else if(choice[0]=="where")
        for(int i=0; i<choice_nos; i++)
            position_word(word,choice[i],filename,infile,counter);
    else if(choice[0]=="context")
        cout<<"not implemented yet";
    else
        cout<<"that is not a valid method";

    return 0;
}

