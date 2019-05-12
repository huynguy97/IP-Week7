#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX_LENGTH = 100;
const int MAX_LENGTH_WORD = 100;
const int MAX_WORDS = 3000;
typedef char Word [MAX_LENGTH_WORD];
typedef Word Words [MAX_WORDS];

/*                        */

void ask_filename (char filename[MAX_LENGTH])
{
    cout << "welke file wil je openen?" << endl;
    cin.getline (filename, MAX_LENGTH, '\n');
}

int read_file (ifstream& inputfile, Words words)
{
    assert (inputfile.is_open());

    int i = 0;

    while (inputfile)
    {
        inputfile >> words [i];
        i++;
    }

    cout << "Het zijn " << i << " woorden" << endl;
    return i;
}

void content (Words words, int aantal_woorden)
{
    for (int i = 0; i < aantal_woorden; i++)
    {
        cout << words[i] << endl;
    }
}

bool woorden_vergelijken (Word a, Word b)
{
    for (int i = 0; i < MAX_LENGTH_WORD; i++){
        if (a[i] != b[i]){
            return false;
        }
        if (a[i] == '\0'){
            return true;
        }
    }

    return true;
}

int count_words (int aantal_woorden, Words sequence, Words words, int sequence_aantal, int index[MAX_WORDS])
{
    int k = 0;

    for (int i = 0; i < aantal_woorden; i ++){
        bool b = true;

        for (int j = 0; j < sequence_aantal; j++){
            if (!woorden_vergelijken(words[i+j], sequence[j])){
                b = false;
                break;
            }
        }
        if (b){
            index[k] = i;
            k++;
        }
    }

    return k;
}

int aantal_sequence(Words sequence, Words words, int index[MAX_WORDS], int i)
{
    cout << "welke woorden wil je weten? Voer in met een spatie tussen de woorden, sluiten met een #" << endl;
        int j = 0;
        while (true)
        {
            cin >> sequence[j];

            if (sequence[j][0] == '#'){
                break;
            }

            j++;

        }
        int g = count_words(i, sequence, words, j, index);
}

int main()
{
    ifstream inputfile;
    Words words;
    char filename[MAX_LENGTH];
    ask_filename (filename);
    inputfile.open (filename);
    int i = read_file (inputfile, words);

    int k;

    cout << "wil je content toets 1, wil je stoppen toets 2" << endl;
    cin >> k;

    if (k == 1)
    {
        content (words , i);
    }

    if (k == 2)
    {
        return 0;
    }

    cout << "voor count toets 1, voor where toets 2, voor context toets 3" << endl;
    cin >> k;
    Words sequence;

    int index[MAX_WORDS];

    if (k == 1)
    {
        int g = aantal_sequence(sequence, words, index, i);
        cout << g << endl;
        cout << i << endl;
        cout << ((g * 100)/ (i)) << endl;
    }

    if (k == 2)
    {
        int g = aantal_sequence(sequence, words, index, i);

        for (int r = 0; r < g; r++){
            cout << index[r] << endl;
        }

        cout << g << endl;
    }

    if (k == 3)
    {
        cout << "welke woorden wil je weten? Voer in met een spatie tussen de woorden, sluiten met een #" << endl;
        int j = 0;
        while (true)
        {
            cin >> sequence[j];

            if (sequence[j][0] == '#'){
                break;
            }

            j++;

        }
        int g = count_words(i, sequence, words, j, index);

        int m;
        cout << "welke waarde voor m" << endl;
        cin >> m;

        for (int r = 0; r < g; r++){
            for (int q = -m; q < j+m; q++){
                cout << words [index[r]+q] << " ";
            }
            cout << endl;
        }

        cout << g << endl;
    }
}

