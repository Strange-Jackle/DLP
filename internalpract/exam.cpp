#include <iostream>
#include <string>
#include <cctype>
#include <stack>
using namespace std;

enum KnownTokenType {
    NUMBER,
    OPERATOR,
    PARENTHESIS,
    E_O_I,
    UNKNOWN
};

struct Token {
    KnownTokenType type;
    string value;
};

class Analyser {
public:
    Analyser(const string &input) : input(input), pos(0) {}

    Token getNextToken() {
        while (pos < input.size()) {
            char current = input[pos];
            if (isspace(current)) 
            {
                ++pos;
            } 
            else if (isdigit(current)) 
            {
                return tokenizeNumber();
            } 
            else if (current == '+' || current == '-' || current == '*' || current == '/') 
            {
                return tokenizeOperator();
            } 
            else if (current == '(' || current == ')') 
            {
                return tokenizeParenthesis();
            } 
            else 
            {
                ++pos;
                return {UNKNOWN, string(1, current)};
            }
        }
        return {E_O_I, ""};
    }

    Token tokenizeNumber() {
        string number;
        while (pos < input.size() && isdigit(input[pos])) 
        {
            number += input[pos++];
        }
        return {NUMBER, number};
    }

    Token tokenizeOperator() {
        char op = input[pos++];
        return {OPERATOR, string(1, op)};
    }

    Token tokenizeParenthesis() {
        char paren = input[pos++];
        return {PARENTHESIS, string(1, paren)};
    }

    string input;
    int pos;
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluate(const string &input) {
    Analyser lexer(input);
    stack<int> values;
    stack<char> ops;
    Token token;

    while ((token = lexer.getNextToken()).type != E_O_I) {
        if (token.type == NUMBER) 
        {
            values.push(stoi(token.value));
        } 
        else if (token.type == PARENTHESIS && token.value == "(") 
        {
            ops.push('(');
        } 
        else if (token.type == PARENTHESIS && token.value == ")") 
        {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();
        } 
        else if (token.type == OPERATOR) 
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token.value[0])) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(token.value[0]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    // string input;
    // cout<<"Enter the expression: ";
    // cin>>input;
    string input = "4/(1-2)";
    int result = evaluate(input);
    cout << "Result: " << result << endl;
    return 0;
}