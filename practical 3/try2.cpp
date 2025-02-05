#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Structure to store token information
struct TokenInfo {
    string type;
    string value;
    int lineNumber;
};

unordered_set<string> keywords = {
    "int", "float", "double", "char", "if", "else", "for", "while",
    "do", "switch", "case", "break", "continue", "return", "void",
    "class", "namespace", "using",
    "bool", "true", "false", "include", "main", "cout", "cin", "endl"
};

unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "&", "|", "^", "<<", ">>", "++", "--", "+=", "-=",
    "*=", "/=", "%=", "&=", "|=", "^=", ".", "::"
};

class LexicalAnalyzer {
private:
    vector<TokenInfo> tokens;
    vector<string> lexicalErrors;
    vector<string> symbolTable;
    int currentLine;

    bool isKeyword(const string& word) {
        return keywords.find(word) != keywords.end();
    }

    bool isOperator(const string& word) {
        return operators.find(word) != operators.end();
    }

    bool isIdentifier(const string& word) {
        if (word.empty() || isdigit(word[0]) || isKeyword(word)) return false;
        for (char c : word) {
            if (!isalnum(c) && c != '_') return false;
        }
        return true;
    }

    bool isNumber(const string& word) {
        bool hasDecimal = false;
        if (word.empty()) return false;

        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == '.') {
                if (hasDecimal) return false;
                hasDecimal = true;
            } else if (!isdigit(word[i])) {
                return false;
            }
        }
        return true;
    }

    void addToken(const string& type, const string& value) {
        tokens.push_back({type, value, currentLine});
    }

    void addError(const string& word) {
        lexicalErrors.push_back(word + " (Line " + to_string(currentLine) + ")");
    }

public:
    LexicalAnalyzer() : currentLine(1) {}

    void analyze(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        bool insideComment = false;

        while (getline(file, line)) {
            string word;
            bool insideString = false;

            for (size_t i = 0; i < line.length(); ++i) {
                char c = line[i];

                if (insideComment) {
                    if (i < line.length() - 1 && line[i] == '*' && line[i + 1] == '/') {
                        insideComment = false;
                        ++i;
                    }
                    continue;
                }

                if (i < line.length() - 1 && line[i] == '/' && line[i + 1] == '*') {
                    insideComment = true;
                    ++i;
                    continue;
                }

                if (i < line.length() - 1 && line[i] == '/' && line[i + 1] == '/') {
                    addToken("Comment", line.substr(i));
                    break;
                }

                if (c == '"' || c == '\'') {
                    if (!insideString) {
                        if (!word.empty()) {
                            processWord(word);
                            word.clear();
                        }
                        word = c;
                        insideString = true;
                    } else {
                        word += c;
                        addToken("String", word);
                        word.clear();
                        insideString = false;
                    }
                    continue;
                }

                if (insideString) {
                    word += c;
                    continue;
                }

                if (ispunct(c)) {
                    if (!word.empty()) {
                        processWord(word);
                        word.clear();
                    }
                    string op(1, c);
                    if (isOperator(op)) {
                        addToken("Operator", op);
                    } else {
                        addToken("Punctuation", op);
                    }
                    continue;
                }

                if (isspace(c)) {
                    if (!word.empty()) {
                        processWord(word);
                        word.clear();
                    }
                } else {
                    word += c;
                }
            }

            if (!word.empty()) {
                processWord(word);
            }
            currentLine++;
        }
        file.close();
    }

    void processWord(const string& word) {
        if (isKeyword(word)) {
            addToken("Keyword", word);
        } else if (isNumber(word)) {
            addToken("Number", word);
        } else if (isIdentifier(word)) {
            addToken("Identifier", word);
            if (find(symbolTable.begin(), symbolTable.end(), word) == symbolTable.end()) {
                symbolTable.push_back(word);
            }
        } else {
            addError(word);
        }
    }

    void writeToCSV(const string& outputFile) {
        ofstream file(outputFile);
        if (!file.is_open()) {
            cerr << "Error: Could not create output file" << endl;
            return;
        }

        // Write headers
        file << "Token Analysis Results\n\n";

        // Write Tokens section
        file << "TOKENS\n";
        file << "Type,Value,Line Number\n";
        for (const auto& token : tokens) {
            file << token.type << "," << token.value << "," << token.lineNumber << "\n";
        }

        // Write Lexical Errors section
        file << "\nLEXICAL ERRORS\n";
        file << "Error\n";
        for (const auto& error : lexicalErrors) {
            file << error << "\n";
        }

        // Write Symbol Table section
        file << "\nSYMBOL TABLE\n";
        file << "Index,Identifier\n";
        for (size_t i = 0; i < symbolTable.size(); i++) {
            file << (i + 1) << "," << symbolTable[i] << "\n";
        }

        file.close();
        cout << "Analysis results have been written to " << outputFile << endl;
    }
};

int main() {
    string inputFile, outputFile;

    cout << "Enter the input file name to analyze: ";
    cin >> inputFile;

    cout << "Enter the output CSV file name: ";
    cin >> outputFile;

    LexicalAnalyzer analyzer;
    analyzer.analyze(inputFile);
    analyzer.writeToCSV(outputFile);

    return 0;
}
