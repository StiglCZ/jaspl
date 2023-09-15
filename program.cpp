#include <fstream>
#include <vector>
#include "tokenizer.hh"
#include "parser.hh"
#include <string>
#include <string.h>
char str[4096];
using namespace std;
void read_file(string filename){
    using namespace std;
    ifstream input(filename);
    input.seekg(0, std::ios::end);
    int length = input.tellg();
    input .seekg(0);
    streampos fileSize = input.tellg();
    input.read(str,length);
    input.close();
}
void compile(string filename, stack<string> *usings, string *output){
    for(int i =0; i < 4096;i++)str[i] = '\0';
    read_file(filename);
    vector<string> tokens = tokenize(str);
    *output += ";" + filename + "\n" + parse(tokens,usings);
}
int main(int argc, char* argv[]){
    string output;
    stack<string> usings;
    //Compiling
    if(argc < 2)
        logerr("Too few args",errType::common,"File loading");
    compile(argv[1],&usings, &output);
    while (usings.size() > 0){
        string filename = usings.top();
        usings.pop();
        compile(filename,&usings, &output);
    }
    output = "global _start\n_start:\n\tcall main\n\tmov eax, 1\n\txor ebx, ebx\n\tint 0x80\n" + output;
    //Output the final code
    cout << output;
    return 0;
}