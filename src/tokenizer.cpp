#include <string>
#include <vector>
using namespace std;
//Replace util function
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
    //Get rid of double white characters
    while(replaceAll(source,"  "," ") > 0);
    while(replaceAll(source,"\t\t","\t") > 0);
    while(replaceAll(source,"\n\n","\n") > 0);
    vector<string> tokens;
    string tmp = "";
    bool ignore = false, comment = false;
    for(size_t i =0; i < source.length();i++){
        //Comments with $ sign
        if(source[i] == '$')comment = true;
        if(comment){
            if(source[i] == '\n')comment = false;
            continue;
        }
        //String syntax(string is not done yet,
        //but this is implmented already)
        if(source[i] == '"'){
            ignore = !ignore;
            tmp += '"';
            if(!ignore){
                tokens.push_back(tmp);
                tmp = "";
            }continue;
        }
        if(ignore){
            char ch[] = {source[i]};
            tmp += ch;
            continue;
        }
        //++ and -- syntax
        if(source[i] == '-' || source[i] == '+'){
            int last = tokens.size()-1;
            if(tokens[last] == "+" || tokens[last] == "-"){
                char ch[] = {source[i]};
                tokens[last] += ch;
                continue;
            }
        }
        //Replacing special characters crucial to gen. functionality
        if(source[i] == ';' || source[i] == ',' ||
           source[i] == '{' || source[i] == '}' ||
           source[i] == '(' || source[i] == ')' ||
           source[i] == '+' || source[i] == '-' ||
           source[i] == '*' || source[i] == '/' ||
           source[i] == '<' || source[i] == '>' ||
           source[i] == '=' || source[i] == '!'){
        //Converting char into string so its not broken when pushed
            char ch[] = {source[i]};
            tokens.push_back(tmp);
            tokens.push_back(ch);
            tmp = "";
        //White space characters - gone
        }else if(source[i] == ' '  ||
                 source[i] == '\n' ||
                 source[i] == '\t'){
            if(tmp != "")tokens.push_back(tmp);
            tmp = "";
        }else tmp += source[i];
    }
    //Removing empty fields left by white spaces
    for(size_t i =0; i < tokens.size();i++){
        if(tokens[i] == "" || tokens[i] == " ")
        tokens.erase(tokens.begin() + i);
    }
    return tokens;
}
