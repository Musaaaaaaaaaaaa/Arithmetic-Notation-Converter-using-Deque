#ifndef NOTATIONCONVERTER_HPP
#define NOTATIONCONVERTER_HPP

#include "NotationConverterInterface.hpp"
#include "Deque.hpp"
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <stack>

class NotationConverter : public NotationConverterInterface {
private:
    bool isOperator(char c) const;
    int precedence(char op) const;
    bool isValidChar(char c) const;
    std::string trim(const std::string& s) const;
    std::string infixToPostfixInternal(const std::string& inStr);
    std::string infixToPrefixInternal(const std::string& inStr);
    std::string reverseString(const std::string& s);

public:
    std::string postfixToInfix(std::string inStr) override;
    std::string postfixToPrefix(std::string inStr) override;
    std::string infixToPostfix(std::string inStr) override;
    std::string infixToPrefix(std::string inStr) override;
    std::string prefixToInfix(std::string inStr) override;
    std::string prefixToPostfix(std::string inStr) override;
};

#endif
