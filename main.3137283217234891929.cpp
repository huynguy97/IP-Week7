//                        
//                         
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <string>
using namespace std;

enum Command{Enter,Content,Stop,Count,Where,Context,Invalid};

const int MAX_WORDS_NUM=50000;
const int MAX_SEQUENCE_LENGTH=25;
const int MAX_INDICES_AMOUNT=2500;
string file_content[MAX_WORDS_NUM];
Command parse_command(string order){
    //              
    assert(true);
    //                                                    
    //                                                     
    //                                                                        
    /*              
                                    
                                      
                                   
                                    
                                    
                                      
                                 */

    //                                  
    cin.ignore(1);
    if(order=="enter")   return Enter;
    if(order=="content") return Content;
    if(order=="stop")    return Stop;
    if(order=="count")   return Count;
    if(order=="where")   return Where;
    if(order=="context") return Context;
    return Invalid;
}

int readin_file(ifstream& infile){
    //                                                                           
    //                                              
    //                         
    //                                                                      
    //                                                                              
    if(!infile.is_open()){
        return -1;
    }
    int i=0;
    while(infile&&i<MAX_WORDS_NUM){
        infile>>file_content[i];
        i++;
    }
    return i;
}

void enter_filename (int& wordcount){
    //                
    assert(true);
    //                                                                       
    //                                                                                 
    string fname;
    getline(cin, fname);
    ifstream infile(fname.c_str());
    int result=readin_file(infile);
    if(result==-1){
        cout << "Invalid/wrong filename given! Please try again." <<endl;
        return;
    }
    infile.close();
    wordcount=result-1;
    cout<<"Sucessfully read "<<result-1<<" words from the file."<<endl;
    if(result==MAX_WORDS_NUM){
        cout<<"Warning: Maximum Word count read. Further contents may be missing.";
    }
}

void give_content(int wordcount){
    //                
    assert(true);
    //                                                                    
    for(int i=0;i<wordcount;i++){
        cout<<file_content[i]<<endl;
    }
}

bool check_hit(string sequence[], int seqlen, int pos, int wordcount){
    //                
    assert(true);
    //                                                                                              
    for(int i=0;i<seqlen;i++){
        if(pos+i>=wordcount||sequence[i]!=file_content[pos+i]){
            return false;
        }
    }
    return true;
}

int read_arguments(string sequence[]){
    //                
    assert(true);
    //                                                                                    
    //                                                                            
    string concatseq;
    int i=0;
    getline(cin, concatseq);
    concatseq+=' ';
    string cur="";
    for(int j=0;j<(int)concatseq.length();j++){
        if(concatseq.at(j)==' '&&i<MAX_SEQUENCE_LENGTH){
            sequence[i]=cur;
            cur="";
            i++;
        }
        else{
            cur+=concatseq.at(j);
        }
    }
    if(i>MAX_SEQUENCE_LENGTH){
        cout<<"The sequence was to search for was to long, only the first ";
        cout<<MAX_SEQUENCE_LENGTH<<" words were taken."<<endl;
    }
    return i;
}

int calc_indices(int wordcount, int indices[MAX_INDICES_AMOUNT], string sequence[],int seqlen){
    //                
    assert(true);
    //                                                                            
    //                               
    int i=0;
    for(int j=0;j<=wordcount-i;j++){
        if(check_hit(sequence,seqlen,j,wordcount)){
                indices[i]=j;
                i++;
        }
    }
    return i;
}

void count_sequence(int wordcount){
    //                
    assert(true);
    //                                                                        
    //                                                                         
    string sequence[MAX_SEQUENCE_LENGTH];
    int seqlen=read_arguments(sequence);
    int indices[MAX_INDICES_AMOUNT];
    int matches=calc_indices(wordcount,indices,sequence,seqlen);
    cout<<"Matches found: "<<matches;
    cout<<" , total words: "<<wordcount;
    cout<<" ("<<(100.0*matches)/wordcount<<"%)."<<endl;

}

void show_indices(int wordcount){
    //                
    assert(true);
    //                                                                         
    //                                                        
    string sequence[MAX_SEQUENCE_LENGTH];
    int indices[MAX_INDICES_AMOUNT];
    int seqlen=read_arguments(sequence);
    int occurences=calc_indices(wordcount,indices,sequence,seqlen);
    if(occurences==0){
        cout<<"0 occurences found."<<endl;
        return;
    }
    if(occurences==1){
        cout<<"The sequence was found at index "<<indices[0]+1<<"(1 match)."<<endl;
        return;
    }
    //           
    cout<<"The sequence was found at indices "<<indices[0]+1;
    //                  
    for(int i=1;i<occurences-1;i++){
        cout<<", "<<indices[i]+1;
    }
    //          
    cout<<" and "<<indices[occurences-1]+1<<"(total "<<occurences<<" matches)."<<endl;
}

void show_context(int wordcount){
    //                
    assert(true);
    //                                                                       
    //                                                   
    int surround;
    cin>>surround;
    //                       
    cin.ignore(1);
    string sequence[MAX_SEQUENCE_LENGTH];
    int indices[MAX_INDICES_AMOUNT];
    int seqlen=read_arguments(sequence);
    int occurences=calc_indices(wordcount,indices,sequence,seqlen);
    for(int i=0;i<occurences;i++){
        for(int j=max(0,indices[i]-surround);j<min(indices[i]+surround+seqlen,wordcount);j++){
            cout<<file_content[j]<<" ";
        }
        cout<<endl;
    }
    cout<<occurences<<((occurences==1)?" occurence found":" occurences found.")<<endl;
}

void exec_command (Command order,int& wordcount){
    //                
    assert(true);
    //                                                                     
    switch(order){
        case Enter: enter_filename(wordcount);break;
        case Content:give_content(wordcount);break;
        case Count:count_sequence(wordcount);break;
        case Where:show_indices(wordcount);break;
        case Context:show_context(wordcount);break;
        default:break;
    }
}

int main()
{
    Command order;
    int wordcount;
    while(order!=Stop){
        cout<<"Give a command >> ";
        string choice;
        cin>>choice;
        order=parse_command(choice);
        exec_command(order,wordcount);
    }
    //                                                                                        
}

