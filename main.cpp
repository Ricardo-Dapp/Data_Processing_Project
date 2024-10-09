
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>


enum Category {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    SEPARATOR,
};

class Token {
public:
    std::string value;
    Category tokenType;
    Token(std::string a, Category b): value(a), tokenType(b){}
};

std::vector<std::string> keywords = {"int", "if", "else", "for", "while", "return", "void", 
                                    "cout", "endl","#include", "<iostream>" , "using" , "namespace", "std", "main"};
std::vector<std::string> separators = {"(", ")", "[", "]", "{", "}", "," , ";"};
std::vector<std::string> operators = {"+", "-", "++", "--", "*", "%", "<", ">", "**", "/", "=","==", "<<", ">>" };
std::vector<Token> tokenHolder;

int tokenCounter = 0;

// create a function to create a token instead of repeating it during the for loop
void tokenizeData(std::string val)
{
    bool found = false;

    for(int i = 0; i < tokenHolder.size(); i++)
    {
        if(tokenHolder[i].value == val)
        {
          found = true;

        }
    }

    if(!found)
    {
        if(std::find(keywords.begin(), keywords.end(), val) != keywords.end()) 
        {
                Token inputToken = Token(val, Category::KEYWORD);
                tokenHolder.push_back(inputToken);
        }
        else if(std::find(separators.begin(), separators.end(), val) != separators.end())
        {
                Token inputToken = Token(val, Category::SEPARATOR);
                tokenHolder.push_back(inputToken);
        }
        else if(std::find(operators.begin(), operators.end(), val) != operators.end())
        {
            Token inputToken = Token(val, Category::OPERATOR);
            tokenHolder.push_back(inputToken);
        }
        else if(isdigit(val[0]) || val[0] == '"')
        {
            Token inputToken = Token(val, Category::LITERAL);
            tokenHolder.push_back(inputToken);
        }
        else if(val[0] != '/' || val[1] != '/' )
        {
            Token inputToken = Token(val, Category::IDENTIFIER);
            tokenHolder.push_back(inputToken);
        }
    }
    tokenCounter++;
    
}
int main () {

    std::string data;
    std::string parsedData;
    

    std::ifstream inputFile("test1.txt");

        if (!inputFile.is_open()) 
        {
            std::cout << "Error opening the file!" << std::endl;
            return 1;
        }   
    
    std::cout << "File Content: " << std::endl;

    // get the data from the file into a string
    while (getline(inputFile, data)) {
       /*
        if (!data.empty() && (data[0] != '/' && data[1] != '/') ||
            !data.empty() && (data[0] !='*' && data[1] != '*') ||
            data.empty() && data[0] !='*') */
        if(!data.empty() && (data[0] != '/' && data[1] != '/') && (data[0] !='*' && data[1] != '*') && (data[0] !='/' && data[1] != '*') &&(data[0] !='*' && data[1] != '/'))
        {
            parsedData += data.append("\n");
        }
    }
    inputFile.close();
   
    // remove spaces
    bool wasLastSpace = false;
    std::string cleanData;

    for(int i = 0; i < parsedData.size() ; i++)
    {
        if(std::isspace(parsedData[i]))
        {
            if(!wasLastSpace)
            {
                cleanData += parsedData[i];
                wasLastSpace = true;
            }
        }
        else
        {
           cleanData+= parsedData[i];
            wasLastSpace = false;
        }  
    }

    // display the new string
   std::cout << cleanData << std::endl;


    // tokenize
    std::string temp;

    for(int i = 0; i < cleanData.size() ; i++)
    {
        if(cleanData[i] == ' ' || cleanData[i] == '\n' )
        { 
            if(std::find(temp.begin(), temp.end(), '"') == temp.end())
            {
                 if(!temp.empty())
                 {
                    tokenizeData(temp);
                    temp.clear();
                 }
            }
            
           
        }
        else if(cleanData[i] == ',' || cleanData[i] == '(' || cleanData[i] == ')' || cleanData[i] == ';' 
                ||cleanData[i] == '{' || cleanData[i] == '}' || cleanData[i] == '[' || cleanData[i] == ']')
                {

                    if(!temp.empty())
                    {
                      
                        tokenizeData(temp);
                        temp.clear();
                        
                       
                    }
                    tokenizeData(std::string(1, cleanData[i]));
                   
                }
      else if((cleanData[i] == '<' && cleanData[i+1] == '<') || 
            (cleanData[i] == '>' && cleanData[i+1] == '>'))
    {
        if(!temp.empty())
        {
            tokenizeData(temp);
            temp.clear();
        }
        // Tokenize << or >> as a single token
        tokenizeData(std::string(1, cleanData[i]) + std::string(1, cleanData[i+1]));
        i++; // Skip the next character since we processed a 2-character operator
    }
        else
        {
            temp += cleanData[i];
        }
    }

    if (!temp.empty()) {
        tokenizeData(temp);
    }

    // Display Categories with tokens 
    
    std::cout << "Categories | Tokens          |\n" ;
    
    std::cout << "Keywords: ";
    
    for (int i = 0; i < tokenHolder.size(); ++i) {
        
        if(tokenHolder[i].tokenType == KEYWORD)
        {
            std::cout << tokenHolder[i].value << ", ";
            
        }
       
        
    }

    std::cout << "\n";

    std::cout << "Separators: ";
    for (int i = 0; i < tokenHolder.size(); ++i) {
        
        if(tokenHolder[i].tokenType == SEPARATOR)
        {
            std::cout << tokenHolder[i].value << ", ";
        }
        
    }
    

    std::cout << "\nIdentifier: ";

    for (int i = 0; i < tokenHolder.size(); ++i) {
        
        if(tokenHolder[i].tokenType == IDENTIFIER)
        {
            std::cout << tokenHolder[i].value << ", ";
        }
       
        
    }

     std::cout << "\nOperators: ";

    for (int i = 0; i < tokenHolder.size(); ++i) {
        
        if(tokenHolder[i].tokenType == OPERATOR)
        {
            std::cout << tokenHolder[i].value << ", ";
        }
       
        
    }
      std::cout << "\nLiterals: ";

    for (int i = 0; i < tokenHolder.size(); ++i) {
        
        if(tokenHolder[i].tokenType == LITERAL)
        {
            std::cout << tokenHolder[i].value << ", ";
        }
   
        
    }

    std::cout << "\nTokens: " << tokenCounter << std::endl;
   
    return 0;

}