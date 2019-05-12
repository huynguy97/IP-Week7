#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

/*
                                     
                                     
 */

using namespace std;
const int MAX_WORDS = 30000;

void showArray(string words[MAX_WORDS], int& nmWords)
{
    //              
    assert(nmWords<=MAX_WORDS);
    //                                                          
    for (int i = 0; i < nmWords; i++) {
        cout << words[i] << " ";
    }

}

void readfile(ifstream& infile, string filein, string words[MAX_WORDS], int& nmWords)
{
    //              
    assert(!infile.is_open() && nmWords<=MAX_WORDS);
    //               
    //                                            
    string infilename = filein;
    infile.open(infilename);
    if(infile.is_open()){
        cout << "File opened successfully.\n";
        int i=0;
        while(infile && i < MAX_WORDS){
            infile >> words[i];
            i++;
        }
        nmWords = i-1;
    }
    else
    {
        cout << "File did not open.\n";
    }
infile.close();
}

int count(string words[MAX_WORDS], string seqArray[MAX_WORDS], int& nmWords, int& seqWords)
{
    //              
    assert(nmWords<=MAX_WORDS && seqWords<=MAX_WORDS);
    //               
    //                                                                          
    //                                                                                                                     
    //                                                                        
    //                                                                                          
    int q=0;
    int counter=0;
    for (int i = 0; i < nmWords; ++i) {
        if(words[i]==seqArray[q]){
            q++;
        }
        else
        {
            q=0;
            if(words[i]==seqArray[q]){
                q++;
            }
        }
        if(q==seqWords){
            counter++;
        }
    }
 return counter;
}

int where(string words[MAX_WORDS], string seqArray[MAX_WORDS], int& nmWords, int& seqWords)
{
    //              
    assert(nmWords<=MAX_WORDS && seqWords<=MAX_WORDS);
    //               
    //                                                                                                            
    int q=0;
    int counter=0;
    int index =0;
    for (int i = 0; i < nmWords; i++) {
        if(words[i]==seqArray[q]){
            q++;
        }
        else
        {
            q=0;
            if(words[i]==seqArray[q]){
                q++;
            }
        }
        if(q==seqWords){
            counter++;
            index = i - seqWords + 2;
            cout << "Index number: " << index << "\n";
        }
    }
    return counter;
}

int context(string words[MAX_WORDS], string seqArray[MAX_WORDS], int& nmWords, int& seqWords, int m)
{
    //              
    assert(nmWords<=MAX_WORDS && seqWords<=MAX_WORDS);
    //               
    //                                                                                                                              
    //                                                                      
    int q=0;
    int counter=0;
    int index =0;
    int start=0;
    int end=nmWords;
    for (int i = 0; i < nmWords; i++) {
        if(words[i]==seqArray[q]){
            q++;
        }
        else
        {
            q=0;
            if(words[i]==seqArray[q]){
                q++;
            }
        }
        if(q==seqWords){
            counter++;
            index = i - seqWords + 2;
            if(index-m-1>0){
                start=index-m-1;
            }
            if(i+m<=nmWords){
                end=i+m;
            }
            cout << "-";
            for (int j = start; j <= end; ++j) {
                cout << words[j] << ' ';
            }
            cout << '\n';
        }

    }
    return counter;
}

void interaction(string words[MAX_WORDS], int& nmWords, bool& stopFunc, string seqArray[MAX_WORDS], int& seqWords)
{
    //              
    assert(nmWords<=MAX_WORDS && seqWords<=MAX_WORDS && !stopFunc);
    //               
    //                                                        
    //                                                                              
    //                                                                                
    //                                                                                        
    ifstream input_file;
    string choice;
    string out;
    string filename;

    cout << "Please choose what you would like to do:\n";
    cout << "\t-Enter *filename*\n";
    cout << "\t-Content\n";
    cout << "\t-Count\n";
    cout << "\t-Where\n";
    cout << "\t-Context\n";
    cout << "\t-Stop\n";
    cin >> choice;

    if (choice == "Enter") { 
        cin.ignore(1);
        getline(cin, out, '\n');
        filename = out;
        readfile(input_file, filename, words, nmWords);
        cout << "The file contains " << nmWords << " words." <<endl;
}
    else if(choice=="Content"){
        showArray(words, nmWords);
    }
    else if(choice=="Count"){
        int i=0;
        while(cin.get() != '\n'){
            cin >> seqArray[i];
            i++;
        }
        seqWords=i;
        int occ = count(words, seqArray, nmWords, seqWords);
        cout << "The word sequence appears " << occ << " times.\n";
        cout << "The number of words is " << nmWords << ".\n";
        double perC = static_cast<double>(occ)/nmWords * 100;
        cout << "This is " << perC << "% of the words.\n ";
    }
    else if(choice=="Where"){
        int i=0;
        while(cin.get() != '\n'){
            cin >> seqArray[i];
            i++;
        }
        seqWords=i;
        int occ = where(words, seqArray, nmWords, seqWords);
        cout << "The number of occurrences is " << occ << ".\n";

    }
    else if(choice=="Context"){
        int i=0;
        int m=0;
        cin >> m;
        while(cin.get() != '\n'){
            cin >> seqArray[i];
            i++;
        }
        seqWords=i;

        int occ = context(words, seqArray, nmWords, seqWords, m);
        cout << occ;
    }
    else if(choice=="Stop"){
        stopFunc=true;
}
}

int main() {
    string words[MAX_WORDS];
    string seqArray[MAX_WORDS];
    int nmWords=0;
    int seqWords=0;

    bool stopFunc= false;
    while(!stopFunc) {
        interaction(words, nmWords, stopFunc, seqArray, seqWords);
        cout <<"\n \n";
    }
    return 0;
}
