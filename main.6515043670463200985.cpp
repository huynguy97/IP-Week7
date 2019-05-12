#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;
//                                                                                  

const int MAX_CMD_SIZE = 1000;
const int MAX_WORD_SIZE = 50;
enum CMD {Enter, Content, Stop, Count, Where, Context, ERROR};
const int MAX_WORDS = 10000;

char textData[MAX_WORDS][MAX_WORD_SIZE];
bool KeepRunningProgram = true;
int wordsInTextData = 0;

void clearCharArray(char data[MAX_WORDS][MAX_WORD_SIZE])
{
    for (int i = 0; i < MAX_WORDS; i++){
        for (int j = 0; j < MAX_WORD_SIZE; j++){
            data[i][j] = '\0';
        }
    }
}

int seq_search(char data[], int from, int to, char item)
{
    //               
    assert(from >= 0 && to >= 0);
    //                                                                                                                          
    if (from > to) {//                   
        return to+1;
    }

    int index = from;
    while (index <= to && data[index] != item){
        index++;
    }
    return index;
}

void partialStringCopy(char from [], char to [], int startIndex, int endIndex, int fromArrayLength, int toArrayLength)
{
    //                                                                                                                                                                  
    //                                        
    assert(startIndex >= 0 && endIndex >= startIndex && startIndex < fromArrayLength && endIndex < fromArrayLength && (endIndex - startIndex + 1) < toArrayLength);
    //                                                                                                                                                             
    int toIndex = 0;
    for (int i = startIndex; i <= endIndex; i++){
        to[toIndex] = from[i];
        toIndex++;
    }
    //                                     
    to[toIndex] = '\0';
}

CMD getCommandType(char input [MAX_CMD_SIZE])
{
    //             
    assert (MAX_CMD_SIZE>0 && MAX_WORD_SIZE >0);
    //               
    //                                               
    int firstSpaceIndex = seq_search(input,0,MAX_CMD_SIZE-1,' ');
    if (firstSpaceIndex >= MAX_CMD_SIZE || firstSpaceIndex == 0)
    {
        return ERROR;
    }
    char cmd [MAX_WORD_SIZE]; //                                     
    partialStringCopy (input, cmd, 0, firstSpaceIndex-1, MAX_CMD_SIZE, MAX_WORD_SIZE);
    if (strcmp(cmd, "enter")==0)
    {
        return Enter;
    }
    else if (strcmp(cmd, "content")==0)
    {
        return Content;
    }
    else if (strcmp(cmd, "stop")==0)
    {
        return Stop;
    }
    else if (strcmp(cmd, "count")==0)
    {
        return Count;
    }
    else if (strcmp(cmd,"where")==0)
    {
        return Where;
    }
    else if (strcmp(cmd, "context")==0)
    {
        return Context;
    }
    else
    {
        return ERROR;
    }
}

bool cmdEnter(char input [MAX_CMD_SIZE])
{
    clearCharArray(textData);
    ifstream fin;
    char fName [MAX_CMD_SIZE];
    int from = seq_search(input, 0, MAX_CMD_SIZE-1,' ');
    partialStringCopy(input, fName, from+1, MAX_CMD_SIZE-1, MAX_CMD_SIZE, MAX_CMD_SIZE);
    fin.open(fName);
    cout << "File: " << fName << endl;
    if (fin.is_open())
    {
        cout << " opened file" << endl;
        int counter = 0;
        while (!fin.eof())
        {
           fin >> textData[counter];
           counter ++;
        }
        cout <<"number of words in file_"<< counter << endl;
        wordsInTextData = counter;
        return true;
    }
    else
    {
        cout << " an error occured" << endl;
        return false;
    }

}

