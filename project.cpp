#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_set>

// Define token types
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SEPARATOR,
    UNKNOWN
};

// Structure to represent a token
struct Token {
    std::string value;
    TokenType type;
};

// Keywords set for simplicity
std::unordered_set<std::string> keywords = {"int", "float", "if", "else", "for", "while", "return", "void" , "cout", "endl"};

// Check if a string is a keyword
bool isKeyword(const std::string& word) {
    return keywords.find(word) != keywords.end();
}

// Check if a string is a number
bool isNumber(const std::string& word) {
    if (word.empty()) return false;
    for (char c : word) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

// Tokenize a given line into tokens
std::vector<Token> tokenize(const std::string& line) {
    std::vector<Token> tokens;
    std::string temp;

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        // If it's a separator or operator, store temp as a token and then add the separator/operator
        if (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            if (!temp.empty()) {
                // Determine the type of the token stored in temp
                if (isKeyword(temp)) {
                    tokens.push_back({temp, TokenType::KEYWORD});
                } else if (isNumber(temp)) {
                    tokens.push_back({temp, TokenType::NUMBER});
                } else {
                    tokens.push_back({temp, TokenType::IDENTIFIER});
                }
                temp.clear();
            }

            // Add the separator or operator as its own token
            tokens.push_back({std::string(1, ch), TokenType::SEPARATOR});
        } 
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>') {
            if (!temp.empty()) {
                // Determine the type of the token stored in temp
                if (isKeyword(temp)) {
                    tokens.push_back({temp, TokenType::KEYWORD});
                } else if (isNumber(temp)) {
                    tokens.push_back({temp, TokenType::NUMBER});
                } else {
                    tokens.push_back({temp, TokenType::IDENTIFIER});
                }
                temp.clear();
            }

            // Add the operator as its own token
            tokens.push_back({std::string(1, ch), TokenType::OPERATOR});
        }
        else {
            temp += ch; // Accumulate characters into temp for keywords, identifiers, or numbers.
        }
    }

    // If there's any leftover in temp, add it as a token
    if (!temp.empty()) {
        if (isKeyword(temp)) {
            tokens.push_back({temp, TokenType::KEYWORD});
        } else if (isNumber(temp)) {
            tokens.push_back({temp, TokenType::NUMBER});
        } else {
            tokens.push_back({temp, TokenType::IDENTIFIER});
        }
    }

    return tokens;
}

int main() {

    std::string line;
    std::vector<Token> allTokens;
    int tokenCounter = 0;
    std::ifstream inputFile("testData.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    

    // Read the file line by line and tokenize each line
    while (getline(inputFile, line)) {
        std::vector<Token> tokens = tokenize(line);
        allTokens.insert(allTokens.end(), tokens.begin(), tokens.end());
    }

    inputFile.close();

    // Print all tokens with their types
    for (const Token& token : allTokens) {
        std::cout << "Token: \"" << token.value << "\", Type: ";

        switch (token.type) {
            case TokenType::KEYWORD: std::cout << "KEYWORD"; break;
            case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
            case TokenType::NUMBER: std::cout << "NUMBER"; break;
            case TokenType::OPERATOR: std::cout << "OPERATOR"; break;
            case TokenType::SEPARATOR: std::cout << "SEPARATOR"; break;
            default: std::cout << "UNKNOWN"; break;
        }
        std::cout << std::endl;
    }

    return 0;
}
