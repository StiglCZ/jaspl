#include <vector>
#include <string>
#include <stack>
#include <iostream>
using namespace std;
//cout << "\033[32m";
    //cout << "\033[37m";
enum errType{syntax, warn, common, info};
const int keywords_size = 5;
const string keywords[keywords_size] = {"call","int","return","if","set"};
void logerr(string message, errType type, string position){
    cout << message << endl;
    if(position.length() > 0)
        cout << "\tAt:" << position << endl;
    exit(1);
}
bool isValidNumber(const std::string& str) {
    try {std::stod(str);return true;} 
    catch (const std::exception& e) {return false;}
}
int keyword(string word){
    for(int i =0; i < keywords_size;i++){
        if(word == keywords[i])
            return i;
    }return -1;
}
string parse_number(string token, string name){
    if(isValidNumber(token))return token;
    if(token[0] == '\\')return name + "_" + token.replace(0,1,"");
    return "dword["  + name + "_" + token + "]";
}
string parse_operator(string input){
    if(input == "=")return "je";
    if(input == "!")return "jne";
    if(input == ">")return "jb";
    if(input == "<")return "jl";
    return "jnz";
}
string parse(vector<string> tokens,stack<string> *usingsptr){
    string result = "";
    stack<string> bss;
    for(int i =0; i < tokens.size();i++){
        //Detector for an object
        if(tokens[i] == "use"){
            //TODO: Add using functionality which joins the library code with the normal one
            string fileName = tokens[++i]
                .replace(0,1,"")
                .replace(tokens[i].size()-1,1,"");
            usingsptr->push(fileName);
        }else if(tokens[i] == "func"){
            //Getting the functions name, arugments and return type
            string name = tokens[++i];
            int conditionCounter = 0;
            stack<int> labelStack;
            result += name + ":\n";
            stack<string> args;
            if(tokens[++i] != "(")  logerr("( token not found in function define!",errType::syntax,name);
            while(++i < tokens.size()){
                     if(tokens[i] == ")") break;
                else if(tokens[i] != ","){args.push(tokens[i]);
                     if(tokens[i] != "void" && tokens[i] != "int"){
                        bss.push(name + "_" + tokens[i]);
                        
                        result +=  
                        "\tpop ebx\n\tpop eax\n\tpush ebx\n\tmov dword[" + name + "_" + tokens[i] + "], eax\n";
                       }
                    }
            }
            if(tokens[i] != ")")    logerr(") token not found in function define!",errType::syntax,name);
            if(tokens[++i] != "{")  logerr("Funcion opening not detected!", errType::syntax,name);
            //Getting the actual content
            int level = 0;
            while(++i < tokens.size()){
                string line_result = "";
                if(tokens[i] == "{") level++;
                else if(tokens[i] == "}")
                if(level-- == 0)break;
                else{
                    line_result += name + to_string(labelStack.top()) + "a:\n";
                    labelStack.pop();
                }
                switch(keyword(tokens[i])){
                    case 0:{
                        //Will implement arguments later
                        string fname = tokens[++i];i++;
                        while(++i < tokens.size()){
                            if(tokens[i] == ")")break;
                            line_result += "\tmov eax, " + parse_number(tokens[i],name) + "\n" +
                                           "\tpush eax\n";
                        }
                        line_result += "\tcall " + fname + "\n";
                        i++;
                        }break;
                    case 1:
                        bss.push(name + "_" + tokens[++i]);
                        if(tokens[++i] == "="){
                            if(isValidNumber(tokens[++i]))
                                line_result += 
                                    "\tmov eax, " + tokens[i++] + "\n" +
                                    "\tmov dword[" + bss.top() + "], eax\n";
                            else line_result += 
                                    "\tmov eax, dword[" + name + "_" + tokens[i++] + "]\n" +
                                    "\tmov dword[" + bss.top() + "], eax\n";
                        }
                        break;
                    case 2:
                        if(tokens[++i] == ";") line_result += "\tmov ebx, 0\n\tret\n";
                        else if(isValidNumber(tokens[i])){
                            line_result += 
                                "\tmov eax, " + tokens[i] + "\n" +
                                "\tmov ebx, 1\n" + 
                                "\tret\n";
                            i++;
                        }else{
                            line_result += 
                                "\tmov eax, dword[" + name + "_" + tokens[i] + "]\n" +
                                "\tmov ebx, 1\n" + 
                                "\tret\n";
                            i++;
                        }
                        break;
                    
                    case 3:{
                        if(tokens[++i] != "(") logerr("Broken syntax after the IF word",errType::syntax,name);
                        string num0 = parse_number(tokens[++i],name);
                        string op = parse_operator(tokens[++i]);
                        string num1 = parse_number(tokens[++i],name);
                        string label = name + to_string(conditionCounter++);
                        labelStack.push(conditionCounter-1);
                        line_result += 
                            "\tmov eax, " + num0 + "\n" +
                            "\tmov ebx, " + num1 + "\n" +
                            "\tcmp eax, ebx\n\t" +
                            op + " " + label + "\n" +
                            "\tjmp " + label + "a\n"+
                            label + ":\n";
                            }
                        break;
                    case 4:{
                        string 
                            numb1 = parse_number(tokens[++i],name),
                            numb2 = parse_number(tokens[++i],name),
                            numb3 = parse_number(tokens[++i],name),
                            numb4 = parse_number(tokens[++i],name),
                            inter = tokens[++i];
                            line_result += 
                                "\tmov eax, " + numb1 + "\n"+
                                "\tmov ebx, " + numb2 + "\n"+
                                "\tmov ecx, " + numb3 + "\n"+
                                "\tmov edx, " + numb4 + "\n"+
                                "\tint 0x"    + inter + "\n";
                            i++;
                        }
                        break;
                }
                result += line_result;
            }
        }
    }result += "section .bss\n";
    while(bss.size()){
        result += "\t" + bss.top() + " resd 1\n";
        bss.pop();
    }result += "section .text\n";
    return result;
}