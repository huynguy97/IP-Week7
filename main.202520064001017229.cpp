//                           
//                         
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

void Enter (ifstream& infile, string filename, string Words[500], int& i)
{
    //              
    assert(true);
    //               
    //                                                                                           
    i=0;
    string word;

    infile.open(filename) ;
    if(infile)
    {
        while(infile >> word)
        {
            Words[i] = word;
            i++;
        }
        cout<<"The file has "<< i <<" words."<<endl;
    }
    else
    {
        cout<<"Operation failed."<<endl;
    }
}

//              

void command(string com,int& i,string Words[500])
{
    //              
    assert(true);
    //               
    /*
                         
    */

    ifstream infile;
    string filename;
    if (com =="enter")
    {

        getline(cin.ignore(1),filename);

        cout << filename << endl;
        Enter(infile,filename, Words,i);
        /*                                
         
                                                                                 
         
            
         
                                            
         */

    }
    else if(com =="content")
    {
        for(int j=0; j<i;j++)
        {
            cout << Words[j] << " ";
        }
    }

    /*
                         
     

                                                                                   
                                                                                              

                                                 
                                                      
                                    
                      
                                      
                   
                                       
                       
                
                     

               
                 
                         

                                                 
                                                      
                                    
                                              

                      
                                      
                   

                                       

                                             
                                                              
                       
                
                     

               
                          
                       
                 

                           

                                                 
                                                      
                                    
                                              

                      
                                      
                   

                                       

                                             
                                                              
                       
                
                     

               
                        
                                           
                                                           
      */

    }

int main()
{
    int i;
    string Words[500];
    ifstream infile;
    string com;
    while(com!="stop")
    {
        cout << "Enter command" << endl;
        cin >> com;
        command(com,i,Words);
    }

    return 0;
}

