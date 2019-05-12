#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <string>
using namespace std;

int enter (ifstream& infile, string words[], int& array_size)
{
    assert(true);
    //                                                                                            
    int number = 0;
    char filename[1000], a;
    char line[100];
    cin.ignore(80, '\n');
    string repeatable;
    cin.getline(filename,100,'\n');
    infile.open(filename);
    while(infile)
    {
        infile.get(a);
        if(int(a) > 64 && int(a) < 91 || int(a) > 96 && int(a) < 123 || int(a) == 39)
        {
            repeatable = repeatable + a;
        }
        else
        {
            if(repeatable!="")
            {
                words[array_size] = repeatable;
                array_size++;
                repeatable = "";
            }
        }
    }
    return array_size;
}

void content(string words[],int array_size)
{
    assert(true);
    //                                                                           
        for(int i=0;i<array_size;i++)
        {
            cout << words[i] <<endl;
        }
}

void duplication(string words[] ,string duplicate_array[], int array_size)
{
    assert(true);
    //                                                    
    for(int i = 0; i < array_size; i++)
    {
        duplicate_array[i] = words[i];
    }

}

void Count(string words[],int array_size,string duplicate_array[])
{
    assert(true);
    //                                                                                                            
    //                                                              
    duplication(words,duplicate_array,array_size);
    int second_array_count=0;
    for(int i=0;i<array_size;i++)
    {
        double occurance_count =1;
        for(int u=i+1;u<array_size;u++)
        {
            if(duplicate_array[i]!="0")
            {
                if(duplicate_array[i]==duplicate_array[u])
                {
                    occurance_count++;
                    duplicate_array[u]="0";
                }
            }

        }
            if(duplicate_array[i]!="0")
        {
            cout << duplicate_array[i] << "," << occurance_count <<","<< array_size <<"," << (occurance_count/array_size*100)<< "%"<< endl;
            second_array_count++;

        }
    }
}

 void where(string words[],int array_size, string duplicate_array[])
 {
     assert(true);
     //                                               
     duplication(words,duplicate_array,array_size);
     for(int i = 0; i < array_size; i++)
     {
         if(duplicate_array[i] != "")
         {
             cout << duplicate_array[i] << " " << i+1 <<" ";
             for (int y = i+1; y < array_size; y++)
             {
                 if(duplicate_array[i] == duplicate_array[y])
                 {
                     duplicate_array[y] = "";
                     cout << y+1 << " ";
                 }
             }
             cout<<endl;
         }
         else i++;
     }
 }
void context(string words[],int array_size)
{
    assert(true);
    //                                                                                                                       
    int repeats = 0, all = 0;
    for(int i = 0; i < array_size; i++)
    {
        cout << words[i] << " ";
        if(i != 0)
        {
            for(int y = 0; y < i; y++)
            {
                if(words[i] == words[y])
                {
                    repeats++;
                }
            }
            cout << "before occurs " << repeats << " ";
            all = all + repeats;
            repeats = 0;
        }
        else cout << "before occurs " << 0 << " ";
        for(int y = i+1; y < array_size; y++)
        {
            if(words[i] == words[y])
                {
                    repeats++;
                }
        }
        all = all + repeats;
        cout << "after it occurs " << repeats << " ";
        cout <<"in total it occurs "<< all << " times" <<endl;
        repeats = 0;
        all = 0;
    }
}
int main()
{
    ifstream infile;
    static string words[40000], duplicate_array[40000];
    int action=0;
    bool state= true;
    int array_size=0;
    cout << "1. enter 2. content 3.count 4.where 5.context 0.shut down" << endl;
    cout << "input number of a function you want to use: " << endl;
    while(state)
    {
        cin >> action;
        switch(action){
        case 0:
            state =false;
            break;
        case 1:
            enter(infile,words,array_size);
           break;
        case 2:
            content(words,array_size);
            break;
        case 3:
            Count(words,array_size,duplicate_array);
            break;
        case 4:
            where(words,array_size,duplicate_array);
            break;
        case 5:
            context(words,array_size);
            break;
        }
    }
}

