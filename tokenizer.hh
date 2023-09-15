#include <string>
#include <vector>
using namespace std;
int replaceAll(std::string& str, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    int counter = 0;
    while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.length(), replace);
        pos += replace.length();
        counter++;
    }return counter;
}
vector<string> tokenize(string source){
    while(replaceAll(source,"  "," ") > 0);
    while(replaceAll(source,"\t\t","\t") > 0);
    while(replaceAll(source,"\n\n","\n") > 0);
    //cout << source;
    vector<string> tokens;
    string tmp = "";
    bool ignore = false, comment = false; 
    for(int i =0; i < source.length();i++){
        if(source[i] == '$')comment = true;
        if(comment){
            if(source[i] == '\n')comment = false;
            continue;
        }
        if(source[i] == '"'){
            ignore = !ignore;
            tmp += '"';
            if(!ignore){
                tokens.push_back(tmp);
                tmp = "";
            }continue;
        }
        if(source[i] == '-' || source[i] == '+'){
            int last = tokens.size()-1;
            if(tokens[last] == "+" || tokens[last] == "-"){
                char ch[] = {source[i]};
                tokens[last] += ch;
                continue;
            }
        }
        if(source[i] == ';' || source[i] == ',' ||
           source[i] == '{' || source[i] == '}' ||
           source[i] == '(' || source[i] == ')' ||
           source[i] == '+' || source[i] == '-' ||
           source[i] == '*' || source[i] == '/' ||
           source[i] == '<' || source[i] == '>' ||
           source[i] == '=' || source[i] == '!'){
            char ch[] = {source[i]};
            //cout << tmp << "\n" << ch << "\n";
            tokens.push_back(tmp);
            tokens.push_back(ch);
            tmp = "";
        }else if(source[i] == ' '  ||
                 source[i] == '\n' ||
                 source[i] == '\t'){
            if(tmp != "")tokens.push_back(tmp);
            tmp = "";
        }else tmp += source[i];
    }
    for(int i =0; i < tokens.size();i++){
        if(tokens[i] == "" || tokens[i] == " ")
        tokens.erase(tokens.begin() + i);
    }
    return tokens;
}
