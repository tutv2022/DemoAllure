#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <string>

class StringOperations {
public:
    static std::string Concatenate(const std::string& str1, const std::string& str2);
    static int GetLength(const std::string& str);
    static std::string ToUpperCase(const std::string& str);
};

#endif // STRING_OPERATIONS_H

