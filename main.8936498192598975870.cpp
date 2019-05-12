#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

//                             
//                        

using namespace std;
//
const int MAX_CHARACTERS= 60;
const int MAX_WORDS = 30000;

bool open_file(ifstream& file) {
    string name;
    getline(cin, name);
    file.open(name.c_str());
    return file.is_open();
}

void read_content(ifstream& file)
{
    string word;
    int wordcount =0;
    while (file >> word)
    {
        cout<< word << '\n';
        wordcount++;
    }
    cout << wordcount;
}

bool user_interface() {
    string command;
    cout << "Enter command: " << endl;
    cin >> command;
    cin.ignore(1);

    if (command == "enter") {
        ifstream file;
        if (open_file(file)) {
            read_content(file);
            file.close();
        }
    }
    else if (command == "content") {

    }
}

int main()
{
    user_interface();

}

