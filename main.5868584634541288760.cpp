//                                                                       
//                                                                                   
//                                                                                        
//                                                                                       
//          

//                                     
//                                      

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

const int MAX_CHARS = 60 ;
const int MAX_WORDS = 30000 ;

enum Command {Enter, Content, Stop, Count, Where, Context};

bool open_text_file (ifstream& infile)
{
    //              
    assert(!infile.is_open());
    /*               
                                                      
    */
    char filename[80];

    cin.getline ( filename, 80, '\n');
    infile.open ( filename ) ;
    return infile.is_open () ;
}

bool read_word (ifstream& infile, char word [MAX_CHARS] )
{
    //             
    assert(infile.is_open());
    /*               
                                                
    */
    infile >> word ;
    return infile ;
}

int sequential_search ( char words[][MAX_CHARS], int from, int to, char search_value[MAX_CHARS] )
{
    //               
    assert ( 0 <= from && 0 <= to ) ;
    //                 
    //                                                           

    int  position = from ;
    while (position < to && strcmp(words[position], search_value)!=0)
        position++ ;
    return position ;
}

bool tally_word (char word [MAX_CHARS],  char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int& no )
{
    //              
    assert(no>=0&&no<MAX_WORDS);
    /*               
                                                                                             
                                                                              
    */

    int pos = sequential_search ( words, 0, no, word ) ;

    if ( pos < no )
        {
            freqs [pos]++ ;
            return true ;
        }
    else if ( pos < MAX_WORDS )
        {
            strcpy ( words [pos], word ) ;
            freqs [pos] = 1 ;
            no++ ;
            return true ;
        }
    return false ;
}

int count_words (ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int  freqs [MAX_WORDS] )
{
    //              
    assert(infile.is_open());
    /*
                                                                           
    */
    int no = 0 ;
    char next [MAX_CHARS];
    while ( read_word (infile, next) && tally_word (next, words, freqs, no) && no < MAX_WORDS );
    return no ;
}

void user_interaction(Command &cmd)
{
    //             
    assert(cmd!=Stop);
    /*               
                                                                  
    */
   char c[100];
   char space;

   cin>>c;

   if(strcmp(c,"enter")==0)
   {
       cin.get(space);
       cmd=Enter;
   }
   if(strcmp(c,"content")==0)
        cmd=Content;
    if(strcmp(c,"stop")==0)
        cmd=Stop;
}

/*      
                                                                                                                                                   
                                                                                                                                                                                    
                                                                                                                                            
                                                                                                                                                                     
                                                                         
                                                                                                                                                                       
                      
*/
int main()
{

    ifstream file ;

    Command cmd=Enter;

    int nr;

    char words [MAX_WORDS][MAX_CHARS];
    int  freqs [MAX_WORDS] ;

    //                                                                             
    while(cmd!=Stop)
    {
        user_interaction(cmd);

        if(cmd == Enter)
        {
            if (open_text_file (file))
                {
                    nr = count_words ( file, words, freqs) ;
                    cout<<nr;
                }
            else
                cout<<"The operation has failed: The file could not be opened."<<endl;
        }
        if(cmd == Content)
        {
            for(int i=0;i<nr;i++)
                cout<<words[i]<<endl;
        }
    }
    return 0;
}

