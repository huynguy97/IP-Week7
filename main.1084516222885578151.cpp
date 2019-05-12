#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

/*                             */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*                                              */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /*                                   */
    MSG messages;            /*                                            */
    WNDCLASSEX wincl;        /*                                    */

    /*                      */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /*                                    */
    wincl.style = CS_DBLCLKS;                 /*                     */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /*                                    */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /*         */
    wincl.cbClsExtra = 0;                      /*                                       */
    wincl.cbWndExtra = 0;                      /*                                  */
    /*                                                              */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /*                                                             */
    if (!RegisterClassEx (&wincl))
        return 0;

    /*                                                  */
    hwnd = CreateWindowEx (
               0,                   /*                                     */
               szClassName,         /*           */
               _T("Code::Blocks Template Windows App"),       /*            */
               WS_OVERLAPPEDWINDOW, /*                */
               CW_USEDEFAULT,       /*                              */
               CW_USEDEFAULT,       /*                                        */
               544,                 /*                    */
               375,                 /*                      */
               HWND_DESKTOP,        /*                                         */
               NULL,                /*         */
               hThisInstance,       /*                          */
               NULL                 /*                         */
           );

    /*                                       */
    ShowWindow (hwnd, nCmdShow);

    /*                                                                */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /*                                                        */
        TranslateMessage(&messages);
        /*                                 */
        DispatchMessage(&messages);
    }

    /*                                                                       */
    return messages.wParam;
}

/*                                                                     */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /*                     */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /*                                     */
        break;
    default:                      /*                                      */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <cassert>
using namespace std ;

const int MAX_CHARS = 60 ;
const int MAX_WORDS = 3000 ;
const int MAX_FILENAME_LENGTH = 80 ;

bool open_text_file (ifstream& infile)
{

    assert (!infile.is_open()) ;
    cout << "Input filename" << '\n' ;
    char filename [MAX_FILENAME_LENGTH] ;
    cin.getline(filename, MAX_FILENAME_LENGTH, '\n') ;

    infile.open(filename) ;
    return infile.is_open() ;
}

bool read_word (ifstream& infile, char word [MAX_CHARS])
{
    assert(infile.is_open()) ;

    infile >> word ;
    return infile ;
}

int sequential_search (char words [MAX_WORDS][MAX_CHARS], int pos, int& no, char search_value [MAX_CHARS])
{
    assert (0 <= pos && 0 <= no) ;
    if (pos > no)
    {
        return no + 1 ;
    }
    while ((pos <= no ) && (words [pos] != search_value))
    {
        pos++ ;
    }
    return pos ;
}

bool tally_word (char word [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int& no )
{
    assert (no >= 0 && no < MAX_WORDS) ;
    int pos = sequential_search(words, 0, no, word) ;
    cout << pos << '\t'  << no << '\n';
    if (pos < no)
    {
        cout << "freqs test" << '\n';
        freqs [pos]++ ;
        return true ;
    }
    else if (pos < MAX_WORDS)
    {
        strcpy(words [pos], word) ;
        freqs [pos] = 1 ;
        no++ ;
        return true ;
    }
    cout << "false tally" << '\n';
    return false ;
}

int count_words (ifstream& infile, char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS])
{
    assert (infile.is_open()) ;
    int no = 0 ;
    char next [MAX_CHARS] ;
    while (read_word(infile, next) && tally_word(next, words, freqs, no ) && no < MAX_WORDS ) ;
    {
        return no ;
    }

}

void display_frequencies (char words [MAX_WORDS][MAX_CHARS], int freqs [MAX_WORDS], int no)
{
    assert (no >= 0 && no < MAX_WORDS) ;
    for ( int i = 0; i < no ; i++ )
    {
        cout << words [i] << '\t' << freqs [i] << '\n' ;
    }

}

void count(ifstream& infile, char search_value [MAX_CHARS], char words [MAX_WORDS][MAX_CHARS], int& no, int pos)
{

    cout << "Enter search value" << endl;
    cin.getline(search_value, MAX_CHARS, '\n');

    cout << search_value;
    cout << sequential_search(words, pos, no, search_value) ;

}

int main()
{
    ifstream input_file ;
    if (open_text_file(input_file))
    {
        char c;
        char words [MAX_WORDS][MAX_CHARS] ;
        int p;
        int n;
        char search_value [MAX_CHARS];
        string s;
        cout << "input command ";
        cin >> s;
        if (s=="count")
        {
            count(input_file, search_value, words, n, p);
        }
        input_file.close() ;
        while (true);
        cin.get(c);
        return 0;
    }

    else
    {
        return 1;
    }

}

