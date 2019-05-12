#include <iostream>
#include <fstream>
#include <cassert>
#include <cerrno>
#include <string>
#include <cstring>

//                          
//                       

/*            
                                                                             
                                                                             
                                                                        
                                                                            
                                                                            
                                                                              
                                                                          
                                                                             
                                                                             
         
 */

const int MAX_ARGC = 256;
const int MAX_UINPUT_LENGTH = 2048;
const int MAX_WORDS_IN_MEMORY = 8192;

const std::string USAGE =
"Commands:\n"
"enter <filename>\n"
"    Opens the file at <filename> and stores the words in memory.\n"
"    Inefficient, but that's the assignment.\n\n"
"content\n"
"    Displays the stored words in memory, if any.\n\n"
"count [<words>]\n"
"    Displays the number of occurences of the word sequence <words>, and the\n"
"    relation to the total count of words within the text.\n\n"
"where <words>\n"
"    Displays the index positions of the word sequence <words>.\n\n"
"context <m> <words>\n"
"    Displays all occurences of the word sequence <words> within the context\n"
"    of <m> surrounding words.\n\n"
"stop\n"
"    Quit program.\n\n";

enum Action {Invalid=0, Enter, Content, Stop, Count, Where, Context};

void print_banner(char arg0[]) {
    std::cerr << arg0 << "\n\n";
    std::cerr << USAGE;
}

void sanitize_word(std::string* inword, std::string* outword) {
    assert(true);
    /*                
     */
    char c_outword[inword->length()+1];

    bool end_loop = false;
    for (unsigned int i=0, j=0; !end_loop; i++) {
        if (inword->c_str()[i] > 96 && inword->c_str()[i] < 123) {
            c_outword[j] = inword->c_str()[i];
            j++;
        } else if (inword->c_str()[i] > 64 && inword->c_str()[i] < 91) {
            c_outword[j] = inword->c_str()[i] + 32;
            j++;
        } else if (inword->c_str()[i] == '\0') {
            c_outword[j] = '\0';
            end_loop = true;
        }
    }

    *outword = static_cast<std::string>(c_outword);
}

void load_file(std::string args[], int argc,
               std::string words[], int* wc) {
    assert(MAX_WORDS_IN_MEMORY > 0);
    /*                
     */
    std::string filename;
    std::ifstream infile;
    std::string temp_word;

    if (argc < 2) {
        std::cerr << "No filename given!" << std::endl;
        return;
    }

    filename = args[1];
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            filename += ' ';
            filename += args[i];
        }
    }

    //                                   
    infile.open(filename);
    if (!infile.is_open()) {
        std::cerr << "Could not open input file: " << std::strerror(errno)
            << std::endl;
        return;
    }

    for (*wc = 0; *wc < MAX_WORDS_IN_MEMORY && infile; *wc = *wc + 1) {
        infile >> temp_word;
        sanitize_word(&temp_word, &words[*wc]);
    }

    *wc = *wc - 1; //                           
    std::cerr << "Total words in file: " << *wc << std::endl;
}

void show_words(std::string args[], int argc,
                std::string words[], int wc) {
    assert(true);
    /*                
     */
    if (argc > 1) {
        std::cerr << "Too many arguments!" << std::endl;
        return;
    }

    for (int i=0; i < wc; i++) {
        std::cout << words[i] << ' ';
    }

    std::cout << std::endl;
}

int split_input_at(char input[MAX_UINPUT_LENGTH],
                    char delim,
                    std::string args[MAX_ARGC]) {
    assert(true);
    /*                
                                                                               
                                              
     */
    int char_counter = 0;

    bool end_iloop = false;
    int i = 0;
    for (; i < MAX_ARGC && !end_iloop; i++) {
        char input_word[MAX_UINPUT_LENGTH];
        bool end_jloop = false;

        for (int j = 0; char_counter < MAX_UINPUT_LENGTH && !end_jloop;) {
            if (input[char_counter] == delim) {
                end_jloop = true;
            } else if (input[char_counter] == '\0') {
                input_word[j] = '\0';
                end_jloop = true;
                end_iloop = true;
            } else {
                input_word[j] = input[char_counter];
            }
            char_counter++;
            j++;
        }

        args[i] = static_cast<std::string>(input_word);
        //                                  
    }
    return i;
}

