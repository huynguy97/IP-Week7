//                                                       
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;

const int MAX_WORDS = 50000;
const int MAX_WORDS_IN_QUERY = 100;

int readfile(string words[]){
	//            
	assert(true);
	//             
	//                                              
	//                                                          
	//                                                     
	char trash;
	cin.get(trash); //                                     
	string filename;
	getline(cin, filename);
	ifstream text(filename);
	if (text.is_open()){
		int numWords = 0;
		while (text and not text.eof()){
			text >> words[numWords];
			numWords++;
		}
		cout << numWords << " words have been read from file \"" << filename << "\"\n";
		return numWords;
	}
	else{
		cout << "couldn't open file \"" << filename << "\"\n";
		return -1;
	}
}

void showwords(string words[], int numWords){
	//            
	assert(numWords >= 0);
	assert(numWords < MAX_WORDS);
	//             
	//                                                          
	for (int i = 0;i<numWords;i++){
		cout << words[i] << endl;
	}
	return;
}

void readWordsUntilLineEnd(string queryWords [], int& numQueryWords){
	//              
	assert(true);
	//               
	//                                                                                            
	numQueryWords = 0;
	char c;
	bool keepReading = true;
	while(keepReading&&cin.get(c)){
		if(c=='\n'){
			numQueryWords++;
			keepReading = false;
		} else {
			if(c==' '){
				if(queryWords[numQueryWords].length()>0){
					numQueryWords++;
				}	
			} else {
				queryWords[numQueryWords] += c;
			}
		}
	}
}

int count(string words[], int numWords,string queryWords[], int numQueryWords){
	//             
	assert(numQueryWords > 0);
	assert(numQueryWords <= MAX_WORDS);
	assert(numWords >= 0);
	assert(numWords <= MAX_WORDS);
	//              
	//                                                         
	int numMatch = 0;
	for (int i = 0;i<numWords-numQueryWords;i++){
		bool match = true;
		for (int j = 0;j<numQueryWords;j++){
			if (words[i+j] != queryWords[j]){
				match = false;
			}
		}
		if (match){
			numMatch++;
		}
	}
	cout << "found " << numMatch << " matches for query";
	for (int i = 0;i<numQueryWords;i++){
		cout << " " << queryWords[i];
	}
	cout << endl;
	cout << "total words is: " << numWords << endl;
	cout << "query is " << (100.0*static_cast<float>(numMatch)/static_cast<float>(numWords)) << "% of total words" << endl;
	return numMatch;
}

void where(string words [], int numWords, string queryWords[], int numQueryWords){
	//              
	assert(numQueryWords > 0);
	assert(numQueryWords <= MAX_WORDS);
	assert(numWords >= 0);
	assert(numWords <= MAX_WORDS);
	//                
	//                                                                                                           
	cout << "occurences found on indices:\n";
	int numMatch = 0;
	for(int i=0; i+numQueryWords<=numWords; i++){
		bool match = true;
		for(int j=i; j<i+numQueryWords; j++){
			if(words[j]!=queryWords[j-i]){
				match = false;
			}
		}
		if(match){
			cout << i+1 << " ";
			numMatch++;
		}
	}
	cout << endl;
	cout << "total number of occurences:" << numMatch << endl;
}

void context(string words [], int numWords,string queryWords[], int numQueryWords, int contextLength){
	//              
	assert(numQueryWords > 0);
	assert(numQueryWords <= MAX_WORDS);
	assert(numWords >= 0);
	assert(numWords <= MAX_WORDS);
	assert(contextLength >= 0);
	//                                                                                                                          
	int numMatch = 0;
	for(int i=0; i+numQueryWords<=numWords; i++){
		bool match = true;
		for(int j=i; j<i+numQueryWords; j++){
			if(words[j]!=queryWords[j-i]){
				match = false;
			}
		}
		if(match){
			for(int j=i-contextLength; j<i; j++){
				if(j>=0){
					cout << words[j] << " ";
				}
			}
			cout << words[i];
			for(int j=i+1; j<=i+contextLength; j++){
				cout << " " << words[j];
			}
			cout << endl;
			numMatch++;
		}
	}
	cout << "total number of occurences: " << numMatch << endl;
}

int main(){
	string words[MAX_WORDS];
	int numWords = 0;
	string command;
	while(command != "stop"){
		cin >> command;
		if (command == "enter"){
			numWords = readfile(words);
		}
		if (command == "content"){
			showwords(words,numWords);
		}
		if (command == "count"){
			string queryWords[MAX_WORDS_IN_QUERY];
			int numQueryWords;
			readWordsUntilLineEnd(queryWords,numQueryWords);
			count(words,numWords,queryWords,numQueryWords);
		}
		if (command == "where"){
			string queryWords[MAX_WORDS_IN_QUERY];
			int numQueryWords;
			readWordsUntilLineEnd(queryWords, numQueryWords);
			where(words, numWords,queryWords,numQueryWords);
		}
		if (command == "context"){
			int contextLength;
			cin>>contextLength;
			string queryWords[MAX_WORDS_IN_QUERY];
			int numQueryWords;
			readWordsUntilLineEnd(queryWords, numQueryWords);
			context(words, numWords,queryWords,numQueryWords,contextLength);
		}
	}
	return 0;
}

