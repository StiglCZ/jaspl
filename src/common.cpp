#include "common.hh"
int replaceAll(std::string& str, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    int counter = 0;
    while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.length(), replace);
        pos += replace.length();
        counter++;
    }return counter;
}