int readWordsFromStringPos(char str[], int strMaxLength, int startPos, int nMaxSearchWords, char SWords [][MAX_WORD_SIZE])
{
    //              
    assert(strMaxLength > 0 && startPos < strMaxLength && nMaxSearchWords > 0);
    //                                                                                                                                                 
    int endIndex = seq_search(str,0,strMaxLength-1,'\0');
    int i = startPos;

    int wordCounter = 0;

    while (i < endIndex && wordCounter < nMaxSearchWords){
        int nextSpace = seq_search(str,i,endIndex, ' ');
        if (nextSpace == i){
            i++; //                                         
        } else {
            //                                          
            if (nextSpace == endIndex+1){ //                                           
                partialStringCopy(str,SWords[wordCounter],i,endIndex-1,strMaxLength,MAX_WORD_SIZE); //                                                        
                wordCounter++;
                i = endIndex; //                            
            } else {
                partialStringCopy(str,SWords[wordCounter],i,nextSpace-1,strMaxLength,MAX_WORD_SIZE); //                   
                wordCounter++;
                i=nextSpace+1;
            }
        }
    }

    return wordCounter-1; //                                                              
}

bool cmdCount(char input [MAX_CMD_SIZE])
{
    //              

    if(wordsInTextData == 0){
        cout << "Please enter a file first" << endl;
        return false;
    }

    const int nSearchWords = 100;
    char SWords [nSearchWords][MAX_WORD_SIZE];
    int firstSpaceIndex = seq_search(input, 0, MAX_CMD_SIZE-1, ' ');

    if (firstSpaceIndex >= MAX_CMD_SIZE){
        return false;//     
    }

    int nRead = readWordsFromStringPos(input,MAX_CMD_SIZE,firstSpaceIndex,nSearchWords,SWords);
    if (nRead < 0){
        //                          
        cout << "Error: no words to check" << endl;
        return false;
    }

    int matchesFound = 0;

    //                                                     
    for (int twIndex = 0; twIndex < MAX_WORDS; twIndex++){
        if (strcmp(textData[twIndex],SWords[0]) == 0) {//                     
            bool allEqual = true;
            int compareCounter = 1;
            while (allEqual && compareCounter <= nRead && (twIndex+compareCounter) < MAX_WORDS){ //                                                    
                if (strcmp(textData[twIndex+compareCounter],SWords[compareCounter]) != 0){
                    //                                                          
                    allEqual = false;
                }
                compareCounter++;
            }
            //                                                     
            if ((twIndex+compareCounter) >= MAX_WORDS){
                allEqual = false;
            }

            //                                                           
            matchesFound++;
        }
    }
    cout << "Found " << matchesFound << " matches in a text of " << wordsInTextData << " which is " << static_cast<double>(matchesFound)/wordsInTextData*100.0 << "%." << endl;
    return true;
}

bool cmdWhere(char input [MAX_CMD_SIZE])
{
    //              

    if(wordsInTextData == 0){
        cout << "Please enter a file first" << endl;
        return false;
    }

    const int nSearchWords = 100;
    char SWords [nSearchWords][MAX_WORD_SIZE];
    int firstSpaceIndex = seq_search(input, 0, MAX_CMD_SIZE-1, ' ');

    if (firstSpaceIndex >= MAX_CMD_SIZE){
        return false;//     
    }

    int nRead = readWordsFromStringPos(input,MAX_CMD_SIZE,firstSpaceIndex,nSearchWords,SWords);
    if (nRead < 0){
        //                          
        cout << "Error: no words to check" << endl;
        return false;
    }

    int matchesFound = 0;

    //                                                     
    for (int twIndex = 0; twIndex < MAX_WORDS; twIndex++){
        if (strcmp(textData[twIndex],SWords[0]) == 0) {//                     
            bool allEqual = true;
            int compareCounter = 1;
            while (allEqual && compareCounter <= nRead && (twIndex+compareCounter) < MAX_WORDS){ //                                                    
                if (strcmp(textData[twIndex+compareCounter],SWords[compareCounter]) != 0){
                    //                                                          
                    allEqual = false;
                }
                compareCounter++;
            }
            //                                                     
            if ((twIndex+compareCounter) >= MAX_WORDS){
                allEqual = false;
            }

            //                                                           
            matchesFound++;
            cout << "Match at: " << twIndex+1 << endl;
        }
    }
    cout << "Found " << matchesFound << " in total." << endl;
    return true;
}

