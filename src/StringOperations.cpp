#include "StringOperations.h"
#include <sstream>

std::string StringOperations::Concatenate(const std::string& str1, const std::string& str2) {
    return str1 + " " + str2;
}

int StringOperations::GetLength(const std::string& str) {
    return static_cast<int>(str.length());
}

std::string StringOperations::ToUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
    return result;
}

