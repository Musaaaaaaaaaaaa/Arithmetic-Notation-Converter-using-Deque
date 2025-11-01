//Moosa Shehzad Abbasi
//U37033529
//Implements a Deque and a NotationConverter class that converts arithmetic expressions between infix, postfix, and prefix forms.

#include "NotationConverter.hpp"
#include "Deque.hpp"
#include <algorithm>
#include <stack>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <string>

//small helpers (local to this .cpp)
static inline bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//split into tokens even if input has no spaces, e.g. "(A+B)*(Y-D)"
static std::vector<std::string> splitTokens(const std::string& s) {
    std::vector<std::string> tok;
    std::string cur;
    auto flush = [&]() {
        if (!cur.empty()) { tok.push_back(cur); cur.clear(); }
    };
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            flush();
        } else if (isOp(c) || c == '(' || c == ')') {
            flush();
            tok.emplace_back(1, c);
        } else {
            cur.push_back(c); //operand piece (letters/digits)
        }
    }
    flush();
    return tok;
}

static std::string joinTokens(const std::vector<std::string>& v) {
    std::ostringstream oss;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) oss << ' ';
        oss << v[i];
    }
    return oss.str();
}

//remove parentheses and normalize spaces for outputs that must not contain '(' or ')'
static std::string removeParens(const std::string &s) {
    std::string out; out.reserve(s.size());
    for (char c : s) if (c != '(' && c != ')') out.push_back(c);

    //normalize spaces
    std::string result;
    result.reserve(out.size());
    bool space = false;
    for (char ch : out) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            if (!space) { result += ' '; space = true; }
        } else { result += ch; space = false; }
    }
    if (!result.empty() && result.front() == ' ') result.erase(result.begin());
    if (!result.empty() && result.back()  == ' ') result.pop_back();
    return result;
}

//notationConverter methods
bool NotationConverter::isOperator(char c) const { return isOp(c); }

int NotationConverter::precedence(char op) const {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool NotationConverter::isValidChar(char c) const {
    return std::isalnum(static_cast<unsigned char>(c)) || isOperator(c) || c == '(' || c == ')' || std::isspace(static_cast<unsigned char>(c));
}

std::string NotationConverter::trim(const std::string& s) const {
    std::string out; out.reserve(s.size());
    bool space = false;
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!space) { out += ' '; space = true; }
        } else { out += c; space = false; }
    }
    if (!out.empty() && out.front() == ' ') out.erase(out.begin());
    if (!out.empty() && out.back()  == ' ') out.pop_back();
    return out;
}

//infix tokens -> Postfix tokens (Shunting-yard), left-associative for + - * /
static std::vector<std::string> infixTokensToPostfixTokens(
    const std::vector<std::string>& tokens,
    const NotationConverter* self
) {
    std::vector<std::string> out;
    std::vector<std::string> opStack;

auto prec = [&](char c){
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
};


    for (const auto& t : tokens) {
        if (t == "(") {
            opStack.push_back(t);
        } else if (t == ")") {
            while (!opStack.empty() && opStack.back() != "(") {
                out.push_back(opStack.back());
                opStack.pop_back();
            }
            if (!opStack.empty() && opStack.back() == "(") opStack.pop_back();
        } else if (t.size() == 1 && isOp(t[0])) {
            //left-associative: pop while stack top has precedence >= current
            while (!opStack.empty()
                   && opStack.back().size() == 1
                   && isOp(opStack.back()[0])
                   && prec(opStack.back()[0]) >= prec(t[0])) {
                out.push_back(opStack.back());
                opStack.pop_back();
            }
            opStack.push_back(t);
        } else {
            //operand
            out.push_back(t);
        }
    }
    while (!opStack.empty()) {
        out.push_back(opStack.back());
        opStack.pop_back();
    }
    return out;
}

//postfix to Infix
std::string NotationConverter::postfixToInfix(std::string inStr) {
    for (char c : inStr) if (!isValidChar(c)) throw std::invalid_argument("Invalid character");

    auto tokens = splitTokens(inStr);
    Deque<std::string> st;

    for (const auto& t : tokens) {
        if (t.size() == 1 && isOp(t[0])) {
            std::string right = st.back(); st.pop_back();
            std::string left  = st.back(); st.pop_back();
            st.push_back("(" + left + " " + t + " " + right + ")");
        } else {
            st.push_back(t);
        }
    }
    return st.back();
}

//postfix to Prefix
std::string NotationConverter::postfixToPrefix(std::string inStr) {
    return infixToPrefix(postfixToInfix(inStr));
}

//infix to Postfix
std::string NotationConverter::infixToPostfix(std::string inStr) {
    for (char c : inStr) if (!isValidChar(c)) throw std::invalid_argument("Invalid character");
    auto tokens  = splitTokens(inStr);
    auto postfix = infixTokensToPostfixTokens(tokens, this);
    return removeParens(joinTokens(postfix));
}

//infix to Prefix
std::string NotationConverter::infixToPrefix(std::string inStr) {
    for (char c : inStr) if (!isValidChar(c)) throw std::invalid_argument("Invalid character");

    auto tokens = splitTokens(inStr);
    //reverse tokens and swap parens
    std::reverse(tokens.begin(), tokens.end());
    for (auto& t : tokens) {
        if (t == "(") t = ")";
        else if (t == ")") t = "(";
    }

    auto reversedPostfix = infixTokensToPostfixTokens(tokens, this);

    //reverse postfix tokens to get prefix tokens
    std::reverse(reversedPostfix.begin(), reversedPostfix.end());

    return removeParens(joinTokens(reversedPostfix));
}

//prefix to infix
std::string NotationConverter::prefixToInfix(std::string inStr) {
    for (char c : inStr) if (!isValidChar(c)) throw std::invalid_argument("Invalid character");

    auto tokens = splitTokens(inStr);
    std::reverse(tokens.begin(), tokens.end());

    Deque<std::string> st;
    for (const auto& t : tokens) {
        if (t.size() == 1 && isOp(t[0])) {
            std::string left  = st.back(); st.pop_back();
            std::string right = st.back(); st.pop_back();
            st.push_back("(" + left + " " + t + " " + right + ")");
        } else {
            st.push_back(t);
        }
    }
    return st.back();
}

//prefix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr) {
    return infixToPostfix(prefixToInfix(inStr));
}
