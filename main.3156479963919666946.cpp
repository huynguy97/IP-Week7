#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

const int MAX_WORDS=30000;

//                                                                                          
//                                                                                          

bool open_text_file(ifstream& infile, char filename[80]){
    infile.open(filename);
    return infile.is_open();
}

int count_words(ifstream& file,int& w,string text[MAX_WORDS])
{
    w=0;
    while(file){
        file>>text[w];
        w++;}
    w--;
    return w;
}

void content(string text[MAX_WORDS], int w)
{
    for(int i=0;i<w;i++){
        cout<<text[i]<<" ";}
}

int main(){
    ifstream file;
    string command;
    char filename[80];
    char chr[2000];
    string instance[50];
    string text[MAX_WORDS];
    int w=0;
    int c=0;
    while(command!="stop"){
            cout << "Please enter command: " << "\n";
            cin >> command;
        if(command== "enter"){
            cin.ignore(1);
            cin.getline(filename, 80, '\n');
            if (open_text_file (file, filename)){
                cout << "file opened"<<endl;
                cout<<"This text contains "<<count_words(file,w,text)<<" words"<<endl;
                file.close();}
            else{
            cout << "File could not be opened"<<endl;}
        }
        else if(command=="content"){
            content(text,w);
            cout<<endl;}
        else if(command=="count"){
            cin.ignore(1);
            cin.getline(chr, 120, '\n');
            int i=0;
            int j=0;
            int f=0;
            bool found;
            while(chr[i]!='\0'){
                string str;
                while(chr[i]!=' '&&chr[i]!='\0'){
                    str=str+chr[i];
                    i++;}
                instance[j]={str};
                j++;
                i++;
            }
        for(int k=0;k<w;k++){
            if(j==1){
                if(instance[0]==text[k]){
                    f++;}
            }
            else{
                if(instance[0]==text[k]){
                    for(int l=j;l>=0;l--){
                        int m=1;
                        if(instance[m]==text[k+m]){
                            found=true;}
                        else{
                            found=false;}
                        m++;
                    }
                    if(found){
                        f++;}
                }
            }
        }
        cout<<f << "\n";
        int x = sizeof(instance)/sizeof(instance[0]);
        cout << x;
        float percentage = 00.00;
        percentage = x/w * 100;
        cout << "Percentage of total words: " << percentage << "\n";
        }
        else if(command=="where"){
            cin.ignore(1);
            cin.getline(chr, 120, '\n');
            int i=0;
            int j=0;
            int f=0;
            bool found;
            while(chr[i]!='\0'){
                string str;
                while(chr[i]!=' '&&chr[i]!='\0'){
                    str=str+chr[i];
                    i++;}
                instance[j]={str};
                j++;
                i++;
            }
        for(int k=0;k<w;k++){
            if(j==1){
                if(instance[0]==text[k]){
                    cout<<k+1<<' ';}
            }
            else{
                if(instance[0]==text[k]){
                    for(int l=j;l>=0;l--){
                        int m=1;
                        if(instance[m]==text[k+m]){
                            found=true;}
                        else{
                            found=false;}
                        m++;
                    }
                    if(found){
                        cout<<k+1<<' ';}
                }
            }
        }

        }
    else if(command=="context"){
            int a=0;
            cin.ignore(1);
            cin>>a;
            cin.ignore(1);
            cin.getline(chr, 120, '\n');
            int i=0;
            int j=0;
            int f=0;
            bool found;
            while(chr[i]!='\0'){
                string str;
                while(chr[i]!=' '&&chr[i]!='\0'){
                    str=str+chr[i];
                    i++;}
                instance[j]={str};
                j++;
                i++;
            }
        for(int k=0;k<w;k++){
            if(j==1){
                if(instance[0]==text[k]){
                    for(int x=a;a>0;x--){
                            cout<<text[k-x]<<' ';}
                    for(int y=0;y>a;y++){
                            cout<<text[k+y]<<' ';}
                }
            }
            else{
                if(instance[0]==text[k]){
                    for(int l=j;l>=0;l--){
                        int m=1;
                        if(instance[m]==text[k+m]){
                            found=true;}
                        else{
                            found=false;}
                        m++;
                    }
                    if(found){
                        for(int x=a;a>0;x--){
                            cout<<text[k-x]<<' ';}
                        for(int y=0;y>a;y++){
                            cout<<text[k+y]<<' ';}
                    }
                }
            }
        }
    }
    }
    cout<<"Program terminated";
return 0;
}

