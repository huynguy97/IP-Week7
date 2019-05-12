#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

//                        

using namespace std;

const int MAX_CHARS = 60;
const int MAX_WORDS = 30000;

/*                                           
                                             
                                             
                                             
                                             
                                                
                                             
                                             
                                             
                                             
                                             
                                             
                                            */

bool enter_and_open_file (ifstream& infile)
{
    //                
    assert( !infile.is_open() );
    /*               
                                                            
    */

    char filename[80];
    cin.ignore();
    cin.getline (filename, 80, '\n');
    infile.open(filename);

    if(infile.is_open()){
        return true;
    }
    else{
        return false;
    }

}

int sequential_search ( string data [], int from, int to, string search_value )
{
    //               
    assert ( 0 <= from && 0 <= to ) ;
    /*               
                                     
                                                                                       
                                                                                              
    */

    if ( from > to ){
        return to + 1 ;
    }
    int position = from ;
    while (position <= to && data [ position ] != search_value){
        position++ ;
    }

    return position ;
}

bool read_and_store_word (ifstream& infile, string words[MAX_CHARS], char word [MAX_CHARS], int no){

    //                
    assert( infile.is_open() );
    /*               
                                      
    */

    infile >> words[no];
    //                 
    return infile;

}

int count_words (ifstream& infile, string words[MAX_WORDS]){

    //                
    assert( infile.is_open() );
    /*               
                                                                  
    */

    int no = 0;
    char next [MAX_WORDS];

    while(read_and_store_word(infile, words, next, no) && no < MAX_WORDS){
        no++;
    }

    return no;

}

int get_arguments(string arguments[100]){

    //                
    assert( true );
    /*               
                                                                                       
    */
    int no_of_arguments;
    for(int i = 0; i < 100; i++){
        cin >> arguments[i];
        if(cin.get() == '\n'){
            no_of_arguments = i+1;
            for(i= i+1; i < 100; i++){
                arguments[i] = "";
            }
        }
    }
    return no_of_arguments;

}

int count_word_sequence(string words[MAX_WORDS], string arguments[100]){

    //                
    assert( true );
    /*               
                                                   
    */
    int no_of_arguments = get_arguments(arguments);
    int counter = 0;
    int word1 = 0;

        for(int i = 0; i < MAX_WORDS; i++){

            word1 = sequential_search(words, word1, MAX_WORDS, arguments[0]);
            if(word1 >= MAX_WORDS){
                return counter;
            }
            for(int j = 1; j <= no_of_arguments; j++){

                if(no_of_arguments == 1){
                    words[word1] == arguments[j] && j == no_of_arguments - 1;
                    counter++;
                }
                else{
                    if(words[word1 + j] == arguments[j] && j == no_of_arguments - 1){
                        counter++;
                    }
                    else{
                        j = no_of_arguments + 1;
                    }
                }
            }
            word1++;
    }
}

int word_where(string words[MAX_WORDS], string arguments[100]){

    //                
    assert( true );
    /*               
                                       
    */
    int no_of_arguments = get_arguments(arguments);
    int counter = 0;
    int word1 = 0;

        for(int i = 0; i < MAX_WORDS; i++){
            word1 = sequential_search(words, word1, MAX_WORDS, arguments[0]);
            if(word1 >= MAX_WORDS){
                return counter;
            }

            for(int j = 1; j <= no_of_arguments; j++){
                if(no_of_arguments == 1){
                    words[word1] == arguments[j] && j == no_of_arguments - 1;
                    counter++;
                    cout << "Index: " << counter << endl;
                }
                else{
                    if(words[word1 + j] == arguments[j] && j == no_of_arguments - 1){
                        counter++;
                        cout << "Index: " << counter << endl;
                    }
                    else{
                        j = no_of_arguments + 1;
                    }
                }
            }
            word1++;
            cout << "Index: " << counter << endl;
    }
}

int main()
{
    ifstream file;
    string words[MAX_WORDS];
    string command;
    string arguments[100];

    cout << "Enter one of these commands: enter filename, content, stop, count, where, context" << endl;
    cin >> command;

    while(true){
        if(command == "enter"){

            if(file.is_open()){
                file.close();
            }
            enter_and_open_file(file);
            int no = count_words(file, words);
            cout << no << " words are read" << endl;

        }

        else if(command == "content"){

            int no = count_words(file, words);
            for(int i = 0; i < no; i++){
                cout << words[i] << endl;
            }

        }

        else if(command == "stop"){
            file.close();
            return 0;
        }

        else if(command == "count"){
            int no_of_occurrences = count_word_sequence(words, arguments);
            int total = count_words(file, words);
            double percentage = ((no_of_occurrences * 1.0) / (total * 1.0)) * 100.00;
            cout << "The program found " << no_of_occurrences << " occurrences of this word sequence" << endl;
            cout << "The total number of words in this text is: " << total << endl;
            cout << "The percentage of the word sequence with respect to the total number of words is: " << percentage << endl;
        }

        else if(command == "where"){
            //                                    
            //                                                            
            cout << "This command does not work unfortunately" << endl;
        }

        else if(command == "context"){
            cout << "This command does not work unfortunately" << endl;
        }

        file.clear();
        file.seekg(0, ios::beg);
        cout << "\nEnter one of these commands: enter filename, content, stop, count, where, context" << endl;
        cin >> command;
    }
}

