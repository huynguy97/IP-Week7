#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

/*
                            
                          
*/

ifstream infile;
string words;
string allWords;
string indexWords;

bool file_is_open(ifstream& infile){

    cout << "enter file name: " ;\
    char filename[100];
    cin.getline(filename, 100, '\n');
    infile.open(filename);

    return infile.is_open();

    //                                                            
}

void check_word_content(ifstream& infile){
    assert(infile.is_open());
    int wordCount = 0;
    while(infile >> allWords){
        cout << allWords + " ";
        allWords.append(allWords + " ");
        wordCount++;

    }

    cout << "\n";

    infile.clear();
    infile.seekg(0, ios::beg);

    //                                                            
    //                       
}

void check_specific_word_count(ifstream& infile, string c){
    assert(infile.is_open() && c.length() > 0);
    int specificWord = 0;
    int maxWords = 0;

    while(infile >> words){
        maxWords++;
        if(words == c){
            specificWord++;
        }
    }

    infile.clear();
    infile.seekg(0, ios::beg);

    float percentage = ((float)specificWord/(float)maxWords)*100;
    cout << c << "\t" << "total" << "\t" << "% " << c << " in total"<< endl;
    cout << specificWord << "\t" << maxWords << "\t" << percentage << "%" << endl;

    /*
                                                                          
                                                                 
    */
}

void check_specific_word_index(ifstream& infile, string c){
    assert(infile.is_open() && c.length() > 0);
    int wordIndex = 0;
    int wordAmount = 0;

    while(infile >> indexWords){
        wordIndex++;
        if(indexWords == c){
            cout << c << " appears at index " << wordIndex << endl;
            wordAmount++;
        }
    }

    cout << c << " occurs " << wordAmount << " times" << endl;

    infile.clear();
    infile.seekg(0, ios::beg);

    /*
                                                      
                                                          
    */

}

void check_specific_word_context(ifstream& infile, string c, int m){
    assert(infile.is_open() && c.length() > 0 && m > 0);
    bool context = false;
    int x = m;
    int occurences = 0;
    while(infile >> words){
        if(words == c){
            context = true;
            occurences++;
        }

        if(context){
            cout << words << " ";
            x--;
        }

        if(x == -1){
            x = m;
            cout << "\n";
            context = false;
        }
    }

    cout << c << " occurs " << occurences << " times";
    infile.clear();
    infile.seekg(0, ios::beg);

    /*
                                                                              
                                                                           
                                  
    */
}
int main()
{
    int words;
    int choice;
    int contentX;
    char whatWord[100];
    file_is_open(infile);

    cout << "What word do you want to check?: " << endl;
    cin.getline(whatWord, 100, '\n');

    cout << "Do you want to execute the (1) Content, (2) Count, (3) Where or (4) Context function?: " << endl;

    cin >> choice;

    switch(choice){
        case 1: check_word_content(infile); break;
        case 2: check_specific_word_count(infile, whatWord); break;
        case 3: check_specific_word_index(infile, whatWord); break;
        case 4: cout << "How many words do you want to print ahead?" << endl;
                cin >> contentX;
                check_specific_word_context(infile, whatWord, contentX);
                break;
        }
}