int query_user(Action* action, std::string args[MAX_ARGC], int* argc) {
    assert(MAX_ARGC > 2);
    /*                
                                                          
     */
    char input[MAX_UINPUT_LENGTH];
    char c;

    *action = Invalid;

    std::cerr << "> ";
    bool end_loop = false;
    for (int i=0; !end_loop && i < MAX_UINPUT_LENGTH; i++) {
        std::cin.get(c);

        if (std::cin.eof()) {
            //                                                             
            //                                                 
            *action = Stop;
            return 1;
        }

        if (std::cin.fail()) {
            return -errno;
        }

        if (c == '\n') {
            input[i] = '\0';
            end_loop = true;
        } else {
            input[i] = c;
        }
    }

    *argc = split_input_at(input, ' ', args);
    //                                  

    if (args[0] == "enter") {
        *action = Enter;
    } else if (args[0] == "content") {
        *action = Content;
    } else if (args[0] == "stop") {
        *action = Stop;
    } else if (args[0] == "count") {
        *action = Count;
    } else if (args[0] == "where") {
        *action = Where;
    } else if (args[0] == "context") {
        *action = Context;
    }

    return 1;
}

void occurence(Action action,
               std::string args[], int argc,
               std::string words[], int wc) {
    assert(action == Count || action == Where || action == Context);
    /*                
     */
    int occ_count = 0;
    int m;
    int args_offset = 1;

    if (action == Where && argc < 2) {
        std::cerr << "'where' needs an argument!" << std::endl;
        return;
    } else if (action == Count && argc < 2) {
        std::cerr << "'count' needs an argument!" << std::endl;
        return;
    } else if (action == Context && argc < 3) {
        std::cerr << "'context' needs a number and an argument!" << std::endl;
        return;
    }

    if (action == Context) {
        m = std::stoi(args[1]);
        args_offset++;
    }
    for (int i=args_offset; i < argc; i++) {
        std::cout << args[i] << std::endl;
    }

    for (int i=0; i <= (wc - (argc - args_offset)); i++) {
        bool match = true;
        for (int j=0; match && (j < (argc - args_offset)); j++) {
            //                                                                   
            if (words[i+j] != args[j+args_offset]) {
                match = false;
            }
        }

        if (match) {
            occ_count++;

            if (action == Where) {
                std::cout << "Sequence found at: " << i+1 << std::endl;
            }

            if (action == Context) {
                for (int j=-m; j < 0 && i+j > 0; j++) {
                    std::cout << words[i+j] << ' ';
                }
                for (int j=0; j < (argc - args_offset); j++) {
                    std::cout << words[i+j] << ' ';
                }
                for (int j=(argc - args_offset);
                        j < m + (argc - args_offset) && i+j < wc; j++) {
                    std::cout << words[i+j] << ' ';
                }
                std::cout << std::endl;
            }
        }
    }

    std::cout << "Total number of occurences: " << occ_count << std::endl;

    if (action == Count) {
        std::cout << "Total number of words: " << wc << std::endl;
        float occ_count_f = static_cast<float>(occ_count);
        float wc_f = static_cast<float>(wc);
        std::cout << "sequence / total words: " << occ_count_f/wc_f << std::endl;
    }
}

int main(int argc, char* argv[]) {
    assert(argc > 0);

    int r = -1;
    Action user_action;
    std::string cmd_args[MAX_ARGC];
    int cmd_argc;
    std::string words[MAX_WORDS_IN_MEMORY];
    int wc; //           

    print_banner(argv[0]);

    while (true) {
        r = query_user(&user_action, cmd_args, &cmd_argc);
        if (r < 0) {
            return -r;
        }

        switch(user_action) {
            case Stop:
                std::cerr << "Exiting..." << std::endl;
                std::cerr << std::endl;
                return 0;
                break;
            case Invalid:
                std::cerr << "Invalid command!" << std::endl;
                print_banner(argv[0]);
                break;
            case Enter:
                load_file(cmd_args, cmd_argc, words, &wc);
                break;
            case Content:
                show_words(cmd_args, cmd_argc, words, wc);
                break;
            case Count:
            case Where:
            case Context:
                occurence(user_action, cmd_args, cmd_argc, words, wc);
                break;
        }
    }
}