void printContextAt(int pos, int m){
    //              
    assert(m >= 0);
    //                                                                          

    if(wordsInTextData == 0){
        cout << "Please enter a file first" << endl;
        return;
    }

    for (int i = max(0,pos-m); i < min(wordsInTextData,pos+m+1); i++){
        cout << textData[i] << " ";
    }
    cout << endl;
}

bool cmdContext(char input [MAX_CMD_SIZE])
{
    //              

    if(wordsInTextData == 0){
        cout << "Please enter a file first" << endl;
        return false;
    }

    const int nSearchWords = 100;
    char SWords [nSearchWords][MAX_WORD_SIZE];
    int firstSpaceIndex = seq_search(input, 0, MAX_CMD_SIZE-1, ' ');

    if (firstSpaceIndex >= MAX_CMD_SIZE){
        return false;//     
    }

    //      
    int secondSpaceIndex = seq_search(input, firstSpaceIndex+1, MAX_CMD_SIZE-1, ' ');
    if (secondSpaceIndex >= MAX_CMD_SIZE || secondSpaceIndex == (firstSpaceIndex+1)){
        cout << "Please enter: *context_#_words*, where _ is a space and # a positive number." <<endl;
        return false;//     
    }

    char numberString[MAX_WORD_SIZE];
    partialStringCopy(input,numberString,firstSpaceIndex+1,secondSpaceIndex-1,MAX_CMD_SIZE,MAX_WORD_SIZE);
    int m = atoi(numberString);
    if (m < 0){
        cout << "Please enter a positive amount" << endl;
        return false;
    }

    int nRead = readWordsFromStringPos(input,MAX_CMD_SIZE,secondSpaceIndex,nSearchWords,SWords);
    if (nRead < 0){
        //                          
        cout << "Error: no words to check" << endl;
        return false;
    }

    int matchesFound = 0;

    //                                                     
    for (int twIndex = 0; twIndex < MAX_WORDS; twIndex++){
        if (strcmp(textData[twIndex],SWords[0]) == 0) {//                     
            bool allEqual = true;
            int compareCounter = 1;
            while (allEqual && compareCounter <= nRead && (twIndex+compareCounter) < MAX_WORDS){ //                                                    
                if (strcmp(textData[twIndex+compareCounter],SWords[compareCounter]) != 0){
                    //                                                          
                    allEqual = false;
                }
                compareCounter++;
            }
            //                                                     
            if ((twIndex+compareCounter) >= MAX_WORDS){
                allEqual = false;
            }

            //                                                           
            matchesFound++;
            printContextAt(twIndex, m);
        }
    }
    cout << "Found " << matchesFound << " in total." << endl;
    return true;
}

void cmdContent(){
    if (wordsInTextData <= 0){
        cout << "Please enter a text first" << endl;
        return;
    }

    for (int x = 0; x < wordsInTextData; x++){
        cout << textData[x] << " ";
    }
    cout << endl;
}

bool interpretCommand(char input [MAX_CMD_SIZE])
{
    CMD cmd = getCommandType(input);
    bool result= false;
    switch (cmd)
    {
        case Enter: result = cmdEnter(input); break; //                                                     
        case Content: cmdContent(); result = true; break;
        case Count: result = cmdCount(input); break; //                                                     
        case Where: result = cmdWhere(input); break; //                                                     
        case Context: result = cmdContext(input); break; //                                                     
        case Stop: KeepRunningProgram = false; result = true; break;
        case ERROR: cout << "CMD ERROR" <<endl; result = false; break;
    }
    return result;
}

int main() {
    clearCharArray(textData);

    char cmd [MAX_CMD_SIZE];
    while (KeepRunningProgram){
        cout<< "Enter a command: " << endl;
        cin.getline(cmd,MAX_CMD_SIZE);
        bool succes = interpretCommand(cmd);
        if (succes){
            cout << "Operation completed without errors." << endl;
        } else {
            cout << "There was an error during execution." << endl;
        }
    }

    return 0;
}

