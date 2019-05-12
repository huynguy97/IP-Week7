#include <iostream>
#include <fstream>
using namespace std;
char letters[52]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

const int WORD_CAPACITY=10000;
const int MAX_TARGETS=30;
/*                                                                                                                                                    
                                
 
                  
                                                         
                      
                              
                          
                         
     
                                                                    
                     
     
                
 

                                                                
 
                                                                                                                                                  
                           
                 
                                                 
                                                      
                                                                     
                     
 

*/

void content(string wordlist[WORD_CAPACITY],int true_size)
{
    cout<<"the listed words, in order of appearance (capitalized words being counted as different words) are:\n";
    for (int element=0;element<true_size;element++)
    {
        cout<<wordlist[element]<<"\n";
    }
}
string remove_end_interpunction(string word)
{
    int length=word.length();
    bool interpunction=true;
    string wordbin;
    while (interpunction) //                                                           
    {
        for (int count=0;count<52;count++) //                    
            {
                if (word[length-1]==letters[count])
                    interpunction=false;
            }
            if (interpunction)
            {
                for (int index=0; index<length-1; index++)
                {
                    wordbin+=word[index];
                }
                word=wordbin;
                wordbin="";
                length--;
            }
    }
    return word; //                                                                                                                                              
}
int add_words_to_list(ifstream& infile, string wordlist[WORD_CAPACITY])
{
    string word;
    int added_words=0;
    bool addition;
    while(infile>>word)
    {
        word=remove_end_interpunction(word);
        addition=true;
        int checked_words=0;
        while ( checked_words<added_words && addition)
        {

           if (word==wordlist[checked_words])
           {
               addition=false;
           }
           checked_words++;
        }
        if (addition)
        {
            wordlist[added_words]=word;
            added_words++;
        }
    }
    return added_words; //                                                                                                                                                      
}
void start_console(ifstream& infile, string wordlist[WORD_CAPACITY])
{
    string holder[WORD_CAPACITY]=wordlist[WORD_CAPACITY];//                                                
    bool ongoing=true;
    while(ongoing)
    {
        cout<<"Do you want to a) enter a file, type :Enter \"filename\"\n b) show the content of the previously entered file, type:Content\n c)stop operations type:Stop\n d)count the occurrences of a word sequence type:Count\n e)find where a word sequence occurs type:Where \n or f)the context in which a word sequence occurs type(not build in due to lack of time):Context\n ";
        string input; //                                                                                                       
        cin>>input;
        int wordcount=0;
        if (input=="A" || input=="a" || input=="Enter" || input=="enter")
        {
            wordlist=holder;
            char filename[50];
            cin.get(); //                                                                                                                          
            cin.getline(filename, 50);
            infile.open(filename);
            if(!infile.is_open())
            {
                cout<<"Opening of file failed, please try again.\n";
            }
            else
            {
                wordcount=add_words_to_list(infile, wordlist);
                cout<<"The size of the created list is:"<<wordcount<<" words.\n";
                infile.close();
                infile.open(filename);//             
            }
        }
        if (input=="b" || input=="Content" || input=="content" || input=="B") //                                                                                     
        {
            if(wordcount==0)
                cout<<"No list has been created as of yet, please do so first.\n";
            else
                content(wordlist,wordcount);
        }
        if (input=="c" || input=="C" || input=="Stop" || input=="stop")
            ongoing=false;
        if (input=="d" || input=="D" || input=="count" || input=="Count")
        {
            if(!infile.is_open())
                cout<<"Please first assign a file and make a list of it using option a)\n";
            else
            {
                string target[MAX_TARGETS];
                string target_word;
                int targets_found=0;
                char endcheck;
                bool ending=false;
                cin.get();//                      
                getline(cin,target_word);
                int length= target_word.length();
                int passed=0;
                while (passed<length)
                {
                    if(target_word[passed]==' ')
                        targets_found++;
                    else
                        target[targets_found]+=target_word[passed];
                    passed++;
                }
                targets_found++;
                string word;
                int total_words=0;
                int occurrences=0;
                int slot=0;
                bool matching=false;
                while (infile>>word)
                {
                    if (matching=false)
                        slot=0;
                    word=remove_end_interpunction(word);
                    total_words++;
                    if (word==target[slot])
                    {
                        if (slot!=0)
                        {
                            if(word==target[0])
                                cout<<"Overlapping potential found, sadly this was too difficult to deal with before the deadline"<<total_words<<"might hold the combination but this isn't certain";
                        }
                        slot++;
                        matching=true;
                        if (slot==targets_found)
                        {
                            occurrences++;
                            slot=0;
                            matching=false;
                        }

                    }
                    else
                        matching=false;

                }
                if (occurrences==0)
                    cout<<"This combination never appears and thus holds 0% of the total text,\n";
                cout<<"The amount of occurrences found is:"<<occurrences<<". This on a total of:"<<total_words<<" words"<<". Giving a percentage of;"<<100*((float)occurrences/(float)total_words)<<"% and occupying"<<targets_found*100*((float)occurrences/(float)total_words)<<"%.\n";
            }
            infile.close();
        }
        if (input=="e" || input=="E" || input=="where" || input=="Where") //                                                                      
        {
            if(!infile.is_open())
                cout<<"Please first assign a file and make a list of it using option a)\n";
            else
            {
                string target[MAX_TARGETS];
                string target_word;
                int targets_found=0;
                char endcheck;
                bool ending=false;
                cin.get();//                      
                getline(cin,target_word);
                int length= target_word.length();
                int passed=0;
                while (passed<length)
                {
                    if(target_word[passed]==' ')
                        targets_found++;
                    else
                        target[targets_found]+=target_word[passed];
                    passed++;
                }
                targets_found++;
                string word="";
                int total_words=0;
                int occurrences=0;
                int slot=0;
                bool matching=false;
                while (infile>>word)
                {
                    if (matching=false)
                        slot=0;
                    word=remove_end_interpunction(word);
                    total_words++;
                    if (word==target[slot])
                    {
                        if (slot!=0)
                        {
                            if(word==target[0])
                                cout<<"Overlapping potential found, sadly this was too difficult to deal with before the deadline"<<total_words<<"might hold the combination but this isn't certain";
                        }
                        slot++;
                        matching=true;
                        if (slot==targets_found)
                        {
                            occurrences++;
                            if (occurrences==1)
                                cout<<"The indices where this combination occurs are:";
                            cout<<total_words-slot<<"to"<<total_words<<".\n";
                            slot=0;
                            matching=false;
                        }

                    }
                    else
                        matching=false;

                }
                if (occurrences==0)
                    cout<<"This combination never appears\n";
                cout<<"The amount of occurrences found is:"<<occurrences<<".\n";
            }
            infile.close();
        }
        /*
                                                                                                                                                                                                                                    
         
                                                       
                                                 
                                 
                                                                                           
                
             
                                           
                                   
                                    
                              
                                  
                                                  
                                         
                                                 
                             
                                     
                 
                                                
                                        
                        
                                                                   
                             
                 
                                
                               
                                  
                                  
                           
                                    
                                    
                 
                                       
                               
                                                        
                                            
                                  
                                           
                     
                                    
                         
                                               
                                                                                                                                                                                                     
                         
                               
                                      
                                                
                         
                                          
                                                               
                                   
                                           
                         

                     
                        
                                       

                 
                                   
                                                             
                    
                 
                                                                                         
                     
                                                                       
                     

                                                                                         
                 
             
                           

         */
    }
    cout<<"\n...Operations successfully stopped!...";
    infile.close();
}

int main()
{
    string wordlist[WORD_CAPACITY]; //                                          
    ifstream infile;
    start_console(infile, wordlist);
//                                               
//                                
    return 0;
}

