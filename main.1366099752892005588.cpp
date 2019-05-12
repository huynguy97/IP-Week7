#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

//                                                       

bool openfile(ifstream& file){
    string filename;
    cout << "enter filename please" << endl;
    cin >> filename;
    file.open(filename.c_str());
    return file.is_open();
}

int countwords(char arrayinput[]){
    int place = 0;
    int numberwords = 1;
    while (!(arrayinput[place] == '0')){
        if (arrayinput[place] == ' '){
            numberwords ++;
        }
        place++;
    }

    cout << "number of words = " << numberwords << endl;
    return numberwords;
}

void countthewords(char thewords[], char text[], int lengthA){
    int totalcount = 0;
    int truecount = 0;
    int place = 0;
    while (!(text[place] == '0')){
        cout << text[place];
        for (int i=0; i < lengthA; i++){
            if (!(text[place + i] == thewords[i]))
                truecount++;
        }
        if (truecount == 0)
            totalcount++;
        truecount = 0;
        place++;
    }

    cout << totalcount;
}
//                                                                                                          
void wherethewords(char thewords[], char text[], int lengthA){
    string newtext[1000];
    string newthewords[100];
    int place = 0;
    int point = 0;
    string input;
    while(!(text[place] == '0')){
        if (text[place] == ' '){
            newtext[point] = input;
            input = "";
            point++;
        }
        else{
        input = input + text[place];
        }
    place++;
    }
    newtext[point] = "0";
//                                                                 
    place = 0;
    point = 0;
    input;
    while(!(thewords[place] == '0')){
        if (thewords[place] == ' '){
            newthewords[point] = input;
            input = "";
            point++;
        }
        else{
        input = input + thewords[place];
        }
    place++;
    }
    newthewords[point] = "0";
    int i = 0;
    int j = 0;
    while (!(newthewords[j] == "0")){
        cout << newthewords[j] << " ";
        while (!(newtext[i] == "0")){
        cout << newtext[i];
        if (newtext[i] == newthewords[j])
            cout << i << "";
        i++;
        }
    j++;
    }
    }

int main(){
    ifstream file;
    if (!openfile(file))
        cout << "couldn't open file";
    int number = 0;
    char inputstring[100000];
    while (!file.eof()){
        inputstring[number] = file.get();
        number++;
    }
    cout << inputstring;
    inputstring[number] = '0';
    countwords(inputstring);

    string command;
    string word;

    cout << "enter a command (count)" << endl;
    cin >> command;
    getline(cin, word);
    int lengthA = word.size();

    char thewords[lengthA];
    strcpy(thewords, word.c_str());
    cout << thewords;

    if (command == "count")
        countthewords(thewords, inputstring, lengthA );
    if (command == "where")
        wherethewords(thewords, inputstring, lengthA);
}

